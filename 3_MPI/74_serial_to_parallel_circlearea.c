#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#include<sys/time.h>
#define N 999999999

int main()
{
    	int i, j;
	double area, pi;
	double dx, y, x;
	double exe_time;
	struct timeval stop_time, start_time;

	dx = 1.0/N;
	x = 0.0;
	area = 0.0;

        MPI_Init(NULL,NULL);
        int rank, size;  

        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
        int chunksize = N/size;


//        for(i=0; i<N; i++){
//            x = i*dx;
//            y = sqrt(1-x*x);
//            area += y*dx;
//        }

        int start = rank*chunksize;      
        int end = start + chunksize; 
        
        if (rank == size-1) end=N; 


        if (rank==0) gettimeofday(&start_time, NULL);

        int localsum=0;
        for(int i=start; i<end; i++){
            x = i*dx;
            y = sqrt(1-x*x);
            localsum += y*dx;
        }

        MPI_Reduce(&localsum, &area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0){ 
            gettimeofday(&stop_time, NULL);
      
            exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
      
            pi = 4.0*area;
      
            printf("\n Value of pi is = %.16lf\n Execution time is = %lf seconds\n", pi, exe_time);
        }      
        
        MPI_Finalize();
  
        return 0;
}
