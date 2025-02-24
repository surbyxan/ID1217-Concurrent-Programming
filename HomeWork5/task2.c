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
/*
In this solution a teacher randomly selects a student to start the pairing. This student partners up with the student to the left.
It also tells the student to the left of the chosen student that it is thats student turn to find a partner. This continues in a 
circle until either a student tries to tell the original student that it is its partner, or that it is that ones turn to pick again. 
Since this is done in an array we loop around it with several if statements. If a student tries to partner up with the student to 
the left and it is the original chosen by the teacher, the student will partner up with itself.
*/


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
    
    int randomNum = getRandomNumber(1, nofstudents - 1);

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
        while(1){
            int recieved_ID;
            MPI_Recv(&recieved_ID, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            //checks if it is the first process called by teacher
            if(Id == randomNum){
                //first case (add case where id = 1 or 2)
                partner = randomNum - 1;
                int nextSearch = randomNum - 2;
                //checks the special case where we have to loop
                if(Id == 1){
                    partner = nofstudents - 1;
                    nextSearch = nofstudents - 2;
                }
                if(Id == 2 ){
                    partner = Id - 1;
                    nextSearch = nofstudents - 1;
                }               
                    printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                    fflush(stdout);

                    MPI_Send(&Id, 1, MPI_INT, partner, 2, MPI_COMM_WORLD);
                    MPI_Send(&Id, 1, MPI_INT, nextSearch, 1, MPI_COMM_WORLD);
                } else{ //all the other cases where the students are pairing themselves
                    //updates if a partner is found
                    if(status.MPI_TAG == 2 ){
                        //printf("yay jag %d har en kompis %d\n", Id, recieved_ID);
                        //fflush(stdout);                    
                        partner = recieved_ID;
                        if(Id - 1 == randomNum){
                            break;
                        }
                    }
                    //algorithm to find partner, and tell which student to look for a partner
                    if(status.MPI_TAG == 1){
                        if(Id == 1){
                            printf("åh %d va upptagen :/, undra om nån annan vill vara med mig %d?\n", recieved_ID, Id);
                            fflush(stdout);

                            partner =  nofstudents - 1;
                            int nextSearch = nofstudents - 2;
                            if(partner == randomNum){
                                partner = Id;
                            }
                            MPI_Send(&Id, 1, MPI_INT, partner, 2, MPI_COMM_WORLD);
                            printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                            fflush(stdout);
                            if(nextSearch == randomNum){
                                break;
                            }
                            MPI_Send(&Id, 1, MPI_INT, nextSearch, 1, MPI_COMM_WORLD);
                        }
                        else if(Id == 2){
                                printf("åh %d va upptagen :/, undra om nån annan vill vara med mig %d?\n", recieved_ID, Id);
                                fflush(stdout);
        
                                partner =  Id - 1;
                                int nextSearch = nofstudents - 1;
                                if(partner == randomNum){
                                    partner = Id;
                                }
                                MPI_Send(&Id, 1, MPI_INT, partner, 2, MPI_COMM_WORLD);
                                printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                                fflush(stdout);
                                if(nextSearch == randomNum){
                                    break;
                                }
                                
                                MPI_Send(&Id, 1, MPI_INT, nextSearch, 1, MPI_COMM_WORLD);
                        }
                        else{
                            printf("åh %d va upptagen :/, undra om nån annan vill vara med mig %d?\n", recieved_ID, Id);
                            fflush(stdout);
        
                            partner =  Id - 1;
                            int nextSearch = Id - 2;
                            if(partner == randomNum){
                                partner = Id;
                            }
                            MPI_Send(&Id, 1, MPI_INT, partner, 2, MPI_COMM_WORLD);
                            printf("Hi %d, do you want to be my partner? From %d\n", partner, Id);
                            fflush(stdout);

                            if(nextSearch == randomNum){
                                break;
                            }
                            
                                
                            MPI_Send(&Id, 1, MPI_INT, nextSearch, 1, MPI_COMM_WORLD);
                        }
                    }
                }
                break;
            }         
            printf("MEOW Hi I'm %d and my partner is %d\n", Id, partner);
            fflush(stdout);
        }	

    	
    MPI_Finalize();
    return 0;

}