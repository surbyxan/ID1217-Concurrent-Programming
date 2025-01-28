#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4  // You can adjust this as needed

// Structure to hold arguments for each quicksort task
typedef struct {
    int start;
    int end;
    int* arr;
} QuickSortArgs;

// Function to perform the partition operation
int partition(int start, int end, int* arr) {
    int i = start;
    int j = end;
    
    // Decide random pivot
    int pivot = rand() % (j - i + 1) + i;

    // Swap the pivot with end element of array
    int temp = arr[end];
    arr[end] = arr[pivot];
    arr[pivot] = temp;

    j--; // Now j is one less than the last element

    // Partition the array
    while (i <= j) {
        if (arr[i] <= arr[end]) {
            i++;
            continue;
        }
        if (arr[j] >= arr[end]) {
            j--;
            continue;
        }
        
        // Swap elements at i and j
        temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
        
        j--;
        i++;
    }

    // Swap pivot element to its correct position
    temp = arr[j + 1];
    arr[j + 1] = arr[end];
    arr[end] = temp;

    return j + 1;
}

// QuickSort function to be called recursively
void* quickSort(void* args) {
    QuickSortArgs* qs_args = (QuickSortArgs*)args;
    int start = qs_args->start;
    int end = qs_args->end;
    int* arr = qs_args->arr;

    if (start >= end) {
        pthread_exit(NULL);  // Base case: when start >= end
    }

    // Partitioning the array and getting pivot index
    int pivotIndex = partition(start, end, arr);

    // Create arguments for the left and right subproblems
    QuickSortArgs leftArgs = {start, pivotIndex - 1, arr};
    QuickSortArgs rightArgs = {pivotIndex + 1, end, arr};

    // Create threads for the left and right subproblems
    pthread_t leftThread, rightThread;

    // Create thread for the left partition
    if (start < pivotIndex - 1) {
        pthread_create(&leftThread, NULL, quickSort, (void*)&leftArgs);
    }

    // Create thread for the right partition
    if (pivotIndex + 1 < end) {
        pthread_create(&rightThread, NULL, quickSort, (void*)&rightArgs);
    }

    // Wait for threads to finish
    if (start < pivotIndex - 1) {
        pthread_join(leftThread, NULL);
    }
    if (pivotIndex + 1 < end) {
        pthread_join(rightThread, NULL);
    }

    pthread_exit(NULL);
}

int main() {
    int n = 7;
    int arr[] = {54, 64, 95, 82, 12, 32, 63};

    srand(time(NULL));

    // Prepare arguments for the quicksort call
    QuickSortArgs args = {0, n - 1, arr};

    // Start the quicksort thread
    pthread_t mainThread;
    pthread_create(&mainThread, NULL, quickSort, (void*)&args);

    // Wait for the main thread to finish
    pthread_join(mainThread, NULL);

    // Print sorted array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
