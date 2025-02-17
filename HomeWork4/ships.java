package HomeWork4;

import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.Random;

//! TIE-fighters (processes)

public class ships extends Thread{
    int tankSizeQ;
    int tankSizeN;
	int currQ;
	int currN;
	int id;
	spacestation deathstar;


    public ships(spacestation deathstar, int tankSizeN, int tankSizeQ, int id){
        //N & Q differ if the constructor is used on the refueler ships,
        //otherwise if it is the tiefighters, they will be the same size.
        this.tankSizeN = tankSizeN; 
        this.tankSizeQ = tankSizeQ;
		this.currN = tankSizeN;
		this.currQ = tankSizeQ;
		this.id = id;
		this.deathstar = deathstar;
    }
	
	//Processer (trådarna(TIE-fighers)) 
	
	//skapa tråd
	public void run(){
		System.out.println("TIE-fighter " + id + " is in space with " + tankSizeN + " N and " + tankSizeQ + " Q");

		Random rnd = new Random();
		int sleepTime = rnd.nextInt(10000) + 1000;
		while(true){

			try{
				//TODO skeppet tappar random mängd fuel (sleeptime)
				Thread.sleep(sleepTime);
			}
			catch(InterruptedException e){
				System.out.println("TIE-fighter " + id + " was interrupted");
			}
			currN = deathstar.refuelN(id, tankSizeN, currN);
			currQ = deathstar.refuelQ(id, tankSizeQ, currQ);		}
		
	/*
		skapa metod för refuel beteedende // kalla på monitor (spacestation)
		refuel (vänta random tid)
		skapa metod för TIE-fighter beteende
			va i rymden i rnd tid
        tie.filltank(ships  )


		//todo här ska vi göra vår logik malin! :)
			/*
			 	att skeppen ska fyllas på med bränsle ifall de behöver det
				ship.refuel
					
				att skeppen ska sova i rymden i en random tid zzZZzzz
				att refueler-skeppen ska fylla på bränsle i death star

				while(true){
					när ett skepp behöver bränsle, kalla på refuel metoden i spacestation
					när det är tomt i en tank, kalla på filltank metoden i spacestation
						eller om en refueler har kommit till death star
				}
	*/
	}
	




}
