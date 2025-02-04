/*Terminate the program with ctrl + c*/
/*Compile and execute: */
//gcc hungrybird.c -o hungrybird
// ./hungrybird
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

#define WORKERS 4 //cannot be less than 2
#define SHARED 1

sem_t serve; //full semaphore
sem_t eat; //empty semaphore
sem_t mutex; //waiting babies

int worms = 0;

//parent function
void *parent(){
    while(true){
    sem_wait(&eat); //den får den tomma semaphore
    for(int i = 0; i < 10; i++){
        printf("Parent: I hope my hard work is paying of! I love my baby birds.\n Worms = %d\n", worms);
        worms++; //jobbar hårt och fyller på worms
    }
    sem_post(&serve);
    }
}

//babybird function
void *babyBird(void *arg){
    int argInt = *(int*) arg;
    while(true){
    sem_wait(&serve);
        if(worms == 0){
            sem_post(&eat);
            printf("Baby %d : CHIRP CHIRP, I'M HUNGRY!!\n", argInt);
        }
        else{
            worms--;
            printf("Baby %d : nom nom eating worms\n worms left: %d\n", argInt, worms);
            sem_post(&serve);
            sleep(2);
        }
    }
}

int main(){
    int id[WORKERS - 1];
    sem_init(&serve, SHARED, 0);
    sem_init(&eat, SHARED, 1);
    pthread_t mommacrow; //parent
    pthread_t babies[WORKERS-1]; //babies

    pthread_create(&mommacrow, NULL, parent, NULL);
    
    for(int i=0;i < WORKERS-1;i++){
        id[i] = i;
        pthread_create(&babies[i],NULL,babyBird,(void *) &id[i]);
    }  

    pthread_join(mommacrow, NULL);
    for(int i = 0; i < WORKERS-1; i++){
        pthread_join(babies[i], NULL);     
    }
    return 0;
}