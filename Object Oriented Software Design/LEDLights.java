package edu.cuny.csi.csc330.lab4;

import java.util.Date;

public class LEDLights {

	// Static constants

	protected static final int MIN_BRIGHTNESS = 1;
	protected static final int MAX_BRIGHTNESS = 7;
	protected static final int MIN_SPEED = 1;
	protected static final int MAX_SPEED = 5;
	protected static final int DEFAULT_BRIGHTNESS = 3;
	protected static final int DEFAULT_SPEED = 3;
	protected static final String COLORS[] = { "red", "green", "blue", "white", "orange", "light green", "dark blue",
			"milk white", "dark yellow", "cyan", "lyons blue", "white pink", "yellow", "light blue", "purple",
			"green white", "light yellow", "sky blue", "brown", "blue white" };
	protected static final String RAINBOW_COLORS[] = { "red", "orange", "yellow", "green", "sky blue", "blue",
			"purple" };

	// Object instance properties

	private boolean powerState;
	private String selectedColor;
	private int selectedBrightness;
	private int selectedSpeed;
	private boolean solidStatic;
	private boolean flashing;
	private boolean jumpingRainbow;
	private boolean fadingRainbow;
	private Date firstTimeOn;
	private Date lastTimeOn;
	
	// Default constructor

	public LEDLights() {
		System.out.println("New Instance \n");
	}

	// Getters

	public boolean isOn() {
		return powerState;
	}

	public String getSelectedColor() {
		return selectedColor;
	}

	public int getSelectedBrightness() {
		return selectedBrightness;
	}

	public int getSelectedSpeed() {
		return selectedSpeed;
	}

	public boolean isSolidStatic() {
		return solidStatic;
	}

	public boolean isFlashing() {
		return flashing;
	}

	public boolean isJumpingRainbow() {
		return jumpingRainbow;
	}

	public boolean FadingRainbow() {
		return fadingRainbow;
	}

	public Date getFirstTimeOn() {
		return firstTimeOn;
	}

	public Date getLastTimeOn() {
		return lastTimeOn;
	}
	
	// Setters

	public void setSelectedColor(String selectedColor) {
		// check if the color is available and if it is, change it and switch to solid static mode
		if (colorIsAvailable(selectedColor)) {
			this.selectedColor = selectedColor;
			switchMode("solidStatic");
		} 
		else {
			System.out.println("The color you selected is not available. Please try another one.");
		}
	}

	public void setSelectedBrightness(int selectedBrightness) {
		this.selectedBrightness = selectedBrightness;
	}

	public void setSelectedSpeed(int selectedSpeed) {
		this.selectedSpeed = selectedSpeed;
	}

	public void setSolidStatic(boolean solidStatic) {
		this.solidStatic = solidStatic;
	}

	public void setFlashing(boolean flashing) {
		this.flashing = flashing;
	}

	public void setJumpingRainbow(boolean jumpingRainbow) {
		this.jumpingRainbow = jumpingRainbow;
	}

	public void setFadingRainbow(boolean fadingRainbow) {
		this.fadingRainbow = fadingRainbow;
	}

	// Public Methods

	// Turn on the lights

	public void on() {
		Date now = new Date();

		// if you're turning on for the first time, set default values
		if (firstTimeOn == null) {
			
			// solid red color with speed and brightness = 3.
			switchMode("solidStatic");
			selectedColor = COLORS[0];
			selectedBrightness = DEFAULT_BRIGHTNESS;
			selectedSpeed = DEFAULT_SPEED;

			// set this to the first time on
			firstTimeOn = now;
		}

		powerState = true;
		lastTimeOn = now;
	}

	// Turn off the lights

	public void off() {
		powerState = false;
	}

	// Increase the speed at which lights alternate

	public void increaseSpeed() {
		// if it's not at maximum yet, increase the speed
		if (selectedSpeed < MAX_SPEED) {
			selectedSpeed++;
		} else {
			System.out.println("The speed is already at maximum!");
		}
	}

	// Decrease the speed at which lights alternate

	public void decreaseSpeed() {
		// if it's not at minimum yet, decrease the speed
		if (selectedSpeed > MIN_SPEED) {
			selectedSpeed--;
		} else {
			System.out.println("The speed is already at minimum!");
		}
	}

	// Increase the brightness of lights

	public void increaseBrightness() {
		if (selectedBrightness < MAX_BRIGHTNESS) {
			selectedBrightness++;
		} else {
			System.out.println("The brightness is already at maximum!");
		}
	}

	// Decrease the brightness of lights

	public void decreaseBrightness() {
		if (selectedBrightness > MIN_BRIGHTNESS) {
			selectedBrightness--;
		} else {
			System.out.println("The brightness is already at minimum!");
		}
	}

	// Visualize the lights and how they change

	public void visualizeLights() {
		// if the lights are on, print out appropriate mode
		if (powerState) {
			if (solidStatic == true) {
				visualizeStatic();
			} else if (flashing == true) {
				visualizeFlashing();
			} else if (jumpingRainbow == true) {
				visualizeJumpingRainbow();
			} else {
				visualizeFadingRainbow();
			}
		} else {
			System.out.println("The lights are off...");
		}

		System.out.println("\n---------------------------------------------------------------------------------");
	}

