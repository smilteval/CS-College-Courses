package edu.cuny.csi.csc330.lab5;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DrunkWalker {

	private Intersection startIntersection;
	private Intersection currentIntersection;

	// collection instances to track history and statistics
	private List<Intersection> stepHistory = new ArrayList<Intersection>();
	private Map<Intersection, Integer> intersectionVisitCount = new HashMap<Intersection, Integer>();

	private DrunkWalker() {
		init();
	}

	/**
	 * 
	 * @param avenue
	 * @param street
	 */
	public DrunkWalker(int avenue, int street) {
		startIntersection = new Intersection(avenue, street);
		init();
	}

	private void init() {
		// check if the intersection is already set
		if (startIntersection == null) {
			startIntersection = new Intersection();
		}
		// the current intersection will be the same as the starting intersection at the beginning
		else {
			currentIntersection = new Intersection(startIntersection.getAvenue(), startIntersection.getStreet());
		}
	}

	/**
	 * step in a random direction
	 */
	public void step() {

		takeAStep();

		// add this next intersection to a "history" list that will contain the sequence of all steps taken by this DrunkWalker instance
		stepHistory.add(currentIntersection);

		// if the intersection has been visited, get its current visit count, if not return 0
		int visitCount = intersectionVisitCount.containsKey(currentIntersection)
				? intersectionVisitCount.get(currentIntersection)
				: 0;

		// add 1 to the current visit count
		intersectionVisitCount.put(currentIntersection, visitCount + 1);

	}

	private void takeAStep() {
		Direction dir = Direction.NONE.getNextRandom();

		int currentAvenue = currentIntersection.getAvenue();
		int currentStreet = currentIntersection.getStreet();

		// update the "currentIntersection" instance to reflect the direction that was just selected

		switch (dir) {
		case SOUTH:
			currentStreet--;
			break;
		case WEST:
			currentAvenue++;
			break;
		case NORTH:
			currentStreet++;
			break;
		case EAST:
			currentAvenue--;
			break;
		case SOUTHWEST:
			currentAvenue++;
			currentStreet--;
			break;
		case NORTHWEST:
			currentAvenue++;
			currentStreet++;
			break;
		case NORTHEAST:
			currentAvenue--;
			currentStreet++;
			break;
		case SOUTHEAST:
			currentAvenue--;
			currentStreet--;
			break;
		default:
			System.exit(0);
		}

		// create a new intersection with the updated avenue and street
		currentIntersection = new Intersection(currentAvenue, currentStreet);
	}

	/**
	 * toString()
	 * 
	 * @return
	 */

	@Override
	public String toString() {
		return "DrunkWalker [stepHistory=" + stepHistory + "]";
	}

	/**
	 * generate string that contains current intersection/location info
	 */
	public String getLocation() {
		return String.format("Current location: DrunkWalker [avenue=%d, street=%d]", currentIntersection.getAvenue(),
				currentIntersection.getStreet());
	}

	/**
	 * Take N number of steps
	 * 
	 * @param steps
	 */
	public void fastForward(int steps) {
		for (int i = 0; i < steps; i++) {
			step();
		}
	}

	/**
	 * Display information about this current walker instance
	 */
	public void displayWalkDetails() {

		System.out.println("Starting Location: " + startIntersection);
		System.out.println("Current/Ending Location: " + currentIntersection);
		System.out.println("Distance (blocks): " + howFar());
		System.out.println("Number of steps taken: " + stepHistory.size());
		System.out
				.println("Number of unique intersections visited: " + intersectionVisitCount.entrySet().size() + "\n");

		intersectionVisitCount.entrySet().forEach(intersection -> {
			// if intersection was visited more than once, include it in the list
			if (intersection.getValue() > 1) {
				System.out.println("Visited " + intersection.getKey() + " " + intersection.getValue() + " times!");
			}

		});
	}

	/**
	 * X Y Coordinate distance formula |x1 - x2| + |y1 - y2|
	 * 
	 * @return
	 */
	public int howFar() {
		int startAvenue = startIntersection.getAvenue();
		int startStreet = startIntersection.getStreet();
		int endAvenue = currentIntersection.getAvenue();
		int endStreet = currentIntersection.getStreet();

		return (Math.abs(startAvenue - endAvenue)) + (Math.abs(startStreet - endStreet));
	}

	public static void main(String[] args) {

		// create Drunkard with initial position (ave,str)
		DrunkWalker billy = new DrunkWalker(6, 23);

		for (int i = 1; i <= 3; ++i) {
			billy.step();
			System.out.printf("billy's location after %d steps: %s\n", i, billy.getLocation());
		}

		// get his current location
		String location = billy.getLocation();

		// get distance from start
		int distance = billy.howFar();
		System.out.println("Current location after fastForward(): " + location);
		System.out.println("That's " + distance + " blocks from start.\n");

		// have him move 25 random intersections
		billy.fastForward(25);
		billy.displayWalkDetails();

	}

}
