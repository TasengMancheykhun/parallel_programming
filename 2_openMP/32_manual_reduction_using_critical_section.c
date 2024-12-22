// Use case of critical section
// Manual Reduction, using critical section
// save storage, sacrificing time by using critical section
// large data N > 100000 

#include<stdio.h>
#include<omp.h>
#define N 10000000      //max value of int
#define T 13

int main(){
  long long sum=0;          // reduced storage by not creating array here
  int chunksize = N/T;

  #pragma omp parallel num_threads(T)	 
  {
      int tid = omp_get_thread_num();
      long long localsum=0;
      int start = tid*chunksize;
      int end = start + chunksize;
      
      if(tid == T-1) end = N;
      
      for (int i=start; i<end; i++) localsum += i+1;     // this can be parallelized, dont put
                                                         // this inside critical section. Putting
                                                        // inside critical section makes the code serial
                                                        // in that part/region

      // if this critical section was not put, every thread would try to put its 'localsum' value 
      // to the shared variable 'sum' giving race condition 
      
      // putting critical section makes the code slow, sacrifices time
    
      #pragma omp critical            // now 'localsum' will be added to 'sum', one thread                                
      {                               // after another, preventing race condition
        sum += localsum;
      }
  }


  printf("Total sum = %lld\n",sum);
  
  if (sum == (N*((N+1)*1L)/2)) printf("___Passed___\n");
  else printf("__Failed__\n");

  return 0;
} 