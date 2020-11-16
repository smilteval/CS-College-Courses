/*
	Smilte Valasinaite
	CSC 211 Spring 2020

	Program Description:
	This program allows coffee shop's customers to select one or more
	items from the menu and calculates and prints the bill on the screen.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Global Variables/Structs 

struct menuItemType {
	string menuItem;
	double menuPrice;
	int inventoryCount;
};

//Function Prototypes

void initData(menuItemType arr[]); //loads the initial menu data into the menu array
void showMenu(const menuItemType arr[]); //prints out the values stored in the menu array and instructs the user on how to input their choices
double calcAmt(menuItemType arr[], int index, int count); //calculates the amount total for each item based on the count provided by the customer
void updateInventory(menuItemType arr[], int index, int count); //updates the count for each menu item after the user has purchased it
void printTotalBill(double price); //calculates and prints the total bill amount

int main() {

	char exit; //variable used to end the program

	menuItemType menu[8]; //declare the array for menu items
	initData(menu); //initialize the array
	
	while (true) {
		
		double price = 0.0;
		int itemIndex = 0;
		int itemCount = 0;

		showMenu(menu);

		while (true) {

			cout << "\nPlease enter the number: ";
			cin >> itemIndex;

			if (itemIndex == 0) { //checkout if enters 0
				printTotalBill(price);
				break;
			}
			else {
				cout << "Please enter the quantity: ";
				cin >> itemCount;

				if (menu[itemIndex].inventoryCount >= itemCount) { //check if the item is available 

					price += calcAmt(menu, itemIndex, itemCount); //update the total price
					updateInventory(menu, itemIndex, itemCount); //update the items left

				}
				else {
					cout << "\nThe number of items you selected is not available...\n";
					cout << "Please select a different quantity or a different item.\n\n";
				}
			}
		}

		cout << "Do you want to exit the program? (Y/N) ";
		cin >> exit;

		if (exit == 'Y') { //exit the program
			break;
		}
	}

	system("pause");
	return 0;
}

void initData(menuItemType arr[])
{
	for (int i = 0; i < 8; i++) { // the count for each menu item is set to 5
		arr[i].inventoryCount = 5;
	}

	arr[0].menuItem = "Plain Egg";
	arr[0].menuPrice = 1.99;

	arr[1].menuItem = "Bacon and Egg";
	arr[1].menuPrice = 3.45;

	arr[2].menuItem = "Muffin";
	arr[2].menuPrice = 2.99;

	arr[3].menuItem = "French Toast";
	arr[3].menuPrice = 4.99;

	arr[4].menuItem = "Fruit Basket";
	arr[4].menuPrice = 5.49;

	arr[5].menuItem = "Cereal";
	arr[5].menuPrice = 1.99;

	arr[6].menuItem = "Coffee";
	arr[6].menuPrice = 1.50;

	arr[7].menuItem = "Tea";
	arr[7].menuPrice = 1.25;
}

void showMenu(const menuItemType arr[])
{
	cout << "\n------------------ MENU ------------------\n\n";
	for (int i = 0; i < 8; i++) {//prints the item list
		cout << left << i + 1 << ". " << arr[i].menuItem << setw(35 - arr[i].menuItem.length());
		cout << right << "$" << fixed << setprecision(2) << arr[i].menuPrice << "\n\n";
	}
	cout << "------------------------------------------\n";
	cout << " SELECT YOUR ITEMS. FOR CHECKOUT ENTER 0 \n\n";
}

double calcAmt(menuItemType arr[], int index, int count)
{
	return arr[index-1].menuPrice * count;
}

void updateInventory(menuItemType arr[], int index, int count)
{
	arr[index].inventoryCount -= count;
}

void printTotalBill(double price)
{
	double tax = price * 0.05;

	cout << "\n----------------YOUR BILL-----------------\n";
	cout << "\nPrice for the items:" << setw(17) << "$" << fixed << setprecision(2) << price << endl;
	cout << "Tax:" << setw(34) << "$" << fixed << setprecision(2) << tax << endl;
	cout << "__________________________________________\n";
	cout << "Total Price:" << setw(25) << "$" << fixed << setprecision(2) << price + tax << "\n\n\n";

}

