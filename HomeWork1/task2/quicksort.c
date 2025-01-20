#ifndef _REENTRANT 
#define _REENTRANT 
#endif 

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define MAXSIZE 10000  /* maximum matrix size */
#define MAXWORKERS 10   /* maximum number of workers */

//initialisera variabler för program

//gör en quicksort algoritm
		//quicksort gör trådar ist för att rekursivt kalla på sig självt

//worker metod som kallar på quicksort och joinar när det är färdigt sorterat

//gör en main metod
	//den ska printa ut resultat och göra arrayer som ska sorteras