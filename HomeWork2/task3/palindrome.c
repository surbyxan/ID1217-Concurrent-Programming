//to compile and execute
// usage with gcc (version 4.2 or higher required):
// gcc -O -fopenmp -o matrixSum-openmp matrixSum-openmp.c
// gcc -O -fopenmp -o matrixSum matrixSum.c
// ./matrixSum-openmp size numWorkers

#include <omp.h>
double start_time, end_time;
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h> 
#include <ctype.h>

#define MAXSIZE 10000 /* maximum matrix size */
#define MAXWORKERS 8  /* maximum number of workers */

char *palin[25143];

int comfunc(const void* a, const void* b) {
   return strcmp(*(const char**)a, *(const char**)b);
}

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


char **readfromfile(){
    
    FILE *file_ptr;
    int idx = 0;

    struct stat st;
    stat("words", &st);
    int size = st.st_size;

    char **arr1 = (char **)malloc(size * sizeof(char*));
    char str[50];

    file_ptr = fopen("words", "r");

    if (NULL == file_ptr) {
        printf("File can't be opened \n");
        return 0;
    }

    while (fgets(str, sizeof(str), file_ptr) != NULL) {
    // Remove the newline character if present
    str[strcspn(str, "\n")] = 0;

    // Allocate memory and store the word in arr1
    if (strlen(str) > 0) {
        for(int i = 0; i < strlen(str); i++){
            if((int) 'A' <= (int) str[i] && (int) str[i] <= (int) 'Z' ){
                str[i] =(char) ((int) str[i] + 32);
            }
        }
        arr1[idx] = strdup(str);  // Copy the word to arr1[idx]
        if (arr1[idx] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);  // or handle it accordingly
        }
        idx++;
    }
}

    fclose(file_ptr);
    
    return arr1;
}

// antingen palindrom eler ett nytt ord om vänt
//spara dessa ord i en ny global array


int main(){
    

    char **arr1; // = (char **)malloc(size * sizeof(char*));
    arr1 = readfromfile();
	omp_set_num_threads(MAXWORKERS);

    //for(int i = 0; i < 25143; i++){
    //    printf("%s\n", arr1[i]);
    //}

    //dela upp arrayn i antalet threads
    int totalWords = 25143;
    int chunk = totalWords/MAXWORKERS;
    int j = 0;
    #pragma omp parallel shared(palin, j)
    {
        //int threadId = omp_get_thread_num();
        //int start = threadId*chunk;
        //int end = (threadId == MAXWORKERS - 1) ? totalWords : (start + chunk); 
        char* strcopy;
        #pragma omp for
        for(int i = 0; i < totalWords; i++){
            strcopy = strdup(arr1[i]);

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
                    //vi bryr oss bara om när item!= NULL
                    if(item != NULL){
                        #pragma omp critical
                        {
                        palin[j] = strrev(strcopy);
                        j++;
                        }
                    }
    
            }
        }
        free(strcopy); 
    }

    for(int i = 0; i < 25143; i++){
        if(palin[i] == NULL)
            break;
       printf("%s\n", palin[i]);
    }

    free(arr1);
   
	//!överför arrayen till en ny fil med enbart palindrom
    
    return 0;
}

