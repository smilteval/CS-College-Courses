package edu.cuny.csi.csc330.lab6;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Date;
import java.util.ResourceBundle;

import edu.cuny.csi.csc330.util.Randomizer;

public class QuickPicker {

	// constants specific to current game - BUT NOT ALL GAMES
	public final static int DEFAULT_GAME_COUNT = 1;
	private final static String DEFAULT_GAME_NAME = "MegaMillions";

	private String gameName;
	private String vendorName;
	private int selectionPool1Size;
	private int selectionCount1;
	private int selectionPool2Size;
	private int selectionCount2;

	private int gameCount;
	private int[][] allNumbers;

	// create n number of (specific) games

	public QuickPicker(String game, int n) throws QuickPickerException {
		gameCount = n;
		gameName = game;
		initGameValues(gameName);
		init(gameCount);
	}

	// get values from the .properties file

	private void initGameValues(String game) throws QuickPickerException {

		try {
			ResourceBundle bundle = ResourceBundle.getBundle(game);

			if (bundle.containsKey("GameName")) {
				gameName = bundle.getString("GameName");
			}
			if (bundle.containsKey("Pool1")) {
				selectionCount1 = Integer.parseInt(bundle.getString("Pool1").split("/")[0]);
				selectionPool1Size = Integer.parseInt(bundle.getString("Pool1").split("/")[1]);
			}
			if (bundle.containsKey("Pool2")) {
				selectionCount2 = Integer.parseInt(bundle.getString("Pool2").split("/")[0]);
				selectionPool2Size = Integer.parseInt(bundle.getString("Pool2").split("/")[1]);
			}
			if (bundle.containsKey("Vendor")) {
				vendorName = bundle.getString("Vendor");
			}
		} catch (Exception e) {
			throw new QuickPickerException("Error: Game '"+ game +"' does not exist :(",
					QuickPickerException.INVALID_GAME_NAME);
		}
	}

	private void init(int games) {

		// create an array that holds the numbers for all games
		allNumbers = new int[gameCount][selectionCount1 + selectionCount2];

		// generate games
		for (int i = 0; i < games; i++) {
			allNumbers[i] = generateOneGame();
		}
	}

	private int[] generateOneGame() {

		int numbers[] = new int[selectionCount1 + selectionCount2];

		// generate unique numbers for pool 1
		for (int j = 0; j < selectionCount1; j++) {

			boolean isUnique = false;

			while (!isUnique) {

				int randomNum = Randomizer.generateInt(1, selectionPool1Size);

				if (isDuplicate(numbers, randomNum) == false) {
					numbers[j] = randomNum;
					isUnique = true;
				}
			}
		}

		// generate unique numbers for pool 2
		for (int k = selectionCount1; k < selectionCount1 + selectionCount2; k++) {

			boolean isUnique = false;

			while (!isUnique) {

				int randomNum = Randomizer.generateInt(1, selectionPool2Size);

				if (isDuplicate(numbers, randomNum) == false) {
					numbers[k] = randomNum;
					isUnique = true;
				}
			}
		}

		// sort first pool in ascending order
		Arrays.sort(numbers, 0, selectionCount1);

		// sort second pool in ascending order
		Arrays.sort(numbers, selectionCount1, selectionCount1 + selectionCount2);

		return numbers;
	}

	private boolean isDuplicate(int[] numbers, int entry) {

		// check if the array contains the entry
		for (int i = 0; i < numbers.length; i++) {
			if (numbers[i] == entry) {
				return true;
			}
		}
		return false;
	}

	public void displayTicket() {

		// display ticket heading
		displayHeading();

		// display selected numbers
		for (int i = 0; i < gameCount; i++) {

			// display game number
			System.out.printf("%n(%2d)", i + 1);

			// display lucky numbers for each game
			for (int j = 0; j < selectionCount1 + selectionCount2; j++) {

				System.out.printf("%2s%02d", "", allNumbers[i][j]);

				// if pool 2 exists, put opening and closing parentheses before its first and
				// after its last entry
				if (selectionCount2 != 0) {
					if (j == selectionCount1 - 1) {
						System.out.printf("%10s", "(( ");
					}
					if (j == selectionCount1 + selectionCount2 - 1) {
						System.out.printf("%4s", " ))");
					}
				}
			}
		}

		// display ticket footer
		displayFooter();

		return;
	}

	protected void displayHeading() {
		System.out.println("-------------------" + gameName + "-------------------\n");
		System.out.printf("%42s%n", new Date());
	}

	protected void displayFooter() {
		System.out.printf("%n%n%33s%,d%n", "Odds of Winning: 1 in ", calculateOdds());
		System.out.println("\n--------------- (c)" + vendorName + "---------------");
	}

	/*
	 * We want to calculate the odds of winning the lottery The lowest number we can
	 * have is 1, the highest - 59
	 *
	 * In order to win, we need to get all numbers correctly, which means that we
	 * will multiply all the odds of picking one number correctly (factorial of pool
	 * of numbers)
	 *
	 * However, we can choose the winning numbers in any order which means that our
	 * chance of winning betters by the number of ways that one sequence can be
	 * written (factorial of selection count)
	 *
	 * Formula: selection pool size! / (selection count! * (selection pool size -
	 * selection count)!)
	 * 
	 */

	private BigInteger calculateOdds() {

		// odds for pool 1
		BigInteger pool1Factorial = factorial(selectionPool1Size);
		BigInteger count1Factorial = factorial(selectionCount1);
		BigInteger difference1Factorial = factorial(selectionPool1Size - selectionCount1);
		BigInteger oddsPool1 = pool1Factorial.divide(count1Factorial.multiply(difference1Factorial));

		// odds for pool 2
		BigInteger pool2Factorial = factorial(selectionPool2Size);
		BigInteger count2Factorial = factorial(selectionCount2);
		BigInteger difference2Factorial = factorial(selectionPool2Size - selectionCount2);
		BigInteger oddsPool2 = pool2Factorial.divide(count2Factorial.multiply(difference2Factorial));

		if(selectionCount2 == 0) {
			return oddsPool1;
		}else {
			return oddsPool1.multiply(oddsPool2);
		}
	}

	private BigInteger factorial(int n) {

		BigInteger fact = new BigInteger("1");

		for (int i = 2; i <= n; i++) {
			fact = fact.multiply(BigInteger.valueOf(i));
		}

		return fact;
	}

	public static void main(String[] args) {

		String gameName = DEFAULT_GAME_NAME; // MegaMillions
		int numberOfGames = DEFAULT_GAME_COUNT; // 1 game

		if (args.length == 2) { // if user provided both arguments, assume the first one to be a game name and
								// second - game count
			gameName = args[0];
			numberOfGames = Integer.parseInt(args[1]);
		} else if (args.length == 1) {// if user provided one argument, assume it to be a game name
			gameName = args[0];
		}

		QuickPicker lotto;
		try {
			lotto = new QuickPicker(gameName, numberOfGames);
			lotto.displayTicket();

		} catch (QuickPickerException e) {
			System.out.println(e);
		}

	}

}
