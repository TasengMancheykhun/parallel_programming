# Parallel Programming
## Pre*requisite: C programming

## Notes on Parallel Programming using pthreads, openMP and open MPI.

## Parallel Programming Concepts:
`
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

  * Last private variable clause:
    * #pragma omp parallel lastprivate(a) num_threads(T)

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

  * Matrix Addition using directive #pragma omp parallel for

  * #pragma omp critical -------------> [CONSTRUCT]

    * What is critical section in openMP?
      * In openMP, a critical section is a region of code created by the construct 'critical' where it creates a lock like feature where at a time, only one thread can enter and execute the task, and all other threads will wait until it finishes and unlocks.

    * Benifits of Critical Section
      * Thread Synchronization
      * Prevents race condition
      * Mutual Exclusive access
    
    * Disadvantage of Critical Section
      * Performance Impact: creates performance bottleneck because other threads are forced to wait        
  * #pragma omp master ----------------> [CONSTRUCT]

    * 'master' is a 'Work Sharing Construct' which creates a region where the code is only executed by the master thread, while other threads in this parallel region will skip this section/region of code.

    * Some use of Master region can be:
      * Initialize the data, say elements of an array.
      * Take input from users
      * To print output

    * There is no implicit barrier at the end of the master construct block. All other threads skips and moves forward and does not wait even if data is not initialized. 

  * #pragma omp single -----------------> [CONSTRUCT]

    * 'single' is also another 'Work Sharing Construct' which creates a region where the block of code is executed by only one thread that is free and others will skip it.

    * There is an 'implicit barrier' at the end of the single block that ensures that all threads reach the end of the block before proceeding. If you want to avoid this implicit barrier, we can use the 'nowait' clause

  * #pragma omp barrier ----------------> [CONSTRUCT]

    * 'barrier' is a construct that is used for synchronization of all threads in a parallel region. Barrier is a point where a thread waits untill all other threads have reached the barrier, ensuring that all threads are synchronized before they continue execution.
  
    * Use case of Barrier
      * Since 'master' has no implicit barrier, here we can use this explicit barrier, so that other threads wait for the master thread to initialize the data.     

  * Timing
    * double starttime = omp_get_wtime()

  * Scheduling
 
    * #pragma omp parallel for schedule(static, 3) num_threads(T)
      * Work sharing clause where the chunksize (3) amount of data is being sent to each thread  
      * Any remainder work is given in round robbin fashion back to thread 0

    * #pragma omp parallel for schedule(dynamic, 3) num_threads(T)
      * Work sharing clause where the chunksize (3) amount of data is being sent to the thread that becomes free at runtime
      * Communication overhead is present here
      * Helps in load balancing    

 
    * #pragma omp parallel for schedule(guided, 3) num_threads(T)

    
    * #pragma omp parallel for schedule(runtime) num_threads(T)
      * Using environment variable called 'OMP_SCHEDULE', which can be used to control the scheduling strategy and chunksize at runtime.
      
      * Eg: export OMP_SCHEDULE = "dynamic,3"
      * check: echo $OMP_SCHEDULE       
      * unset: unset OMP_SCHEDULE

    * #pragma omp parallel for schedule(auto)
      * System automatically selects the most appropriate scheduling strategy

 
  * Atomic function
     * Can do simple operations arithmetic like add,sub,mult
     * for add, must do -------> sum += i+1 
     * for sub, must do -------> sum -= i+1 
     * for must, must do -------> sum *= i+1 

     * Atomic function avoids Race condition
     * Faster than critical sections because:
       * No lock applied
       * No queue management 


## open MPI concepts:
  * MPI is a library for message passing or communication between nodes/cores to perform parallel programming in Distributed Memory Architecture
  * Distributed Memory Architecture vs Shared Memory Architecture
  * What is a process?
  * MPI_Initialize, MPI_Finalize
  * Difference between MPI_Abort(MPI_COMM_WORLD,1) vs MPI_Finalize()?
    * MPI_Abort ---> terminates a process
    * MPI_Finalize() ---> ends the MPI communication
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
 
  * MPI_Type_create_struct
  * Create student struct with data like name, PRN, age, email, etc and send from process 0 to process 1
  * MPI_Pack
  * MPI_Unpack
  * MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm)
  * MPI_Comm_group(MPI_COMM_WORLD, &world_group)
  * MPI_Group_incl()
  * MPI_Comm_create_group()
  * MPI Task Parallelism using manual groups and communicators




<br /> ------------------------------------------------- <br />
**Extra Topics**
* Dynamically allocate 2d Array
  
  * int** arr = (int**) malloc(sizeof(int*)*row); <br />
    for(int i=0; i<row; i++){  <br />
     arr[i] = (int*) malloc(sizeof(int)*col); <br /> 
    } <br />

    
    for(int i=0; i<row; i++){ <br />
      free(arr[i]);  <br />
    } <br />

    free(arr);