	// Check which mode needs to be turned on and which ones turned off

	public void switchMode(String mode) {
		if (mode == "solidStatic") {
			this.solidStatic = true;
			this.flashing = false;
			this.jumpingRainbow = false;
			this.fadingRainbow = false;
		} 
		else if (mode == "flashing") {
			this.solidStatic = false;
			this.flashing = true;
			this.jumpingRainbow = false;
			this.fadingRainbow = false;
		} 
		else if (mode == "jumpingRainbow") {
			this.solidStatic = false;
			this.flashing = false;
			this.jumpingRainbow = true;
			this.fadingRainbow = false;
			this.selectedColor = "rainbow";
		} 
		else if (mode == "fadingRainbow") {
			this.solidStatic = false;
			this.flashing = false;
			this.jumpingRainbow = false;
			this.fadingRainbow = true;
			this.selectedColor = "rainbow";
		} 
		else {
			System.out.println("The mode is not available, please try again.");
		}
	}

	@Override
	public String toString() {
		return "LEDLights [powerState=" + powerState + ", selectedColor=" + selectedColor + ", selectedBrightness="
				+ selectedBrightness + ", selectedSpeed=" + selectedSpeed + ", solidStatic=" + solidStatic
				+ ", flashing=" + flashing + ", jumpingRainbow=" + jumpingRainbow + ", fadingRainbow=" + fadingRainbow
				+ ", firstTimeOn=" + firstTimeOn + ", lastTimeOn=" + lastTimeOn + "]";
	}
	
	// Helper Methods

	// Check if a color is available

	private boolean colorIsAvailable(String color) {
		for (int i = 0; i < COLORS.length; i++) {
			if (COLORS[i] == color) {
				return true;
			}
		}
		return false;
	}

	// Visualize solid static mode
	// pattern: color...

	private void visualizeStatic() {
		System.out.println(selectedColor + "...");
	}

	// Visualize flashing mode
	// pattern: *color*

	private void visualizeFlashing() {
		for (int i = 0; i < 8; i++) {
			System.out.print(" *" + selectedColor + "*");
		}
	}

	// Visualize jumping rainbow mode
	// pattern: *color1* *color2* *color3* *color4* *color5* *color6* *color7*

	private void visualizeJumpingRainbow() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < RAINBOW_COLORS.length; j++) {
				System.out.print(" *" + RAINBOW_COLORS[j] + "*");
			}
		}
	}

	// Visualize fading rainbow mode
	// pattern: color1...color2...color3...color4...color5...color6...color7

	private void visualizeFadingRainbow() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < RAINBOW_COLORS.length; j++) {
				System.out.print(RAINBOW_COLORS[j] + "...");
			}
		}
	}

	// ------------------------------------------MAIN----------------------------------------------------

	public static void main(String[] args) {

		// create an LEDLights instance
		LEDLights lights = new LEDLights();

		// turn on the lights
		lights.on();
		System.out.println("Turned on the lights\n\n" + lights + "\n");
		lights.visualizeLights();

		// change color
		lights.setSelectedColor("green");
		System.out.println("Changed color to green \n\n" + lights + "\n");
		lights.visualizeLights();

		// turn on flash
		lights.switchMode("flashing");
		System.out.println("Turned on flashing \n\n" + lights + "\n");
		lights.visualizeLights();

		// speed up the flashing
		lights.increaseSpeed();
		System.out.println("Increased speed \n\n" + lights + "\n");
		lights.visualizeLights();

		// turn on jumpingRainbow
		lights.switchMode("jumpingRainbow");
		System.out.println("Turned on jumping rainbow \n\n" + lights + "\n");
		lights.visualizeLights();

		// turn on fadingRainbow
		lights.switchMode("fadingRainbow");
		System.out.println("Turned on fading rainbow \n\n" + lights + "\n");
		lights.visualizeLights();

		// make the lights brighter
		lights.increaseBrightness();
		System.out.println("Increased brightness \n\n" + lights + "\n");
		lights.visualizeLights();

		// change color (invalid)
		lights.setSelectedColor("burgundy");
		System.out.println("Changed to invalid color \n\n" + lights + "\n");
		lights.visualizeLights();

		// change color to cyan
		lights.setSelectedColor("cyan");
		System.out.println("Changed color to cyan \n\n" + lights + "\n");
		lights.visualizeLights();

		// turn off the lights
		lights.off();
		System.out.println("Turned off the lights \n\n" + lights + "\n");
		lights.visualizeLights();

		// put the program to sleep for 10 seconds, so that we could see the time
		// difference between firstTimeOn and lastTimeOn
		System.out.println("Let's keep the lights off for 10 seconds :)\n");
		try {
			Thread.sleep(10 * 1000);
		} catch (InterruptedException ie) {
			Thread.currentThread().interrupt();
		}

		// turn on the lights (should keep the last configuration)
		lights.on();
		System.out.println("Turned the lights back on \n\n" + lights + "\n");
		lights.visualizeLights();

	}
}
