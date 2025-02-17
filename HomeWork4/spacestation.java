package HomeWork4;
import java.util.Random;
/* a long time ago in a galaxy far far away */
/* the death star is refueling TIE-figheters */
import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.Random.*;

//! monitorn (death star)

public class spacestation {
	
	/* 
		En monitor för att hålla koll på bränslet i death star och TIE-fighters
		och för att fylla på bränsle i TIE-fighters och i death star
	*/

	Random rnd = new Random();
	int Qmax;
	int Nfuel;
	int Nmax;
	int Qfuel;
	int ports;

	public spacestation(int Nmax, int Qmax, int ports){
		this.Nmax = Nmax;
		this.Qmax = Qmax;
		this.Nfuel = Nmax;
		this.Qfuel = Qmax;
		this.ports = ports;
	}
	

	public synchronized int refuelN(int id, int requestN, int currN){//metod för att tanka som vanligt
        if(requestN > Nfuel ){
			try {
                wait();
            } catch(InterruptedException e) {
                System.out.println("TIE-fighter " + id + " was interrupted");
            }
        }
		//int refuelTime = rnd.nextint(10);

        currN = currN + requestN;
		Nfuel = Nfuel - requestN;

       return currN;
	}


	public synchronized int refuelQ(int id, int requestQ, int currQ){//metod för att tanka som vanligt
        while(requestQ > Qfuel){
            //låt en annan tie fighter refuel 
			try {
                wait();
            } catch(InterruptedException e) {
                System.out.println("TIE-fighter " + id + " was interrupted");
            }
        }
		//int refuelTime = rnd.nextint(10);

        currQ = currQ + requestQ;
		Qfuel = Qfuel - requestQ;

	   return currQ;
	}

	public synchronized void filltank(int id, int tankSizeQ, int tankSizeN){ //metod för att fylla på tanken med bränsle (spacestation)
		if(Nmax - Nfuel > fueler.Nfuel && fueler.Nfuel != 0){
			//filltank
		}
		else if(Qmax - QFuel > fueler.Qfuel && fueler.Nfuel != 0){
			//filltank
		}
		else{
			//wait for space in tank
		}
	}

	/*
	en metod att fylla på varsin fuel (trådar)
	om fuel är tomt, pause refuel och ta in refuel ship
	så ex om vi ökar en tie fighter med 10 N och 5 Q måste vi ta bort
	samma mängd från fuel på death star

	en metod för att fylla på med bränsle på stationen



	*/ 


	

}