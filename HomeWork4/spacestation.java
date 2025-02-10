package HomeWork4;
import java.util.Random;
/* a long time ago in a galaxy far far away */
/* the death star is refueling TIE-figheters */
import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.random.*;

//! monitorn (death star)

public class spacestation {
	
	/* typ klar tror vi
	vi har:
	
	Random rnd = new Random();
	int Nmax = 500;
	int Qmax = 500;
	int Nfuel = Nmax;
	int Qfuel =	Qmax;


	
	synchronized public void refuel(thread TIEfighter){//metod för att tanka som vanligt
        if(tiefighter.Nfuelrequest > N || tiefighter.Qfuelrequest > Q){
            låt en annan tie fighter refuel 
        }
		int refuelTime = rnd.nextint(10);
        thread.sleep(random);
        tiefighter.Nfuel = tiefighter.Nfuel + tiefighterNfuelrequest;
		Nfuel = Nfuel - tiefighter.Nfuelrequest;
        tiefighter.Qfuel = tiefighter.Qfuel + tiefighterQfuelrequest;
		Qfuel = Qfuel - tiefighter.Qfuelrequest;
	}

	synchronized public void filltank(thread fueler){ //metod för att fylla på tanken med bränsle (spacestation)
		if(Nmax - Nfuel > fueler.Nfuel && fueler.Nfuel != 0){
			filltank
		}
		else if(Qmax - QFuel > fueler.Qfuel && fueler.Nfuel != 0){
			filltank
		}
		else{
			wait for space in tank
		}
	}

	en metod att fylla på varsin fuel (trådar)
	om fuel är tomt, pause refuel och ta in refuel ship
	så ex om vi ökar en tie fighter med 10 N och 5 Q måste vi ta bort
	samma mängd från fuel på death star

	en metod för att fylla på med bränsle på stationen



	*/ 


	

}