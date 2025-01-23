#ifndef _REENTRANT 
#define _REENTRANT 
#endif 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
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
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }
    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

//quicksort alogritm

void *quickSort(void *);


int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    //pthread_attr_t attr;

    /* set global thread attributes */
    //pthread_attr_init(&attr);
    //pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    
    pthread_t workerid[MAXWORKERS];

    //struct quicksort_args *pargs;
    //!ändra malloc till rätt storlek sen
    struct quicksort_args *pargs = malloc(sizeof(struct quicksort_args) + 6 * sizeof(int));

    for (int i = 0; i < 6; i++) {
        pargs->arr[i] = arr[i];
    }
    pargs->low= 0;
    pargs->high= 6 - 1;
        


    //pargs->arr = arr;
    //printf("pargs low: %d\n", pargs->low);
    //printf("pargs high: %d\n", pargs->high);

    
    pthread_create(&workerid[0], NULL, quickSort, pargs);
        //pthread_exit(NULL);
    //quickSort(arr, 0, n - 1);
    pthread_join(workerid[0], NULL);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    return 0;
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

// The QuickSort function implementation (the worker function)
//(void * arguments)
void *quickSort(void *arguments) {
    printf("The passed arguments:\n");
    
    struct quicksort_args *args = (struct quicksort_args *)arguments;
    printf("low: %d, high: %d, thread_id: arr[]: \n", args->low, args->high);


    //printf("test\n");
    //printf("low %d high %d\n", args->high, args->low);
    
    if (args->low < args->high) {
        //printf("test1");
        // pi is the partition return index of pivot
        int pi = partition(args->arr, args->low, args->high);
        struct quicksort_args high_args = {args->low, pi - 1, args->arr};
        struct quicksort_args low_args = {pi + 1,args->high, args->arr};

        // Recursion calls for smaller elements
        // and greater or equals elements
		//när vi kallar på quicksort vi vi göra det med en thread     
        

         pthread_t low_thread, high_thread;

        // pthread_t tid;
        //&tid
        pthread_create(&low_thread, NULL, quickSort,  &low_args); 
        //printf("%p", &low_args->thread_id);
        //pthread_exit(NULL);       

        pthread_create(&high_thread, NULL, quickSort, &high_args); 
        //printf("%p", &high_args->thread_id);
        pthread_exit(NULL);
        pthread_join(low_thread, NULL);
        pthread_join(high_thread, NULL);

        //pthread_exit(NULL);
        //quickSort(arr, low, pi - 1);
        //quickSort(arr, pi + 1, high);

		//pthread_join()
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}


//initialisera variabler för program

//gör en quicksort algoritm
		//quicksort gör trådar ist för att rekursivt kalla på sig självt

//worker metod som kallar på quicksort och joinar när det är färdigt sorterat

//gör en main metod
	//den ska printa ut resultat och göra arrayer som ska sorteras