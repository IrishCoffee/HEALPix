#include <iostream>
#include <sys/time.h>
#include <omp.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "mpi.h"
using namespace std;

struct NODE
{
	double ra;
	double dec;
	int pix;
};

double diffTime(timeval start,timeval end)
{
	    return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) * 0.001;
}

int ref_request_node[6][6] = {{0,1,2,3,4,5},{1,0,4,5,3,2},{2,3,0,4,5,1},{3,2,5,0,1,4},{4,5,1,2,0,3},{5,4,3,1,2,0}};

const int SIZE = 1200000000;
int main(int argc, char* argv[])
{
	int rank,numprocs,namelen;
	char processor_name[32];
	int MPI_MESSLEN = atoi(argv[1]);
	struct timeval start,end;
	//MPI Communication Initalization
	MPI_Datatype mpi_node;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Get_processor_name(processor_name,&namelen);

	//Register new data type
	MPI_Datatype old_types[3];
	MPI_Aint indices[3];
	int blocklens[3];
	blocklens[0] = 1;
	blocklens[1] = 1;
	blocklens[2] = 1;
	old_types[0] = MPI_DOUBLE;
	old_types[1] = MPI_DOUBLE;
	old_types[2] = MPI_INT;

	indices[0] = 0;
	indices[1] = sizeof(double);
	indices[2] = 2 * sizeof(double);

	MPI_Type_struct(3,blocklens,indices,old_types,&mpi_node);
	MPI_Type_commit(&mpi_node);

	NODE *send_buffer = (NODE *)malloc(sizeof(NODE) * SIZE);
	NODE *recv_buffer = (NODE *)malloc(sizeof(NODE) * SIZE);

#pragma omp parallel for
	for(int i = 0; i < SIZE; ++i)
	{
		send_buffer[i].pix = i;
		send_buffer[i].ra = i * 1.0;
		send_buffer[i].dec = i * 1.0;
	}

	int exchange_amount = SIZE / numprocs;
	MPI_Status status;
	gettimeofday(&start,NULL);
	for(int i = 0; i < numprocs - 1; ++i)
	{
		int commID = ref_request_node[rank][i+1];
		int ite = exchange_amount / MPI_MESSLEN;
		for(int kk = 0; kk < 2; ++kk)
		{
			if((kk == 0 && commID > rank) || (kk == 1 && commID < rank))
			{
				for(int j = 0; j < ite; ++j)
				{
					MPI_Send(send_buffer + commID * exchange_amount + j * MPI_MESSLEN,MPI_MESSLEN,mpi_node,commID,3,MPI_COMM_WORLD);
		//			printf("rank-%d send to rank-%d chunk-%d\n",rank,commID,j);
				}
			

			}
			else if((kk == 0 && commID < rank) || (kk == 1 && commID > rank))
			{
				for(int j = 0; j < ite; ++j)
				{
					MPI_Recv(recv_buffer + commID * exchange_amount + j * MPI_MESSLEN,MPI_MESSLEN,mpi_node,commID,3,MPI_COMM_WORLD,&status);
		//			printf("rank-%d recv from rank-%d chunk-%d\n",rank,commID,j);
				}
			}
		}
	}
	gettimeofday(&end,NULL);
	printf("rank-%d communication costs %.3f s\n",rank,diffTime(start,end) * 0.001);
}


