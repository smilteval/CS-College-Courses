/**
 * LAB 3 -  Lotto QuickPicker Game 
 */
package edu.cuny.csi.csc330.lab3;

import edu.cuny.csi.csc330.util.Randomizer;

public class LottoQuickPicker {
	
	// constants  specific to current game - BUT NOT ALL GAMES 
	public final static int DEFAULT_GAME_COUNT = 1; 
	private final static String GAME_NAME = "Lotto"; 
	private final static int SELECTION_POOL_SIZE = 59; 
	private final static int SELECTION_COUNT = 6; 


	public LottoQuickPicker() {
		init(DEFAULT_GAME_COUNT); 
	}
	
	public LottoQuickPicker(int games) {
		init(games); 
	}
  

	private void init(int games) {
		
		/**
		 * 
		 * Now what ... START FROM HERE 
		 * What additional methods do you need?
		 * What additional data properties/members do you need? 
		 */
		
		
	}
	


	/**
	 * 
	 */
	public void displayTicket() {
		
		/**
		 * display heading 
		 * 
		 * for i in gameCount 
		 * 		generate selectionCount number of unique random selections in ascending order 
		 * 
		 * display footer 
		 */
		
		
		
		// display ticket heading 
		displayHeading(); 
		
		
		
		/**
		 * Display selected numbers 
		 */

		
		
		// display ticket footer 
		displayFooter(); 
		
		return;
	}
	
	protected void displayHeading() {
	 
		
	}
	
	protected void displayFooter() {
		 
		
	}
	
	
	/**
	 * 
	 * @return
	 */
	private long calculateOdds() {
 
		
		return 0;
	}
  

	/**
	 * @param args 
	 */
	public static void main(String[] args) {
		// takes an optional command line parameter specifying number of QP games to be generated
		//  By default, generate 1  
		int numberOfGames  = DEFAULT_GAME_COUNT; 
		
		if(args.length > 0) {  // if user provided an arg, assume it to be a game count
			numberOfGames = Integer.parseInt(args[0]);  // [0] is the 1st element!
		}
		
		LottoQuickPicker lotto = new LottoQuickPicker(numberOfGames);
		// now what 
		 
		lotto.displayTicket(); 
		

	}

}
