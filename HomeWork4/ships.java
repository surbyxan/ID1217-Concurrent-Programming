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
		//tanka
	public void setFuelN(int fuel){
		currN = currN + fuel;
	}

	public void setFuelQ(int fuel){
		currQ = currQ + fuel;
	}
		//bränsle mätare
	public int getFuelN(){
		return currN;
	}

	public int getFuelQ(){
		return currQ;
	}

	public int requestN(){
		return tankSizeN - currN;
	}

	public int requestQ(){
		return tankSizeQ - currQ;
	}
	
	public int getID(){
		return id;
	}
		
	
	//skapa tråd
	public void run(){
		System.out.println("TIE-fighter " + id + " is in space with " + tankSizeN + " N and " + tankSizeQ + " Q");

		Random rnd = new Random();
		int sleepTime = rnd.nextInt(10000) + 1000;

		while(true){

			switch(id){
				case 0:
					while(true){
						try{
							Thread.sleep(sleepTime);
						}
						catch(InterruptedException e){
							System.out.println("TIE-fighter " + id + " was interrupted");
						}
						if(deathstar.getQFuelSpaceStation() < tankSizeQ - 50){
							deathstar.fillQTank(this);
							System.out.println("The Death Star gets more Qfuel supplied to end the rebellion");
						}
						break;
					}
					break;
				case 1:
					while(true){
						try{
							Thread.sleep(sleepTime);
						}
						catch(InterruptedException e){
							System.out.println("TIE-fighter " + id + " was interrupted");
						}
						if(deathstar.getNFuelSpaceStation() < tankSizeN - 50){
							deathstar.fillNTank(this);
							System.out.println("The Death Star gets more Nfuel supplied to end the rebellion");
						}
						break;
					}
					break;
				default:
					while(true){
						try{
							currN = currN - rnd.nextInt(100);
							currQ = currQ - rnd.nextInt(100);

							if(currN < 0){
								currN = 0;
							}
							if(currQ < 0){
								currQ = 0;
							}
							
							Thread.sleep(sleepTime);
						}
						catch(InterruptedException e){
							System.out.println("TIE-fighter " + id + " was interrupted");
						}
						if(currN < tankSizeN){
							deathstar.refuelN(this);

						}
						if (currQ < tankSizeQ){
							deathstar.refuelQ(this); 
						}
						break;	
					}	
					break;
			}
		}
	}
}
