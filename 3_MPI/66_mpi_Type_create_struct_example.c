#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  char name[10];
  int prn;
  int age;
  char email[16];
  double salary;
  int marks[5];
} student;


int main(){

  MPI_Init(NULL,NULL);
  
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size < 2){
    fprintf(stderr, "World size must be greater than 1 for this example \n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  student data;
  MPI_Datatype struct_type;

  // Create the datatype for my struct
  int blocklengths[6] = {10, 1, 1, 50, 1, 5};
  MPI_Aint displacements[6];
  MPI_Datatype types[6] = {MPI_CHAR, MPI_INT, MPI_INT, MPI_CHAR, MPI_DOUBLE, MPI_INT};

  displacements[0] = offsetof(student, name);
  displacements[1] = offsetof(student, prn);
  displacements[2] = offsetof(student, age);
  displacements[3] = offsetof(student, email);
  displacements[4] = offsetof(student, salary);
  displacements[5] = offsetof(student, marks);
 
  MPI_Type_create_struct(6, blocklengths, displacements, types, &struct_type);
  MPI_Type_commit(&struct_type);

  if (rank == 0) {
    strcpy(data.name, "Taseng");
    data.prn = 1021;
    data.age = 25;
    strcpy(data.email, "taseng9@gmail.com");
    data.salary = 75000.0;
    data.marks[0] = 40; 
    data.marks[1] = 39; 
    data.marks[2] = 40; 
    data.marks[3] = 40; 
    data.marks[4] = 38; 
    
    MPI_Send(&data, 1, struct_type, 1, 0, MPI_COMM_WORLD);
    
    printf("Process 0 sent struct: {name = %s, prn = %d, age = %d, email = %s, salary = %.2f}\n", data.name, data.prn, data.age, data.email, data.salary);
    
    printf("Marks: \n");
    for(int i=0; i<5; i++){
      printf("%d ",data.marks[i]);
    } 
    printf("\n");

  } else if (rank == 1){
    MPI_Recv(&data, 1, struct_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

    printf("Process 1 received struct: {name = %s, prn = %d, age = %d, email = %s, salary = %.2f}\n", data.name, data.prn, data.age, data.email, data.salary);
    
    printf("Marks: \n");
    for(int i=0; i<5; i++){
      printf("%d ",data.marks[i]);
    } 
    printf("\n");
  }

  MPI_Type_free(&struct_type); 
  MPI_Finalize();
  return 0;
}
