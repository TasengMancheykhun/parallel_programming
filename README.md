# Parallel Programming
## Pre*requisite: C programming

## Notes on Parallel Programming using pthreads, openMP and open MPI.

## Parallel Programming Concepts:

  * Cluster Architecture?

  * HPC Architecture?

  * What is a process?
    * A process is an instance of a running program.

  * What is a thread?
    * In a process, multiple lightweight processes called threads can be created which will run simultaneously at the same time and work on differents parts of a process

  * What is concurrency?
    * Multiple threads running simultaneously but not at the same time by context switching

  * What is parallelization?
    * Multiple threads running simultaneously at the same time   

  * One thread runs in one core. PIDs of each thread running in different cores will be same because hey belong to same process.

  * What is shared memory architecture?
    * Architecture where multiple cores are connected and share a single memory is called shared memory architecture. pthreads and openMP are two techniques by which we can perform parallel programming in shared memory architecture. 

  * What is distributed memory architecture?
    * Architecture where in a cluster, multiple nodes are connected via a network is called distributed memory architecture. openMPI can be used to perform parallel programming in distributed memory architecture. 

  * What is Hybrid memory architecture?
    * Architecture that is a combination of both shared and distributed memory architecture is called Hybrid memory architecture.

  * What is race condition in parallel programming?
    * A situation where two or more threads attempt to modify a shared variable simultaneously

  * What are the challenges in Parallel Programming?
    * Synchronization
    * Race condition
    * Data loss
    * Load balancing

  * What are the two type of parallelism?
    * Data Paralelism
      * Data is divided to different threads but same operation is performed
    * Task Parallelism
      * Different threads are used to perform different tasks  

  * What is Fork-Join model?
      
  * 

## pthread concepts:
  * What is pthread?
    * Pthread is an extension of C which allows us to write parallel programs by creating multiple threads in a shared memory architecture
    * Pthread is short for POSIX thread

  *  

## openMP concepts:
  * What is openMP?
    * openMP is an extension of C to parallelize code in shared memory architecture using directives   
    * short for open Multi-Processing
    * 

  * omp_set_num_threads(T);
    * This is a openMP function or routine method to create threads 
    * This creates T number of threads 

  * Directive: They are instructions for compiler that directs/guides the compiler to do operations like parallelism in the program  

  * Directive----> #pragma omp parallel
    * creates a parallel region inside {...} and creates threads equal to number of cores available in the system

  * Directive----> #pragma omp parallel num_threads(T)
    * num_threads() is a clause method to create threads
    * This creates a parallel region and T number of threads that runs code inside {...}

  * omp_get_thread_num()
    * gives the thread number

  * shared variable clause: 
    * #pragma omp parallel shared(a) num_threads(T) 
    * varaiable 'a' is a shared variable in shared memory, available to all threads

  * private variable clause: 
    * #pragma omp parallel private(a) num_threads(T)

  * First private variable clause:
    * #pragma omp parallel firstprivate(a) num_threads(T)

  * default variable clause:
    * #pragma omp parallel default(none) shared(a) num_threads(T)
 
  * Constructs in openMP: They are programming structures that enable parallel execution.
    * Work sharing construct
      * for, single, master      
  
  * Manual Reduction
    * perform sum of natural numbers using manual reduction (i.e using chunksize, start, end. No using for construct)

  * Reduction Clause
    * #pragma omp parallel for reduction(+ : sum) num_threads(T)   
  
  * Measuring timings in openMP
    * starttime = omp_get_wtime()
    * endtime = omp_get_wtime()
    * elapsed_time = endtime-starttime

  * Error checking in openMP
    * ifdef _OPENMP
    * . . . .
    * endif

    * Code inside this will be ignored by gcc compiler when -fopenmp is not used during compilation and sun as normal code. The directive #pragma omp parallel is also ignored and the code runs serially.

  * Matrix Addition using #pragma omp parallel for 
 
 
## open MPI concepts:
  * MPI is a library for message passing or communication between nodes/cores to perform parallel programming in Distributed Memory Architecture
  * Distributed Memory Architecture vs Shared Memory Architecture
  * What is a process?
  * MPI_Initialize, MPI_Finalize
  * What is rank?
  * What is size?
  * Communicator: A group that contains processes that can communicate with each other. 
    * MPI_COMM_WORLD is the default communicator
  * MPI functions
    * MPI_Send
    * MPI_Recv
  * MPI Communication Types:
    * Point to point communication:
      * If communication happens directly between two processes or more
      * Eg: Communication using MPI_Send() 
      * Blocking communication, Non-blocking communication
      * Synchronous communication, Asynchronous communication 
    * Collective communication:  
      * If all processes are part of the communication
      * Eg: Communcation using Broadcast (MPI_Bcast)
  * *Point-to-point communication*
    * hh  
    * pp
  * *Collective communication*
  * Scatter:
    * MPI_Scatter      
  

  * MPI_Datatype
    * MPI_Type_contiguous
    * MPI_Type_vector
    * MPI_Type_indexed  
    * Mimick MPI_Type_indexed as MPI_Type_contiguous and MPI_Type_vector 




* Dynamically allocate 2d Array
  
  * int** arr = (int**) malloc(sizeof(int*)*row); <br />
    for(int i=0; i<row; i++){  <br />
     arr[i] = (int*) malloc(sizeof(int)*col); <br /> 
    } <br />

    
    for(int i=0; i<row; i++){ <br />
      free(arr[i]);  <br />
    } <br />

    free(arr);
