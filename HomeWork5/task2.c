// mpicc -o task2 task2.c

// ./
//mpiexec -np 2 task2
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define TEACHER 0

int main(int argc, char *argv[]){
	int Id, partner, nofstudents;
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &Id );
	MPI_Comm_size(MPI_COMM_WORLD, &nofstudents);
	

	//TEACHER
    if(Id == TEACHER){
        //random id på studenty
        //int studentid = rand(1-n)
        printf("partner up boy!");
        //skickar you're it till den.
        MPI_Send(&studentid, 1, MPI_INT, 1 , 0, MPI_COMM_WORLD);
	}
    else{//STUDENT 
        //hitta kompisar!!!!
        printf("hej! vill du vara min kompis?");
        //den tar sin polare till vänster och blir kompis
        //om till vänster är lärare, hoppa tillslutet.
        //om till vänster är kompis, hoppa till vänster igen.
        //om till vänster är upptagen så är du ensam.
        printf("Hi, I'm %d and my partner is %d\n", Id, partner);
    }	
	//ending the MPI process part
    MPI_Finalize();
    return 0;
}