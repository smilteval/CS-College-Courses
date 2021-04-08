package edu.cuny.csi.csc330.lab5;

import java.util.Scanner;

public class DrunkWalkTester {

	private Scanner input;

	public DrunkWalkTester() {
		init();
	}

	private void init() {
		input = new Scanner(System.in);
	}

	public void runTest(int steps) {

		System.out.print("Enter the starting avenue value: ");
		int avenue = input.nextInt();
		System.out.print("Enter the starting street value: ");
		int street = input.nextInt();

		//////////////////////// start test for Billy
		System.out.println("\n--------------------------------BILLY--------------------------------\n");

		// make the Drunkard with initial position
		DrunkWalker billy = new DrunkWalker(avenue, street);

		// have him move/step 200 times
		billy.fastForward(steps);

		// get his current location
		String billyLocation = billy.getLocation();

		// get distance from start
		int billyDistance = billy.howFar();

		System.out.println("Billy's " + billyLocation);
		System.out.println("That's " + billyDistance + " blocks from start.");

		billy.displayWalkDetails();

		//////////////////// end test for Billy

		//////////////////////// start test for Harvey
		System.out.println("\n--------------------------------HARVEY--------------------------------\n");

		// make the Drunkard with initial position
		DrunkWalker harvey = new DrunkWalker(avenue, street);

		// have him move/step 200 times
		harvey.fastForward(steps);

		// get his current location
		String harveyLocation = harvey.getLocation();

		// get distance from start
		int harveyDistance = harvey.howFar();

		System.out.println("Harvey's " + harveyLocation);
		System.out.println("That's " + harveyDistance + " blocks from start.");

		harvey.displayWalkDetails();

		//////////////////// end test for Billy

		// check who walked a greater distance
		String winner = billyDistance > harveyDistance ? "BILLY" : "HARVEY";

		System.out.println("\n--------------------------------RACE RESULTS--------------------------------\n");
		System.out.println("Billy's distance: " + billyDistance);
		System.out.println("Harvey's distance: " + harveyDistance);
		System.out.println("\n" + winner + " WINS!!!");
	}

	/**
	 * @param args
	 * 
	 */
	public static void main(String[] args) {
		DrunkWalkTester tester = new DrunkWalkTester();

		int steps = 200;
		if (args.length == 1) {
			steps = Integer.parseInt(args[0]);
		}

		tester.runTest(steps);

		System.exit(0);
	}

}
