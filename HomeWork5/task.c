// mpicc -o myprog myprog.c
// ./
//mpiexec -np 2 task
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEACHER 0
#define students n

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    //MPI_MPI_COMM_WORLD MPI_COMM_WORLD;
	int Id, partner, nofstudents;
	bool lonely = true;//mefrfr
	MPI_Comm_rank(MPI_COMM_WORLD, &Id );
	MPI_Comm_size(MPI_COMM_WORLD, &nofstudents);
	//MPI_MPI_COMM_WORLD_somt(somth, &partner);

	//TEACHER
    if(Id == TEACHER){
        int screamingStudents[nofstudents - 1];
		int index = 0;
        printf(" partner up boy\n");
        //rbuf = some shit
		//Getting requests from students
        for(int i = 1; i < nofstudents; i++){
            MPI_Recv(&screamingStudents[index], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			index++;
        }
		//Paring students
        for(int i = 0; i < nofstudents - 1; i++){
			if(i == nofstudents - 2 && nofstudents%2 == 0){
                //this is the last student and it is forever alone :(
                MPI_Send(&screamingStudents[i], 1, MPI_INT, screamingStudents[i], 0, MPI_COMM_WORLD);
            } 
            else if(i % 2 == 0){
                MPI_Send(&screamingStudents[i], 1 , MPI_INT, screamingStudents[i++],0 , MPI_COMM_WORLD);//men den skickar id av i till i++
            }
            else if(i % 2 != 0){
                MPI_Send(&screamingStudents[i] , 1 ,MPI_INT, screamingStudents[i--], 0 , MPI_COMM_WORLD);//skickar id av i till i--
            }
	
            
        }
	}
    else{
        MPI_Send(&Id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&partner, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("HI, I'm %d and my partner is %d\n", Id, partner);

    }	
	
	//när ihopparningen är klar
    MPI_Finalize();
    return 0;
}