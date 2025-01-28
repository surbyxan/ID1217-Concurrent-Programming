#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include <errno.h> // http://man7.org/linux/man-pages/man3/errno.3.html
#define MAXWORKERS 10   /* maximum number of workers */
#define ERROR_MIN_MORE_MAX_VALUE "Min value is more max value, returned 0"


struct quicksort_args {
    int low;
    int high;
    int *arr;
};

pthread_mutex_t lock;
int numWorkers = 0;

void quickSort(void *);
void swap(int* a, int* b);



double read_timer() {//timer function
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

///////////////////////////fill array with random integers/////////////////////////////
// this code snippet is taken from stackoverflow
static int
random_integer(const int min, const int max) {
    if (max == min) return min;
    else if (min < max) return rand() % (max - min + 1) + min;

    // return 0 if min > max
    errno = EINVAL;
    perror(ERROR_MIN_MORE_MAX_VALUE);
    return 0;
}
/* 
    Fills an array with random integer values in a range
*/
static int
random_int_array(int array[], const size_t length, const int min, const int max){
    for (int i = 0; i < length; ++i) {
        array[i] = random_integer(min, max);
    }
    return 0;
}
///////////////////////////end of filling array with integers/////////////////////////////


int main() {
    int arr[100000]; //choose size of array
    int n = sizeof(arr) / sizeof(arr[0]);

    random_int_array(arr, 100000, 0, 100000); //(array we're working with, amount of elements, lowest random int, highest random int)

    //setting the parent arguments
    struct quicksort_args pargs = {0, 100, arr};
    
    pthread_mutex_init(&lock, NULL);

    //the whole sort function call, with the timer reads
    double start_time = read_timer();
    quickSort(&pargs);
    double end_time = read_timer();


    //printing the sorted array
    /*for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");*/

    printf("\nTime taken: %f seconds\n", end_time - start_time);

    pthread_mutex_destroy(&lock);
  
    return 0;
}

// Partition function taken from stackoverflow
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

//worker and sort function
void quickSort(void *arguments) {//creates new threads if possible, else continues on the current thread
    struct quicksort_args *args = (struct quicksort_args *) arguments;

    if( args->low < args->high ){

        int pi = partition(args->arr, args->low, args->high);

        pthread_mutex_lock(&lock);
                
        if(numWorkers < MAXWORKERS - 1){//if the threads are not busy
            numWorkers++;
            pthread_mutex_unlock(&lock);

            struct quicksort_args leftargs = {args->low, pi - 1, args->arr};
            
            pthread_t thread;

            //creating a new thread that "goes" left
            pthread_create(&thread, NULL, (void *) quickSort, &leftargs);
            struct quicksort_args rightargs = {pi + 1, args->high, args->arr};
            quickSort(&rightargs);

            pthread_join(thread, NULL);
        }
        else{//if all the threads are busy
            pthread_mutex_unlock(&lock);
            struct quicksort_args leftargs = {args->low, pi - 1, args->arr};
            struct quicksort_args rightargs = {pi + 1, args->high, args->arr};

            quickSort(&leftargs);
            quickSort(&rightargs);
        
        }
    }
}

//swap function
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
