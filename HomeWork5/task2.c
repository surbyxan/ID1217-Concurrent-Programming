// mpicc -o task2 task2.c

// ./
//mpiexec -np 2 task2
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>

#define TEACHER 0


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
        printf("Teacher: partner up boy %d", randomNum);
        //MPI_Send(&randomNum, 1, MPI_INT, randomNum, 1, MPI_COMM_WORLD);
        //random id på studenty
        //int studentid = rand(1-n)


        //skickar you're it till den.
        
	}
    else{//! STUDENT 
        //hitta kompisar!!!!
        int tag = 0;
        if(randomNum == Id){
            if(Id == 1){
                MPI_Recv(&Id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                partner = nofstudents;
                printf("Hej %d vill du vara min kompis?\n", partner);
                printf("kram! från %d ", Id);
                tag = 1;
                MPI_Send(&nofstudents, 1, MPI_INT, nofstudents - 1, tag, MPI_COMM_WORLD);
            }
            else{
                MPI_Recv(&Id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                partner = Id - 1;
                printf("Hej %d vill du vara min kompis?\n", partner);
                printf("kram! från %d ", Id);
                tag = 1;
                int partner_id = (Id - 1);
                MPI_Send(&partner_id, 1, MPI_INT, partner_id, tag , MPI_COMM_WORLD);
            }
        }
        
        //MPI_Recv(&Id, 1, MPI_INT, Id + 1, tag, MPI_COMM_WORLD, &status);
        if(Id == nofstudents){
            MPI_Recv(&Id, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
        }
       
        
        if(status.MPI_TAG == 0){
            printf("hej! vill du vara min kompis?2\n");
            partner = Id - 1;
            tag = 1;
            int partner_id = Id - 1;
            MPI_Send(&partner_id, 1, MPI_INT, partner_id,tag, MPI_COMM_WORLD);
            printf("Hi, I'm %d and my partner is %d\n", Id, partner);
        }
        if(status.MPI_TAG == 1){
            //recevie va 1 alltså va kompisen uppdagen :(
            printf("hej! vill du vara min kompis?");
            partner = Id + 1;
            tag = 0;
            printf("Nej wtf du är ful och äcklig?!");
            int partner_id = Id - 1;
            MPI_Send(&partner_id, 1, MPI_INT, partner_id,tag, MPI_COMM_WORLD);
        }
                
       
        //den tar sin polare till vänster och blir kompis
        //om till vänster är lärare, hoppa tillslutet.
        //om till vänster är kompis, hoppa till vänster igen.
        //om till vänster är upptagen så är du ensam.
        //MPI_int = 0; (0 ingen kompis 1 kompis)
        //skicka en 1 till din kompis och 0 till den du hatar

        if(randomNum == 1){
            
        }
    }	
	
    MPI_Finalize();
    return 0;
}