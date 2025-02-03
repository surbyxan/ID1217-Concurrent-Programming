//to compile and execute
// usage with gcc (version 4.2 or higher required):
// gcc -O -fopenmp -o matrixSum-openmp matrixSum-openmp.c
// gcc -O -fopenmp -o matrixSum matrixSum.c
// gcc -O -fopenmp -o palindrome palindrome.c
// ./matrixSum-openmp size numWorkers

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h> 
#include <ctype.h>

#define MAXWORKERS 4  /* maximum number of workers */

//new array for all the palindrome words and reverse words
char *palin[25143];

//compare function for the binary search
int comfunc(const void* a, const void* b) {
   return strcmp(*(const char**)a, *(const char**)b);
}

//String reverse from stackoverflow because strrev doesnt exist on linux
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

//read from file method 
char **readfromfile(){
    
    FILE *file_ptr;
    int idx = 0;

    struct stat st;
    stat("words", &st);
    int size = st.st_size;

    char **arr1 = (char **)malloc(size * sizeof(char*));
    char str[100];

    file_ptr = fopen("words", "r");

    if (NULL == file_ptr) {
        printf("File can't be opened \n");
        return 0;
    }

    while (fgets(str, sizeof(str), file_ptr) != NULL) {
    //Remove the newline character if present
    str[strcspn(str, "\n")] = 0;

    //Allocate memory and store the word in arr1
    if (strlen(str) > 0) {
        for(int i = 0; i < strlen(str); i++){
            if((int) 'A' <= (int) str[i] && (int) str[i] <= (int) 'Z' ){
                str[i] =(char) ((int) str[i] + 32);
            }
        }
        arr1[idx] = strdup(str);  //Copy the word to arr1[idx]
        if (arr1[idx] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1); 
        }
        idx++;
    }
}

    fclose(file_ptr);
    
    return arr1;
}

// antingen palindrom eler ett nytt ord om vänt
//spara dessa ord i en ny global array


int main(int argc, char *argv[]){

    int numWorkers;


    /* read command line args if any */
    numWorkers = (argc > 1)? atoi(argv[1]) : MAXWORKERS;
    if (numWorkers > MAXWORKERS) numWorkers = MAXWORKERS;
    
    //setup for parallel work
    char **arr1; 
    arr1 = readfromfile();
	omp_set_num_threads(numWorkers);
    double time = 0;


    //for(int i = 0; i < 104334; i++){
    //    if(arr1[i]==NULL){
    //        break;
    //    }
    //    printf("%s\n", arr1[i]);
    //}
    //printf("done\n");



    //parallel work
    int totalWords = 25143;
    int j = 0;

    
    double t1 = omp_get_wtime();
    #pragma omp parallel shared(palin, j)
    {
        int threadId = omp_get_thread_num();
        //printf("Thread nr: %d", threadId);
 
        char* strcopy;
        #pragma omp for
        for(int i = 0; i < totalWords; i++){
            //we make a copy of the current word we are comparing
            strcopy = strdup(arr1[i]);
            //we reverse to the copy to not modify the original array
            if(arr1[i] == strrev(strcopy)){
                #pragma omp critical
                {
                palin[j] = arr1[i];
                j++;
                }
                //add to our global array and put "lock" on it
            }
            else{
                   const char** item;
                    item = (const char**)bsearch(&strcopy, arr1, totalWords, sizeof(const char*), comfunc);
                    //binary search gives !NULL output when it is a match
                    if(item != NULL){
                        #pragma omp critical
                        {   //Critical section for adding words in the global array
                        palin[j] = strrev(strcopy);     //we reverse again because the copy was reversed in the first if statement
                        j++;
                        }
                    }
    
            }
        }

        free(strcopy); 
    }
    double t2 = omp_get_wtime();
    time = t2 - t1;

    /* Printing method for checking the output
    for(int i = 0; i < 25143; i++){
        if(palin[i] == NULL)
            break;
       printf("%s\n", palin[i]);
    }*/
   printf("TIME: %f for n-cores: %d\n", time, numWorkers);

    FILE *fptr; //Putting the palin array in a new file 
    
    fptr = fopen("output.txt", "w");

    if(fptr == NULL){
        printf("error");
    }

    for(int i = 0; i < totalWords; i++){
        if(palin[i] == NULL)
            break;
        fputs(palin[i], fptr);
        fputs("\n", fptr);
    }

    free(arr1);
    //free(palin);
    
    return 0;
}


//1 thread 0.0080602
//2 thread 0.0078528
//3 thread 0.0087062
//4 thread 0.01991


//STOR ARRAY
//1 thread 0.018505
//2 thread 0.0126454
//3 thread 0.0102788
//4 thread 0.0076314
//8 thread

//50k element
//1 thread 0.0085662
//2 thread 0.0062246 
//3 thread 0.0041218
//4 thread 0.0053752