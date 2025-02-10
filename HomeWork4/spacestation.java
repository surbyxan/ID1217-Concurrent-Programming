package HomeWork4;
import java.util.Random;
/* a long time ago in a galaxy far far away */
/* the death star is refueling TIE-figheters */
import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.random.*;

//! gör en ny fil med trådarna och en ny fil som requestar main

public class spacestation {
	

	Random rnd = new Random();
	//MONITOR
	/*
	vi har:
	N fuel för space station
	Q fuel -::-
	
	
	private void refuel(thread TIEfighter){
		if(Q <= 0 || N <= 0){
            cancel thread and start refuel ship thread
        }
        if(tiefighter.Nfuelrequest > N || tiefighter.Qfuelrequest > Q){
            låt en annan tie fighter refuel 
        }
        thread.sleep(random);
        tiefighter.Nfuel = tiefighter.Nfuel + tiefighterNfuelrequest;
        tiefighter.Qfuel = tiefighter.Qfuel + tiefighterQfuelrequest;
	}

	en metod att fylla på varsin fuel (trådar)
	om fuel är tomt, pause refuel och ta in refuel ship
	så ex om vi ökar en tie fighter med 10 N och 5 Q måste vi ta bort
	samma mängd från fuel på death star

	en metod för att fylla på med bränsle på stationen



	*/ 


	//Processer (trådarna(TIE-fighers)) 
	/*
	skapa tråd
	skapa metod för refuel beteedende
	refuel (vänta random tid)
	skapa metod för TIE-fighter beteende
	va i rymden i rnd tid


	*/

}