#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include <errno.h> // http://man7.org/linux/man-pages/man3/errno.3.html

#define ERROR_MIN_MORE_MAX_VALUE "Min value is more max value, returned 0"

//quicksort algorithm and random array taken from stackoverflow

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

void swap(int* a, int* b);

// Partition function
int partition(int arr[], int low, int high) {
    
    // Choose the pivot
    int pivot = arr[high];
    
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
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


    int arr[100000];
    int n = sizeof(arr) / sizeof(arr[0]);

    random_int_array(arr, 100000, 0, 100000);
    double start_time = read_timer();


    quickSort(arr, 0, n - 1);

    double end_time = read_timer();

    /*
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }*/

    printf("\nTime taken: %f seconds\n", end_time - start_time);

    
    return 0;
}