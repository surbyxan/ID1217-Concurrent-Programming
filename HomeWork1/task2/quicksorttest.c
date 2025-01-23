#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>


#include <errno.h> // http://man7.org/linux/man-pages/man3/errno.3.html

#define ERROR_MIN_MORE_MAX_VALUE "Min value is more max value, returned 0"


#define MAXWORKERS 10   /* maximum number of workers */

struct quicksort_args {
    int low;
    int high;
    int *arr;
};

double read_timer() {
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if (!initialized) {
        gettimeofday(&start, NULL);
        initialized = true;
    }
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

// Swap function
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function
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

// QuickSort function that uses threads
void *quickSort(void *arguments) {
    struct quicksort_args *args = (struct quicksort_args *)arguments;

    if (args->low < args->high) {
        int pi = partition(args->arr, args->low, args->high);

        // Creating separate arguments for low and high partitions
        struct quicksort_args low_args = {args->low, pi - 1, args->arr};
        struct quicksort_args high_args = {pi + 1, args->high, args->arr};

        pthread_t low_thread, high_thread;

        // Create threads for low and high partitions
        pthread_create(&low_thread, NULL, quickSort, &low_args);
        pthread_create(&high_thread, NULL, quickSort, &high_args);

        // Wait for both threads to finish
        pthread_join(low_thread, NULL);
        pthread_join(high_thread, NULL);
    }

    return NULL;
}


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

int main() {


    int arr[100];
    int n = sizeof(arr) / sizeof(arr[0]);

    // Create the initial quicksort arguments struct
    struct quicksort_args args = {0, n - 1, arr};
    random_int_array(arr, 100, 0, 3000);

    // Start timer
    double start_time = read_timer();

    // Create a thread to start the quicksort process
    pthread_t main_thread;
    pthread_create(&main_thread, NULL, quickSort, &args);
    pthread_join(main_thread, NULL);

    // End timer and print the result
    double end_time = read_timer();
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken: %f seconds\n", end_time - start_time);

    return 0;
}
