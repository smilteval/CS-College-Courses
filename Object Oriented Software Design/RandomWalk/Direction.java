/**
 * Completed Direction ENUM 
 */

package edu.cuny.csi.csc330.lab5;

import edu.cuny.csi.csc330.util.Randomizer;

public enum Direction {
	NONE, NORTH, EAST, SOUTH, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST;

	// methods
	public Direction getFavorite() {
		return SOUTH; // It's getting cold! ...
	}

	public Direction getNextRandom() {

		int direction = Randomizer.generateInt(1, 8);

		// 1 = south, 2 = west, 3 = north, 4 = east,
		// 5 = south-west, 6 = north-west, 7 = north-east, 8 = south-east
		
		if (direction == 1) { // south
			return SOUTH;
		} else if (direction == 2) { 
			return WEST;
		} else if (direction == 3) { 
			return NORTH;
		} else if (direction == 4) { 
			return EAST;
		} else if (direction == 5) { 
			return SOUTHWEST;
		} else if (direction == 6) { 
			return NORTHWEST;
		} else if (direction == 7) { 
			return NORTHEAST;
		} else { 
			return SOUTHEAST;
		}
	}

	public static void main(String[] args) {

		int c = 0;
		while (c++ < 100) {
			System.out.println(Direction.NONE.getNextRandom());
		}

	}

}
