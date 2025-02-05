/*Terminate the program with ctrl + c*/
/*Compile and execute: */
//gcc thebearandbees.c -o thebearandbees
// ./thebearandbees
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

#define WORKERS 6 //cannot be less than 2
#define SHARED 1
#define H 50 //honey portions

sem_t serve; //full semaphore
sem_t eat; //empty semaphore

int honeypot = 0;

//Working bee function
void *bees(void *arg){
    int argInt = *(int*) arg;

    while(true){ 
        sem_wait(&eat); //den får den tomma semaphore
        printf("Bees %d: Nothings like a hard days of work, honey is my life\n Honey = %d\n", argInt, honeypot);
        honeypot += 3; //jobbar hårt och fyller på honey

        if(honeypot > H)
            honeypot = H;
        
        if(honeypot == H){
            printf("ʕ•ᴥ•ʔ: Nothings like a good nap! I hope there is some honey in that pot! :P\n");
            sem_post(&serve);
        } 
        else{
            sem_post(&eat);
            //printf("Bees: Im so tired, somebody else gotta work now\n"); //check if sleep works
            sleep(2);   
        }
    }
}

//hungry bear function
void *bear(){
    while(true){
        sem_wait(&serve);
        if(honeypot < 0)
            honeypot = 0;

        if(honeypot == 0){
            printf("ʕ•ᴥ•ʔ: zzZZzzzzzZZZzzzzZZZzzzZZZ \n");
            printf("Bees: WHAT!? The honey is gone!!!!! \n");
            sem_post(&eat);
        }
        else{
            honeypot -= 5;
            printf("ʕ•ᴥ•ʔ: SLURP SLURP I love honey\n honey left: %d\n", honeypot);
            sem_post(&serve);
        }
    }
}

int main(){
    int id[WORKERS-1];
    sem_init(&serve, SHARED, 1);
    sem_init(&eat, SHARED, 0);
    pthread_t theBeeCrew[WORKERS-1]; //beees
    pthread_t Bear; //the hungry bear

    for(int i=0;i < WORKERS-1;i++){
        id[i] = i;
	    pthread_create(&theBeeCrew[i], NULL, bees, (void *) &id[i]);
        //printf("created thread: %d\n", id[i]);
    }  
    
	pthread_create(&Bear,NULL,bear, NULL);
    

    for(int i = 0; i < WORKERS-1; i++){
    	pthread_join(theBeeCrew[i], NULL);
    }
    pthread_join(Bear, NULL);     
    return 0;
}