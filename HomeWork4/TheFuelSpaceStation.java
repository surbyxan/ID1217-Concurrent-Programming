package HomeWork4;

public class TheFuelSpaceStation {
	//! main 
	public static void main(String[] args) {
		System.out.println("A long time ago in a galaxy far, far away...");
		System.out.println("The death star is refueling its TIE-fighters");

		spacestation deathstar = new spacestation(600, 600, 2);


		//init av threads/ skeppen thread.start()
		for(int i = 0; i < 5; i++){
			if(i == 0){
				ships refueler = new ships(deathstar, 0, 500, i);
				refueler.start();

			}
			else if(i == 1){
				ships refueler = new ships(deathstar, 500, 0, i);
				refueler.start();
			}
			else{
				ships tieFighter = new ships(deathstar, 100, 100, i);
				tieFighter.start();
			}
		}
			
			

				
				


		// vid sleep för skeppen, olika rnd för bränsletankarna för att få varians på mängden bränsle som behöver tankas
		// även att typ Q bränslet inte behöver fyllas po om det ör > 3/4 tank
	}
}