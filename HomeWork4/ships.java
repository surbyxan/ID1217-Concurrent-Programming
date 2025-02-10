package HomeWork4;

import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.random.*;

//! TIE-fighters (processes)

public class ships {
    int tankSizeQ;
    int tankSizeN;


    public ships(int tankSizeQ, int tankSizeN){
        //N & Q differ if the constructor is used on the refueler ships,
        //otherwise if it is the tiefighters, they will be the same size.
        this.tankSizeN = tankSizeN; 
        this.tankSizeQ = tankSizeQ;
    }
	
	//Processer (trådarna(TIE-fighers)) 
	/*
	skapa tråd
	public void run(){
		skapa metod för refuel beteedende // kalla på monitor (spacestation)
		refuel (vänta random tid)
		skapa metod för TIE-fighter beteende
		va i rymden i rnd tid
        tie.filltank(ships  )
		}


	*/


}
