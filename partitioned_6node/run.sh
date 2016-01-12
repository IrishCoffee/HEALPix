#echo "sdss * sdss"
time mpirun -machinefile hosts ./main FileList/SDSS_outOrder 120 10000000 0 FileList/SDSS_outOrder 120 10000000 0
#echo "2mass * 2mass"
#time mpirun -machinefile hosts ./main FileList/2MASS_list 120 3924941 0 FileList/2MASS_list 120 3924941 0
#echo "wise * wise"
#time mpirun -machinefile hosts ./main FileList/WISE_list 120 6230283 0 FileList/WISE_list 120 6230283 0	> wise_wise_log
#echo "wise * 2mass"
#time mpirun -machinefile hosts ./main FileList/WISE_list 120 6230283 0 FileList/2MASS_list 120 3924941 0	> wise_2mass_log
#echo "2mass * wise"
#time mpirun -machinefile hosts ./main FileList/2MASS_list 120 3924941 0 FileList/WISE_list 120 6230283 0	> 2mass_wise_log
#echo "wise * sdss"
#time mpirun -machinefile hosts ./main FileList/WISE_list 120 6230283 0 FileList/SDSS_outOrder 120 10000000 0	> wise_sdss_log
#echo "sdss * wise"
#time mpirun -machinefile hosts ./main  FileList/SDSS_outOrder 120 10000000 0 FileList/WISE_list_2 120 6230283 0	> sdss_wise_log
#echo "2mass * sdss"
#time mpirun -machinefile hosts ./main FileList/2MASS_list 120 3924941 0 FileList/SDSS_outOrder 120 10000000 0	> 2mass_sdss_log
#echo "sdss * 2mass"
#time mpirun -machinefile hosts ./main  FileList/SDSS_outOrder 120 10000000 0 FileList/2MASS_list 120 3924941 0 	> sdss_2mass_log
