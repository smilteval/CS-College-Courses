/**
 * LAB 3 -  Lotto QuickPicker Game 
 * @author Smilte Valasinaite
 */
package edu.cuny.csi.csc330.lab3;

import edu.cuny.csi.csc330.util.Randomizer;

import java.util.Arrays;
import java.util.Date;
import java.math.BigInteger;

public class LottoQuickPicker {

	// constants specific to current game - BUT NOT ALL GAMES
	public final static int DEFAULT_GAME_COUNT = 1;
	private final static String GAME_NAME = "Lotto";
	private final static int SELECTION_POOL_SIZE = 59;
	private final static int SELECTION_COUNT = 6;

	private int gameCount;
	private int[][] allNumbers;

	public LottoQuickPicker() {
		init(DEFAULT_GAME_COUNT);
	}

	public LottoQuickPicker(int games) {
		gameCount = games;
		init(games);
	}

	private void init(int games) {

		// create an array that holds the numbers for all games
		allNumbers = new int[gameCount][SELECTION_COUNT];

		// generate games
		for (int i = 0; i < games; i++) {
			allNumbers[i] = generateOneGame();
		}

	}

	private int[] generateOneGame() {

		int numbers[] = new int[SELECTION_COUNT];

		// generate 6 unique numbers
		for (int j = 0; j < SELECTION_COUNT; j++) {

			boolean isUnique = false;

			while (!isUnique) {

				int randomNum = Randomizer.generateInt(1, SELECTION_POOL_SIZE);

				if (isDuplicate(numbers, randomNum) == false) {
					numbers[j] = randomNum;
					isUnique = true;
				}
			}

		}

		// sort the array in ascending order
		Arrays.sort(numbers);

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
			for (int j = 0; j < SELECTION_COUNT; j++) {
				System.out.printf("%2s%02d", "", allNumbers[i][j]);
			}

		}

		// display ticket footer
		displayFooter();

		return;
	}

	protected void displayHeading() {
		System.out.println("-------------------------------------------");
		System.out.println("-------------------" + GAME_NAME + "-------------------");
		System.out.printf("%35s%n", new Date());
	}

	protected void displayFooter() {
		System.out.printf("%n%n%27s%,d%n", "Odds of Winning: 1 in ", calculateOdds());
		System.out.println("-----------------©Tech Deli----------------");
		System.out.println("-------------------------------------------");
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

		BigInteger poolFactorial = factorial(SELECTION_POOL_SIZE);
		BigInteger countFactorial = factorial(SELECTION_COUNT);
		BigInteger differenceFactorial = factorial(SELECTION_POOL_SIZE - SELECTION_COUNT);

		return poolFactorial.divide(countFactorial.multiply(differenceFactorial));
	}

	private BigInteger factorial(int n) {

		BigInteger fact = new BigInteger("1");

		for (int i = 2; i <= n; i++) {
			fact = fact.multiply(BigInteger.valueOf(i));
		}

		return fact;
	}

	public static void main(String[] args) {
		// takes an optional command line parameter specifying number of QP games to be
		// generated
		// By default, generate 1
		int numberOfGames = DEFAULT_GAME_COUNT;

		if (args.length > 0) { // if user provided an argument, assume it to be a game count
			numberOfGames = Integer.parseInt(args[0]); // [0] is the 1st element!
		}

		LottoQuickPicker lotto = new LottoQuickPicker(numberOfGames);

		lotto.displayTicket();
	}

}
