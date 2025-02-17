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

	public int getNFuelSpaceStation(){
		return Nfuel;
	}

	public int getQFuelSpaceStation(){
		return Qfuel;
	}
	

	public synchronized void refuelN(ships ship){//metod för att tanka som vanligt
        while(ship.requestN() > Nfuel || ports == 0){
			try {
                wait();
				System.out.println("|-o-| TIE-fighter waits for Nfuel, not enough fuel in Death Star");
            } catch(InterruptedException e) {
                System.out.println("|-o-| TIE-fighter " + ship.getID() + " was interrupted");
            }
				
        }
		//int refuelTime = rnd.nextint(10);
		ports--;
		//sleep
		System.out.println("|-o-| TIE-fighter " + ship.getID() +  " are refueling N, to crush the rebellion");
		Nfuel = Nfuel - ship.requestN();
        ship.setFuelN(ship.requestN());
		System.out.println("Nfuel: " + Nfuel);
		ports++;
		notifyAll();
	}


	public synchronized void refuelQ(ships ship){//metod för att tanka som vanligt
        while(ship.requestQ() > Qfuel || ports == 0){
            //låt en annan tie fighter refuel 
			try {
                wait();
				System.out.println("|-o-| TIE-fighter waits for Qfuel, not enough fuel in Death Star");
            } catch(InterruptedException e) {
                System.out.println("|-o-| TIE-fighter " + ship.getID() + " was interrupted");
            }
        }
		//int refuelTime = rnd.nextint(10);
		ports--;
		//sleep
		System.out.println("|-o-| TIE-fighter " + ship.getID() +  " are refueling Q, to crush the rebellion");
		Qfuel = Qfuel - ship.requestQ();
		ship.setFuelQ(ship.requestQ());
		System.out.println("Qfuel: " + Qfuel);
		ports++;
		notifyAll();
	}

	public synchronized void fillNTank(ships ship){ //metod för att fylla på tanken med bränsle (spacestation)
		while(Nmax - Nfuel < ship.getFuelN()){
			try {
                wait();
            } catch(InterruptedException e) {
                System.out.println("Refueler " + ship.getID() + " was interrupted");
            }
		}
		//int refuelTime = rnd.nextint(10);
		Nfuel = Nfuel + ship.getFuelN();
		notifyAll();
	}

	public synchronized void fillQTank(ships ship){
		while(Qmax - Qfuel < ship.getFuelQ()){
			try {
                wait();
            } catch(InterruptedException e) {
                System.out.println("Refueler " + ship.getID() + " was interrupted");
            }
		}
		//int refuelTime = rnd.nextint(10);
		Qfuel = Qfuel + ship.getFuelQ();
		notifyAll();
		}

	}

	/*
	en metod att fylla på varsin fuel (trådar)
	om fuel är tomt, pause refuel och ta in refuel ship
	så ex om vi ökar en tie fighter med 10 N och 5 Q måste vi ta bort
	samma mängd från fuel på death star

	en metod för att fylla på med bränsle på stationen



	*/ 


	

