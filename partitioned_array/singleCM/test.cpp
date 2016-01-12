#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;

const int REF_SIZE = 20;
double ref_ra[REF_SIZE];
double ref_dec[REF_SIZE];
int ref_pix[REF_SIZE];
int cnt[REF_SIZE];
const double radius = 0.0056; //degree
const double pi=3.141592653589793238462643383279502884197;
double radians(double degree)
{
	  return degree * pi / 180.0;
}
bool matched(double ra1,double dec1,double ra2,double dec2,double radius)
{
	double z1 = sin(radians(dec1));
	double x1 = cos(radians(dec1)) * cos(radians(ra1));
	double y1 = cos(radians(dec1)) * sin(radians(ra1));

	double z2 = sin(radians(dec2));
	double x2 = cos(radians(dec2)) * cos(radians(ra2));
	double y2 = cos(radians(dec2)) * sin(radians(ra2));

	double distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
	double dist2 = 4 * pow(sin(radians(0.0056 / 2)),2);

	if(distance <= dist2)
		return true;
	return false;

}

int main(int argc, char *argv[])
{
	memset(cnt,0,sizeof(cnt));
	FILE *fd = fopen(argv[1],"r");

	for(int i = 0; i < REF_SIZE; ++i)
	{
		fscanf(fd,"%d%lf%lf",&ref_pix[i],&ref_ra[i],&ref_dec[i]);
		if(ref_pix[i])
			printf("error!\n");
	}
	fclose(fd);

	fd = fopen(argv[2],"r");
	int sum = 0;
	for(int i = 0; i < 2048; ++i)
	{
		int a;
		double b,c;
		fscanf(fd,"%d%lf%lf",&a,&b,&c);
		if(a)
			break;
		for(int j = 0; j < REF_SIZE;++j)
		{
			if(matched(ref_ra[j],ref_dec[j],b,c,radius))
			{
				sum++;
				cnt[j]++;
				printf("matched %.8lf %.8lf match %.8lf %.8lf\n",ref_ra[j],ref_dec[j],b,c);
			}
		}
		cout << endl;
	}

	cout << " sum " << sum <<endl;
	for(int i = 0; i < REF_SIZE; ++i)
		cout << i << " " << cnt[i] << endl;

}
