// Here, I try to optimize the code I write before where whole array was being sent to each process
// In this code, the whole array created is sent chunksize part to other process
// local sum is calculated and sent to rank=0

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){


  MPI_Init(NULL, NULL);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int chunksize = N/size;
  int start=0, end=0;

  int rem = N%size;

  int* sarr;
  if (rank==size-1){
      sarr = (int*) malloc(sizeof(int)*(chunksize+rem));
  }
  else{
      sarr = (int*) malloc(sizeof(int)*chunksize); 
  }

  if(rank==0){
      int* arr = (int*) malloc(sizeof(int)*N);
      
      for(int i=0; i<N; i++){
          arr[i] = i+1;  
      } 

      for(int ii=1; ii<size; ii++){  
          start = ii*chunksize;
          end = start + chunksize; 
          if (ii == size-1) end=N;
          
          int count=0;
          for (int i=start; i<end; i++){
            sarr[count] = arr[i];
            count++;
          }
            

          if (rank==size-1){
              MPI_Send(sarr, chunksize+rem, MPI_INT, ii, 0, MPI_COMM_WORLD);      
          }
          else{
              MPI_Send(sarr, chunksize, MPI_INT, ii, 0, MPI_COMM_WORLD);      
          }
      }

//// For rank=0 localsum
//// -------------------------------------
//      int sum=0, localsum=0;
//      
//      start = rank*chunksize;
//      end = start + chunksize;
//      
//      for(int i=start; i<end; i++){
//         localsum += arr[i];
//      }
//      sum += localsum;
//// -------------------------------------
//      printf("localsum of process 0 = %d \n", localsum);
//
//
//      
//      for (int i=1; i<size; i++){      
//         localsum=0; 
//         MPI_Recv(&localsum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         
//         printf("localsum of process %d = %d \n",i, localsum);  
//
//         sum += localsum;
//      }
//    
//      printf("Total Sum: %d \n",sum);              
                               
      free(arr);
  }      
  else{
      if (rank==size-1){
          MPI_Recv(sarr, chunksize+rem, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      else{
          MPI_Recv(sarr, chunksize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }

     
//      int localsum = 0;
//
//      if (rank==size-1){
//          for(int i=0; i<(chunksize+rem); i++){
//              localsum += sarr[i];
//          }
//      }else{
//           for(int i=0; i<chunksize; i++){
//              localsum += sarr[i];
//          }      
//      }
//
//      MPI_Send(&localsum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
   
  MPI_Finalize();
  
  free(sarr);
  
  return 0;
}
