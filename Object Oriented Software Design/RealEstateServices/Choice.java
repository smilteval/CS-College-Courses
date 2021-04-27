package realty;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Choice extends JFrame{

	JPanel panel;
	JLabel location, agent, text;
	JButton locationButton, agentButton;

	public Choice() {
		location = new JLabel();
		location.setText("     Locations:"); // (must be 5 spaces )
		agent = new JLabel();
		agent.setText("     Agents:"); // (must be 5 spaces )
		locationButton = new JButton("Choose");
		agentButton = new JButton("Choose");
		panel = new JPanel(new GridLayout(3, 1));
		panel.add(location); // location label
		panel.add(locationButton); // location button
		panel.add(agent); // agent label
		panel.add(agentButton); // agent button

		ClickListener click = new ClickListener();
		
		locationButton.addActionListener(click);
		agentButton.addActionListener(click);
		
		setTitle("What would you like to search for?");
		setSize(375, 150); // setting the size of the window
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		add(panel, BorderLayout.CENTER);
	}
	
	private class ClickListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource() == locationButton) {
				setVisible(false);
				new SearchLocation();
			}
			else if(e.getSource() == agentButton) {
				setVisible(false);
				new SearchAgent();
			}
		}
	}
	
	public static void main(String[] args) {
		new Choice();
 	}
}
