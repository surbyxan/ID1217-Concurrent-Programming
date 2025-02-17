package HomeWork4;

public class TheFuelSpaceStation {
	//! main 
	public static void main(String[] args) {
		System.out.println("A long time ago in a galaxy far, far away...");
		System.out.println("the death star is refueling its TIE-fighters");


		//init av threads/ skeppen thread.start()
		for(int i = 0; i < 5; i++){
			if(i == 0){
				ships refueler = new ships(i, 0, 500);
				refueler.start();

			}
			else if(i == 1){
				ships refueler = new ships(i, 500, 0);
				refueler.start();
			}
			else{
				ships tieFighter = new ships(i, 100, 100);
				tieFighter.start();
			}
		}
			
			

				
				


		// vid sleep för skeppen, olika rnd för bränsletankarna för att få varians på mängden bränsle som behöver tankas
		// även att typ Q bränslet inte behöver fyllas po om det ör > 3/4 tank
	}
}