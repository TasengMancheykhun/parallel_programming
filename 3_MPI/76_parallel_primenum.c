#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>

//#define N 1000000
#define N 1000

/*
                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

*/

int main()
{

        MPI_Init(NULL,NULL);

        int rank, size;
 
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	int i, j;
	int count, flag;
	double exe_time;
	struct timeval stop_time, start_time;

	//count = 1; // 2 is prime. Our loop starts from 3

        count = 0;

	if (rank==0) gettimeofday(&start_time, NULL);


        int chunksize = N/size; 
        int start;
        
        if (rank==0){
            start = 3;
        }
        else{
            start = rank*chunksize;
        } 

        int end = start + chunksize;
        if (rank == size-1) end=N;

 
//	for(i=3; i<N; i++)
//	{
//	    flag = 0;
//	    for(j=2; j<i; j++)
//	      {
//		 if((i%j) == 0)
//		 {
//		    flag = 1;
//		    break;
//		 }
//	      }
//
//            if(flag == 0)
//              {
//            	count++;
//              }
//	}


	for(i=start; i<end; i++)
	{
	    flag = 0;
	    for(j=2; j<i; j++)
	      {
                 if((i%j) == 0)
		 {
		    flag = 1;
		    break;
		 }
	      }

            if(flag == 0)
              {
            	count++;
              }
	}


        int finalcount = 0;
        MPI_Reduce(&count, &finalcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        printf("process = %d, count = %d \n",rank, count);

        if (rank == 0){
         	gettimeofday(&stop_time, NULL);

        	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));

	        printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", finalcount, exe_time);
        }

        MPI_Finalize();
        return 0;
}
