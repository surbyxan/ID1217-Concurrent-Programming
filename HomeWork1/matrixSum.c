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
#define DEBUG


pthread_mutex_t barrier;  /* mutex lock for the barrier */
pthread_cond_t go;        /* condition variable for leaving */
int numWorkers;           /* number of workers */ 
int numArrived = 0;       /* number who have arrived */

struct extremeValues {
  int position[2];    //define the position of our extreme value, position[0] = place in first array, position[1] = place in second array
  int value;          //the value of the extreme value
}; 

/* a reusable counter barrier */
void Barrier() {
  pthread_mutex_lock(&barrier); 
  numArrived++;
  if (numArrived == numWorkers) {
    numArrived = 0;
    pthread_cond_broadcast(&go);
  } else
    pthread_cond_wait(&go, &barrier);
  pthread_mutex_unlock(&barrier);
}

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
int sums[MAXWORKERS]; /* partial sums */
int matrix[MAXSIZE][MAXSIZE]; /* matrix */

struct extremeValues* maxArray[MAXWORKERS];
struct extremeValues* minArray[MAXWORKERS];

void *Worker(void *);

/* read command line, initialize, and create threads */
int main(int argc, char *argv[]) {
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
  for (l = 0; l < numWorkers; l++)
    pthread_create(&workerid[l], &attr, Worker, (void *) l);
  pthread_exit(NULL);
}

/* Each worker sums the values in one strip of the matrix.
   After a barrier, worker(0) computes and prints the total */
void *Worker(void *arg) {
  long myid = (long) arg;
  int total, i, j, first, last;



  /* determine first and last rows of my strip */
  first = myid*stripSize;
  last = (myid == numWorkers - 1) ? (size - 1) : (first + stripSize - 1);


    struct extremeValues maxStruct, minStruct;
    struct extremeValues *max = &maxStruct;
    struct extremeValues *min = &minStruct;


// Initialize max and min to values from the matrix
max->value = matrix[first][0];
max->position[0] = first;
max->position[1] = 0;

min->value = matrix[first][0];
min->position[0] = first;
min->position[1] = 0;

total = 0; 

for (i = first; i <= last; i++){
    for (j = 0; j < size; j++){
        if (matrix[i][j] > max->value){ //checks current in matrix with the current max value
            max->value = matrix[i][j];
            max->position[0] = i;
            max->position[1] = j;
            //printf("Updated max: %d at [%d, %d] by thread id: %ld\n", 
            //       max->value, max->position[0], max->position[1], myid);
        }
        if (matrix[i][j] < min->value){ //checks current in matrix with the current min value
            min->value = matrix[i][j];
            min->position[0] = i;
            min->position[1] = j;
        }
        total += matrix[i][j];
        sums[myid] = total;

    }
}
    maxArray[myid] = max;
    minArray[myid] = min;
    
  
  Barrier();
  if (myid == 0) {
    total = 0;
    for (i = 0; i < numWorkers; i++){
      if (maxArray[i]->value > max->value) {//compares current value in max array with the saved max struct
        max->value = maxArray[i]->value;
        max->position[0] = maxArray[i]->position[0];
        max->position[1] = maxArray[i]->position[1];
      }
      if (minArray[i]->value < min->value) {//compares current value in min array with the saved min struct
        min->value = minArray[i]->value;
        min->position[0] = minArray[i]->position[0];
        min->position[1] = minArray[i]->position[1];
      }
    //gå igenom struct array för min och max och hitta min/max
      total += sums[i];
    }
    /* get end time */

    end_time = read_timer();
    /* print results */
    printf("The max value of the matrix is: %d\n", max->value );
    printf("at the postition: [%d,%d]\n", max->position[0], max->position[1]);
    printf("The min value of the matrix is: %d\n", min->value );
    printf("at the postition: [%d,%d]\n", min->position[0], min->position[1]);
    printf("The total is %d\n", total);
    printf("The execution time is %g sec\n", end_time - start_time);
  }
}
