/* matrix summation using pthreads

   features: uses a barrier; the Worker[0] computes
             the total sum from partial sums computed by Workers
             and prints the total sum to the standard output

   usage under Linux:
     gcc matrixSum.c -lpthread
     a.out size numWorkers

*/
#ifndef _REENTRANT 
#define _REENTRANT 
#endif 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define MAXSIZE 10000  /* maximum matrix size */
#define MAXWORKERS 10   /* maximum number of workers */
//#define DEBUG


pthread_mutex_t barrier;  /* mutex lock for the barrier */
pthread_cond_t go;        /* condition variable for leaving */
int numWorkers;           /* number of workers */ 
int numArrived = 0;       /* number who have arrived */

struct extremeValues {
  int position[2];    //define the position of our extreme value, position[0] = place in row array, position[1] = place in second array
  int value;          //the value of the extreme value
}; 

struct extremeValues* max;
struct extremeValues* min;

pthread_mutex_t mutex;
pthread_mutex_t mutexBagOfTasks;
int sum = 0;

int bagOfTasks = 0;


/* timer */
double read_timer() {
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }
    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

double start_time, end_time; /* start and end times */
int size, stripSize;  /* assume size is multiple of numWorkers */
int matrix[MAXSIZE][MAXSIZE]; /* matrix */

struct extremeValues* maxArray[MAXWORKERS];
struct extremeValues* minArray[MAXWORKERS];

void *Worker(void *);

/* read command line, initialize, and create threads */
int main(int argc, char *argv[]) {
  
  max = (struct extremeValues*) malloc(sizeof(struct extremeValues));
  min = (struct extremeValues*) malloc(sizeof(struct extremeValues));

  int i, j;
  long l; /* use long in case of a 64-bit system */
  pthread_attr_t attr;
  pthread_t workerid[MAXWORKERS];

  /* set global thread attributes */
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  /* initialize mutex and condition variable */
  pthread_mutex_init(&barrier, NULL);
  pthread_cond_init(&go, NULL);

  /* read command line args if any */
  size = (argc > 1)? atoi(argv[1]) : MAXSIZE;
  numWorkers = (argc > 2)? atoi(argv[2]) : MAXWORKERS;
  if (size > MAXSIZE) size = MAXSIZE;
  if (numWorkers > MAXWORKERS) numWorkers = MAXWORKERS;
  stripSize = size/numWorkers; //stripsize is 

  /* initialize the matrix */
  for (i = 0; i < size; i++) {
	  for (j = 0; j < size; j++) {
          matrix[i][j] = rand()%99;
	  }
  }

  /* print the matrix */
#ifdef DEBUG
  for (i = 0; i < size; i++) {
	  printf("[ ");
	  for (j = 0; j < size; j++) {
	    printf(" %d", matrix[i][j]);
	  }
	  printf(" ]\n");
  }
#endif

  /* do the parallel work: create the workers */
  start_time = read_timer();
  for (l = 0; l < numWorkers; l++){
    pthread_create(&workerid[l], &attr, Worker, (void *) l);
  }
//join the threads when they are done
  for (l = 0; l < numWorkers; l++) {
    pthread_join(workerid[l], NULL);
  }
  end_time = read_timer();

    // /* print results */
    printf("The max value of the matrix is: %d\n", max->value );
    printf("at the postition: [%d,%d]\n", max->position[0], max->position[1]);
    printf("The min value of the matrix is: %d\n", min->value );
    printf("at the postition: [%d,%d]\n", min->position[0], min->position[1]);
    printf("The total is %d\n", sum);
    printf("The execution time is %g sec\n", end_time - start_time);

  //free the global max and min
  free(min);
  free(max);
}

/* Each worker sums the values in one strip of the matrix.
   After a barrier, worker(0) computes and prints the total */
void *Worker(void *arg) {
  long myid = (long) arg;
  int total, j;
  int row;

  /* determine row and last rows of my strip */
  //row = myid*stripSize;
  //last = (myid == numWorkers - 1) ? (size - 1) : (row + stripSize - 1);

  //bag of tasks implementation
  //worker gets task from bag while(true)  
  // mutex på bag of task när dom får och uppdaterar
  //if bagoftasks>=sizeofmatrix break;
  // gör task (beräkningarna)
  // klar


 
//for i = row i<=last i++
//uppdatera max, min och addera till lokala sum
//ta mutex över global sum, min och max
//lägg lägg till lokal sum till global om man har kontroll
//kolla om min/max är större/mindre än nuvarande globala min/max
//släpp mutex

while(true){
  struct extremeValues* local_max = (struct extremeValues*) malloc(sizeof(struct extremeValues));
  struct extremeValues* local_min = (struct extremeValues*) malloc(sizeof(struct extremeValues));
  
  pthread_mutex_lock(&mutexBagOfTasks);
  row = bagOfTasks;
  bagOfTasks++;
  pthread_mutex_unlock(&mutexBagOfTasks);
  //printf("%d", row);

  if(row >= size){
    break;
  }
//trådarna gör beräkningarna lokalt, men det globala värdet uppdateras sekventiellt
// Initialize max and min to values from the matrix
  local_max->value = matrix[row][0];
  local_max->position[0] = row;
  local_max->position[1] = 0;

  local_min->value = matrix[row][0];
  local_min->position[0] = row;
  local_min->position[1] = 0;

  total = 0; 

  //do all the calculations in parallell
      for (j = 0; j < size; j++){
          if (matrix[row][j] > local_max->value){ //checks current in matrix with the current max value
              local_max->value = matrix[row][j];
              local_max->position[0] = row;
              local_max->position[1] = j;
          }
          if (matrix[row][j] < local_min->value){ //checks current in matrix with the current min value
              local_min->value = matrix[row][j];
              local_min->position[0] = row;
              local_min->position[1] = j;
          }
          total += matrix[row][j];
      }
  
    //take control of the global variables with mutex and then update them.
    pthread_mutex_lock(&mutex);
    sum = sum + total;

    if(local_max->value > max->value){
      max->value = local_max->value;
      max->position[0] = local_max->position[0];
      max->position[1] = local_max->position[1];
    }
    if(min->value >= local_min->value){
      min->value = local_min->value;
      min->position[0] = local_min->position[0];
      min->position[1] = local_min->position[1];
    }
    pthread_mutex_unlock(&mutex);
    //free the local variables
    free(local_max);
    free(local_min);
}
  //kill the thread
  pthread_exit(NULL);
}
