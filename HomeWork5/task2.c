// mpicc -o task2 task2.c
//mpiexec -np 2 task2
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>

#define TEACHER 0

#define TAG_SINGLE 1
#define TAG_TAKEN 2


//a true random generating method taken from internetz
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char *argv[]){
    int Id, partner, nofstudents;

    //true random generating method taken from internetz
    srand(time(NULL)); // Seed the random number generator
    //int randomNum = getRandomNumber(1, nofstudents);
    
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &Id );
	MPI_Comm_size(MPI_COMM_WORLD, &nofstudents);
    MPI_Status status;
    
    int randomNum = 3;

	//! TEACHER
    if(Id == TEACHER){
        printf("Teacher: partner up boy %d\n", randomNum);
        fflush(stdout);
        MPI_Send(&randomNum, 1, MPI_INT, randomNum, TAG_SINGLE, MPI_COMM_WORLD);
        //random id på studenty
        //int studentid = rand(1-n)


        //skickar you're it till den.
        
	}
    else{//! STUDENT 
        //hitta kompisar!!!!
        int recieved_ID;
        
        MPI_Recv(&recieved_ID, 1, MPI_INT, MPI_ANY_SOURCE, TAG_SINGLE, MPI_COMM_WORLD, &status);
        if(Id == randomNum){
            //recieve
            if(Id == 1){
                int partner = nofstudents;
                
            }
            else{//first case
                int partner = randomNum - 1;
                printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                fflush(stdout);

                MPI_Send(&partner, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
            }
        }
        else{
            int flag;

            if(status.MPI_TAG == 1){ //är denna process taken
                printf("meow");
                //MPI_Recv(&recieved_ID, 1, MPI_INT, MPI_ANY_SOURCE, TAG_TAKEN, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(recieved_ID == 1 || randomNum != nofstudents){
                    int partner =  recieved_ID + 1;
                    int sent_ID = nofstudents;
                    printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                    fflush(stdout);

                    MPI_Send(&sent_ID, 1, MPI_INT,sent_ID, TAG_SINGLE, MPI_COMM_WORLD);
                }
                else if(randomNum != recieved_ID - 1){
                    int partner = recieved_ID + 1;
                    int sent_ID = recieved_ID - 1;
                    printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                    fflush(stdout);

                    MPI_Send(&sent_ID, 1, MPI_INT,sent_ID, TAG_SINGLE, MPI_COMM_WORLD);
                    
                }
                else{
                    printf("meow");
                }
            }
            else{
                printf("meow");

                //MPI_Recv(&recieved_ID, 1, MPI_INT, MPI_ANY_SOURCE, TAG_SINGLE, MPI_COMM_WORLD, &status);
                if(recieved_ID == 1 || randomNum != nofstudents){
                    int partner =  recieved_ID + 1;
                    int sent_ID = nofstudents;
                    MPI_Send(&sent_ID, 1, MPI_INT,sent_ID, TAG_TAKEN, MPI_COMM_WORLD);
                }
                else if(randomNum != recieved_ID - 1){//vanliga case
                    int partner = recieved_ID + 1;
                    int sent_ID = recieved_ID - 1;
                    MPI_Send(&sent_ID, 1, MPI_INT,sent_ID, TAG_TAKEN, MPI_COMM_WORLD);
                    
                }
                else{
                                        printf("meow2");

                }  
            }
            
        
            printf("Hi I'm %d and my partner is %d\n", Id, partner);
            fflush(stdout);
        }	
    }
	
    MPI_Finalize();
    return 0;

}