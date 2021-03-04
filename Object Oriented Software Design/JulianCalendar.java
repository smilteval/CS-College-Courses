package edu.cuny.csi.csc330.lab1;

/**
 * Generates a non-leap year perpetual Julian Calendar 
 * @author Smilte Valasinaite
 *
 */
public class JulianCalendar {
	
	// Max number of Days in a month 
	static private  final int MAX_DAY = 31; 
	
	// abbreviated Month names 
	static private  final String [] MONTH_NAMES = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	
	// day length of each month 
	static private final  int [] MONTH_SIZES = {
		31, 28, 31,30,31, 30, 31, 31, 30, 31, 30, 31
	};

	/**
	 * display The "DAY" Column Heading 
	 */
	static private void displayDayHeading() {
		System.out.printf("%6s", "Day");
		
	}
	
	/**
	 * display Month names between Day .... Day
	 */
	static private void displayHeading() {
		displayDayHeading(); 
		
		for(int i = 0 ; i < MONTH_NAMES.length ; ++i )  {
			System.out.printf("%5s", MONTH_NAMES[i]);
		}
		
		displayDayHeading(); 
	}
	

	static public void display() {
		displayHeading(); // display heading 
		
		/**
		 * Complete the logic to display a Julian cal given the pre-populated arrays defined by the Class
		 * 
		 * 
		 *
		 *
		 Smilte's WORK GOES HERE 
		 * 
		 */
		
		System.out.printf("%n");		
		
		for(int dayMonth = 1; dayMonth <= MAX_DAY; dayMonth++) {
			
			int dayYear = dayMonth;
			
			System.out.printf("%6d", dayMonth); //prints out the days of the month
			
			//Prints out the days of the year
			for (int month = 0; month < MONTH_NAMES.length; month++) {
				
				//if the day of the month is bigger than the number of days the month has, print zero 
				if(dayMonth > MONTH_SIZES[month]) { 
					System.out.printf("%2s%03d", "", 0);
				}
				//otherwise print the day of the year
				else { 
					System.out.printf("%2s%03d", "", dayYear);
				}
				dayYear += MONTH_SIZES[month];
			
			}	
			
			System.out.printf("%6d", dayMonth); //prints out the days of the month
			System.out.printf("%n");
			
		}
		
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// invoke display method 
		JulianCalendar.display(); 
	}
}