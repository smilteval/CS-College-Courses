/*
	Smilte Valasinaite 
	CSC 211 Spring 2020

	Program Description: 
	This program allows the user to view and reserve seats on an Airplane
*/

#include <iostream>

using namespace std;

//Global Variables:
const int ROWS = 13;
const int COLS = 6;
char seats[ROWS][COLS];

//Function Prototypes:
void init(); //initializes the seats array to '*' - all seats are available initially
void printMenu(); //prints out the menu
void printSeats(); //prints out the seating plan - with available seats marked with '*' and reserved seats marked with 'X'
void getSeatInput(int& rowNum, char& colChar); // gets input from user regarding seat selection
int convertColChar(const char& c); //converts column char to corresponding column number (staring with A being Column 0)
bool checkAvailability(const int& rowNum, const int& colNum); //checks if a seat is available
void reserveSeat(); //function to reserve a single seat
void reserveSeat(const int& numSeats); //function to reserve numSeats number of seats

int main() {
	int menuOption = 0; //the menu option the user chooses
	int numSeats; //number of seats the user wants to reserve

	//Initialize the array
	init(); 

	while (menuOption != 4) {

		//Print the menu and get user input regarding menu choice
		printMenu();
		cout << "Please select one of the options: ";
		cin >> menuOption;

		//Process input and call appropriate functions
		if (menuOption == 1) { //show seats
			printSeats();
		}
		else if (menuOption == 2) { //reserve a single seat
			reserveSeat();
		}
		else if (menuOption == 3) { //reserve multiple seats
			cout << "\nPlease enter the number of seats you would like to reserve: ";
			cin >> numSeats;
			cout << "\n\nPlease enter your choice of seats one at a time. \n";
			reserveSeat(numSeats);
		}
		else if (menuOption == 4) { //exit
			break;
		}
		else {
			cout << "\nThe option you entered is not available\n";
		}
	}

	system("pause");
	return 0;
}

void init()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			seats[i][j] = '*';
		}
	}
}

void printMenu()
{
	cout << "*********************************************************\n\n";
	cout << "Plane Seat Reservation Program\n\n";
	cout << "Please select a menu option from below:\n\n";
	cout << "1. Show seats\n\n";
	cout << "2. Reserve a single seat\n\n";
	cout << "3. Reserve multiple seats\n\n";
	cout << "4. Exit\n\n";
	cout << "*********************************************************\n\n";
}

void printSeats()
{
	cout << "\n\tA  B  C  D  E  F\n\n"; //prints column letters at the top

	for (int i = 0; i < ROWS; i++) {

		cout << "ROW " << i + 1 << "\t"; //prints row numbers on the left

		for (int j = 0; j < COLS; j++) {
			cout << seats[i][j] << "  ";
		}
		cout << "\n\n";
	}
}

void getSeatInput(int& rowNum, char& colChar)
{
	cout << "\nPlease enter the row number: ";
	cin >> rowNum;
	cout << "Please enter the column letter: ";
	cin >> colChar;
	cout << endl;
}

int convertColChar(const char& c)
{
	int num;
	switch (c) {
		case 'a':
		case 'A':	
			num = 0;
			break;
		case 'b':
		case 'B':
			num = 1; 
			break;
		case 'c':
		case 'C':
			num = 2; 
			break;
		case 'd':
		case 'D': 
			num = 3; 
			break;
		case 'e':
		case 'E': 
			num = 4; 
			break;
		case 'f':
		case 'F':
			num = 5; 
			break;
		default: //if any other character 
			num = -1;
	}
	return num;
}

bool checkAvailability(const int& rowNum, const int& colNum)
{
	if (seats[rowNum][colNum] == '*') {
		return true;
	}
	else { 
		return false; 
	}
}

void reserveSeat()
{
	int seatRow; //selected seat row
	char seatColChar; //selected seat column letter
	int seatColNum; //selected seat column number

	//Gets seat input
	getSeatInput(seatRow, seatColChar);
	seatColNum = convertColChar(seatColChar); 
	
	//Checks if the seat exists and is available 
	if (seatColNum == -1 || (seatRow < 1 || seatRow > 13)) { //checks if row and column are in range 1-13 and a-f respectively 
		cout << "The row number or the column letter you entered is incorrect. Please try again.\n";
		reserveSeat();
	}
	else if (checkAvailability(seatRow - 1, seatColNum)){ //checks if the seat is not taken yet
		seats[seatRow-1][seatColNum] ='X';
		cout << "Seat reserved.\n\n";
	}
	else {
		cout << "Seat is already taken. Please choose a different seat.\n";
		reserveSeat();
	}
}

void reserveSeat(const int& numSeats)
{
	for (int i = 0; i < numSeats; i++) {
		reserveSeat();
	}
}
