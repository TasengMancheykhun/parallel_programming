/// NOT POSSIBLE TO SOLVE..........

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define N 100

int main(){
    MPI_Init(NULL,NULL);
    int rank,size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int myid;
    int **m1, **m2, **sumMat;

    int chunksize = N/size;  
//    int start = rank*chunksize; 
//    int end = start + chunksize;
//    if (rank == size-1) end=N;

    if (rank == 0){
//        m1 = (int**)malloc(sizeof(int*) * N);
//        m2 = (int**)malloc(sizeof(int*) * N);
//        sumMat = (int**)malloc(sizeof(int*) * N);

        int m1[N][N];
        int m2[N][N];
        int sumMat[N][N];

        for(int i = 0; i < N; i++){
//            m1[i] = (int*)malloc(sizeof(int) * N);
//            m2[i] = (int*)malloc(sizeof(int) * N);
//            sumMat[i] = (int*)malloc(sizeof(int) * N);

            for(int j = 0; j < N; j++){
                m1[i][j] = 1;
                m2[i][j] = 1;
                sumMat[i][j] = 0;
            }
        }
    } 


    /*
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ",m1[i][j]);
        }
        printf("\n");
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ",m2[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < n; i++){
        sumMat[i] = (int*)malloc(sizeof(int) * n);
        for(j = 0; j < n; j++){
            sumMat[i][j] = m1[i][j] + m2[i][j];
        }
    }
*/


  int sm1[chunksize][N];
//  int** sm1 = (int**)malloc(sizeof(int*)*chunksize);
//  for (int i=0; i<chunksize; i++){
//    sm1[i] = (int*)malloc(sizeof(int)*N);
//  }
  
  MPI_Scatter(m1, chunksize*N, MPI_INT, sm1, chunksize*N, MPI_INT, 0, MPI_COMM_WORLD);
 
  int sm2[chunksize][N];
//  int** sm2 = (int**)malloc(sizeof(int*)*chunksize);
//  for (int i=0; i<chunksize; i++){
//    sm2[i] = (int*)malloc(sizeof(int)*N);
//  }
  
  MPI_Scatter(m2, chunksize*N, MPI_INT, sm2, chunksize*N, MPI_INT, 0, MPI_COMM_WORLD);


   int s_sumMat[chunksize][N];
//  int** s_sumMat = (int**)malloc(sizeof(int*)*chunksize);
//  for (int i=0; i<chunksize; i++){
//    s_sumMat[i] = (int*)malloc(sizeof(int)*N);
//  }

  for (int i = 0; i<chunksize; i++){
      for (int j = 0; j<N; i++){
          s_sumMat[i][j] = sm1[i][j] + sm2[i][j];
      }
  }
  

  MPI_Gather(s_sumMat, chunksize*N, MPI_INT, sumMat, N, MPI_INT, 0, MPI_COMM_WORLD);


  if (rank == 0){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",sumMat[i][j]);
        }
        printf("\n");
    }

    for (int i=0; i<N; i++) free(sumMat[i]);
    free(sumMat);
 
  }


  MPI_Finalize();

   
//  for (int i=0; i<chunksize; i++) free(s_sumMat[i]);
//  free(s_sumMat);
// 
//  for (int i=0; i<chunksize; i++) free(sm1[i]);
//  free(sm1);
//
//  for (int i=0; i<chunksize; i++) free(sm2[i]);
//  free(sm2);


  return 0;
}
