package edu.cuny.csi.csc330.lab2;

import java.util.Arrays;
import java.lang.Math;

/**
 * Provides numerical data based on the values passed in by the user
 * 
 * @author Smilte Valasinaite
 *
 */

public class NumericAnalyzer {

	private int[] numbers;
	private int count;
	private int min;
	private int max;
	private int range;
	private int sum;
	private int mean;
	private int median;
	private int variance;
	private int deviation;

	public NumericAnalyzer(int[] numbers) {
		this.numbers = numbers;
		count = numbers.length;
	}

	// performs all the numeric calculations

	public void analyze() {

		Arrays.sort(numbers); // sorts the array in ascending order

		min = findMin();
		max = findMax();
		range = calculateRange();
		sum = calculateSum();
		mean = calculateMean();
		median = calculateMedian();
		variance = calculateVariance();
		deviation = calculateDeviation();
	}

	// finds a minimum value in the array

	public int findMin() {
		int min = numbers[0];

		for (int i = 1; i < count; i++) {
			if (numbers[i] < min) {
				min = numbers[i];
			}
		}

		return min;
	}

	// finds a maximum value in the array

	public int findMax() {
		int max = numbers[0];

		for (int i = 1; i < count; i++) {
			if (numbers[i] > max) {
				max = numbers[i];
			}
		}

		return max;
	}

	// calculates the difference between the minimum and maximum values

	public int calculateRange() {
		return max - min;
	}

	// calculates the sum of all the numbers in the array

	public int calculateSum() {
		int sum = 0;

		for (int i = 0; i < count; i++) {
			sum += numbers[i];
		}

		return sum;
	}

	// calculates the average of all the numbers in the array

	public int calculateMean() {
		return sum / count;
	}

	// calculates the middle value in the sorted array

	public int calculateMedian() {

		if (count % 2 != 0) {
			return numbers[count / 2];
		}

		return (numbers[(count - 1) / 2] + numbers[count / 2]) / 2;
	}

	// calculates how far the numbers in the array are spread out from their average
	// value

	public int calculateVariance() {

		int squareSum = 0;

		// Subtract the mean from each value in the list, square each of these distances
		// and add all of the squares together

		for (int i = 0; i < count; i++) {
			squareSum += Math.pow(numbers[i] - mean, 2);
		}

		return squareSum / count;
	}

	// calculates standard deviation which is square root of the variance

	public int calculateDeviation() {
		return (int) Math.sqrt(variance);
	}

	// displays all the numerical data

	public void display() {
		displaySortedArray();
		displayCalculatedValues();
	}

	// displays the elements of the sorted array

	public void displaySortedArray() {

		for (int i = 0; i < numbers.length; i++) {
			System.out.printf("%-5d", numbers[i]);
		}

		System.out.print("\n\n");
	}

	// displays the calculated values

	public void displayCalculatedValues() {
		System.out.printf("Count: %,30d%n", count);
		System.out.printf("Min: %,32d%n", min);
		System.out.printf("Max: %,32d%n", max);
		System.out.printf("Range: %,30d%n", range);
		System.out.printf("Sum: %,32d%n", sum);
		System.out.printf("Mean: %,31d%n", mean);
		System.out.printf("Median: %,29d%n", median);
		System.out.printf("Variance: %,27d%n", variance);
		System.out.printf("Standard Deviation: %,17d%n", deviation);
	}

	// checks if a string value only includes digits

	public static boolean isNumeric(String string) {

		for (int i = 0; i < string.length(); i++) {

			// if we find a non-digit character we return false
			if (!Character.isDigit(string.charAt(i)))
				return false;
		}

		return true;
	}

	// ---------------------------------MAIN---------------------------------

	public static void main(String[] args) {

		// throws an error if user doesn't pass in parameters

		if (args.length == 0) {
			System.err.println("Please pass in 1 or more numeric value(s)");
			System.exit(1); // exits the program
		}

		// creates an integer array from the passed arguments

		int[] numbers = new int[args.length];

		for (int i = 0; i < args.length; i++) {

			// validates data (must be a numeric value)

			if (!NumericAnalyzer.isNumeric(args[i])) {
				System.err.println("Please enter an integer instead of: " + args[i]);
				System.exit(2); // exits the program
			}

			numbers[i] = Integer.parseInt(args[i]);
		}

		NumericAnalyzer analyzer = new NumericAnalyzer(numbers);

		analyzer.analyze();
		analyzer.display();

		System.exit(0);

	}

}
