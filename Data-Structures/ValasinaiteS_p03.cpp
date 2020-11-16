/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	The program handles big numbers of arbitrary size, without having to consider the limit of the
	machine representation. The program uses linked chain to get the sum and product of two large numbers.
*/



#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class nNode {
public:
	int data; //holds a 4 digit number
	nNode* next; //pointer to the next node
	nNode* prev; //pointer to the previous node
	nNode() : data(0), next(nullptr), prev(nullptr) {} //default ctor
	nNode(int num) : data(num), next(nullptr), prev(nullptr) {} //1 parameter ctor
};

class lkdBN {
private:
	nNode* head; //pointer to the first node
	nNode* tail; //pointer to the last node
	int itemCount; //size of the big number in terms of nodes
public:
	lkdBN() : head(nullptr), tail(nullptr), itemCount(0) {} //default ctor
	lkdBN(string& stringNum); //conversion ctor
	//lkdBN(const lkdBN& bn); //copy ctor
	lkdBN operator +(const lkdBN& rhs)const;
	lkdBN operator *(const lkdBN& rhs)const;
	//lkdBN& operator=(const lkdBN& other); // assignment operator
	bool addFromHead(const int& anEntry); //inserts a number in the front
	bool addFromTail(const int& anEntry); //inserts a number at the end
	void displayNodes()const; //displays the elements inside nodes
	void displayBN()const; //displays a big number
	int getSize()const { return itemCount; } //returns the number of items in the list
	void setSize(int size) { itemCount = size; } //sets the size of the new list
	void clear();
};

int main() {

	string arrayOfNums[8];//holds the values from text file

	ifstream input("Prj03_testdata.txt");
	if (input.is_open()) {
		cout << "File is open" << endl;
		cout << "________________________________________________________";
		int i = 0;
		while (!input.eof()) { //until the end of file, store string nums into a string array
			input >> arrayOfNums[i];
			i++;
		}
	}
	//place string nums into linked lists where they are converted to ints
	lkdBN num1(arrayOfNums[0]);
	lkdBN num2(arrayOfNums[1]);
	lkdBN num3(arrayOfNums[2]);
	lkdBN num4(arrayOfNums[3]);
	lkdBN num5(arrayOfNums[4]);
	lkdBN num6(arrayOfNums[5]);
	lkdBN num7(arrayOfNums[6]);
	lkdBN num8(arrayOfNums[7]);
	
	cout << "\nNumber 1: ";
	num1.displayBN();
	cout << "\nNumber 2: ";
	num2.displayBN();
	cout << "\n     Sum: ";
	(num1 + num2).displayBN(); //num1 + num2
	cout << "\n Product: ";
	(num1 * num2).displayBN(); //num1 * num2

	cout << "\n________________________________________________________\n";

	cout << "\nNumber 3: ";
	num3.displayBN();
	cout << "\nNumber 4: ";
	num4.displayBN();
	cout << "\n     Sum: ";
	(num3 + num4).displayBN(); //num3 + num4
	cout << "\n Product: ";
	(num3 * num4).displayBN(); //num3 * num4

	cout << "\n________________________________________________________\n";

	cout << "\nNumber 5: ";
	num5.displayBN();
	cout << "\nNumber 6: ";
	num6.displayBN();
	cout << "\n     Sum: ";
	(num5 + num6).displayBN(); //num5 + num6
	cout << "\n Product: ";
	(num5 * num6).displayBN(); //num5 * num6

	cout << "\n________________________________________________________\n";

	cout << "\nNumber 7: ";
	num7.displayBN();
	cout << "\nNumber 8: ";
	num8.displayBN();
	cout << "\n     Sum: ";
	(num7 + num8).displayBN(); //num7 + num8
	cout << "\n Product: ";
	(num7 * num8).displayBN(); //num7 * num8

	cout << "\n________________________________________________________\n";

	system("pause");
	return 0;
}

lkdBN::lkdBN(string& stringNum) //converts a string to an integer and places it into nodes containing 4 digit numbers 
{
	head = nullptr;
	tail = nullptr;
	itemCount = 0;

	int i = stringNum.length();
	while (i >= 4){ //while there are more than 4 digits left
		string stringDigits = stringNum.substr(i - 4, 4); //place 4 digits from the original string to the stringDigits
		int fourDigits = stoi(stringDigits); //convert stringDigits to an integer
		addFromTail(fourDigits); //add that integer to the linked chain
		i -= 4;
	}
	if (i != 0) { //if the number's length is not a multiple of four
		int fourDigits = stoi(stringNum.substr(0, i)); //convert remaining stringDigits to an integer
		addFromTail(fourDigits); //add that integer to the linked chain
	}
}

lkdBN lkdBN::operator+(const lkdBN& rhs) const
{
	lkdBN sumBN; //new list containing the sum of two other lists

	//points to the first node of the two lists 
	nNode* ptr1 = head;
	nNode* ptr2 = rhs.head;
	int carry = 0;
	
	//traverses through both lists
	while (ptr1 != nullptr || ptr2 != nullptr) { //while at least one of the lists is full
		
		int num1 = 0;
		int num2 = 0;

		if (ptr1 != nullptr && ptr2 != nullptr) { //if both lists are full, get their digits
			num1 = ptr1->data;
			num2 = ptr2->data;
		}
		if (ptr1 == nullptr) { //if the first list is empty, take 0 as its digit and take digits from the second list
			num1 = 0;
			num2 = ptr2->data;
		}
		if (ptr2 == nullptr) {//if the second list is empty, take 0 as its digit and take digits from the first list
			num2 = 0;
			num1 = ptr1->data;
		}
		
		int sum = carry + num1 + num2; //add digits from both lists and add carried value, if the list ended, take 0 instead

		carry = 0;

		//handles value carrying
		if (sum >= 10000) {
			carry = sum / 10000;
			sum = sum % 10000;
		}

		//adds the result to the sumBN list
		sumBN.addFromTail(sum);

		//if the lists are not empty, point to the next node
		if (ptr1 != nullptr) {
			ptr1 = ptr1->next;
		}
		if (ptr2 != nullptr) {
			ptr2 = ptr2->next;
		}
	}
	
	if (carry > 0) { //if there is still a value in carry, create a new node for it
		sumBN.addFromTail(carry);
		carry = 0;
	}

	return sumBN;
}

lkdBN lkdBN::operator*(const lkdBN& rhs) const
{
	lkdBN tempBN;//holds the result of multiplication of one node from big number 1 with every node in big number 2
	lkdBN product;
	//points to the first node of the two lists 
	nNode* ptr1 = head;
	nNode* ptr2 = rhs.head;
	//points to the first node of the temporary list
	nNode* tempPtr = new nNode;
	nNode* proPtr = new nNode;

	tempBN.head = tempPtr;

	int carry = 0;

	if ((getSize() == 1 && ptr1->data == 0) || (rhs.getSize() == 1 && ptr2->data == 0)) { //if one of the numbers is 0, the result is 0 as well
		cout << "0"; //any number *0 is 0
	}
	else if (getSize() == 1 && ptr1->data == 1) { //if the first big number is "1", then the result will be the second big number
		while (ptr2 != nullptr) {
			tempPtr->data = ptr2->data;
			ptr2 = ptr2->next;
			tempPtr = tempPtr->next;
		}
	}
	
	else {
		for (int i = 0; i < getSize();i++) { //multiply each node of big number 1 
			for (int j = 0; j < rhs.getSize();j++) { //with each node of big number 2

				int num1 = 0;
				int num2 = 0;

				if (ptr1 != nullptr && ptr2 != nullptr) { //if both lists are full, get their digits
					num1 = ptr1->data;
					num2 = ptr2->data;
				}
				if (ptr1 == nullptr) { //if the first list is empty, take 0 as its digit and take digits from the second list
					num2 = ptr2->data;
				}
				if (ptr2 == nullptr) {//if the second list is empty, take 0 as its digit and take digits from the first list
					num1 = ptr1->data;
				}

				int mul = (num1 * num2) + carry;

				//cout << endl << mul << endl;
				carry = 0;

				if (mul >= 10000) {
					carry = mul / 10000;
					//cout << endl << mul << endl;
					mul = mul % 10000;
					//cout << endl << mul << endl;
				}

				tempBN.addFromTail(mul);
				
				//if the lists are not empty, point to the next node
				
				ptr2 = ptr2->next;
			}
			
			if (carry > 0) { //if there is still a value in carry, create a new node for it
				tempBN.addFromTail(carry);
				carry = 0;
			}
			ptr2 = rhs.head;
			if (ptr1 != nullptr) {
				ptr1 = ptr1->next;
			}

			product = product + tempBN; //add temp list to our product

			tempBN.clear();
			for (int z = i;z >= 0;z--) { //for every new iteration add four zeros (shift numbers to the left)
				tempBN.addFromHead(0000);
			}
		}
	}
	
	return product;
}


bool lkdBN::addFromHead(const int& anEntry)
{
	nNode* newPtr = new nNode(anEntry); //alocates a new node with a number
	if (head != nullptr) {
		newPtr->next = head; //newPtr's next pointer points to the node that the head is pointing to
		head->prev = newPtr; //head's prev pointer points to the new pointer
		head = newPtr; //head points to the newPtr
	}
	else {
		head = newPtr;
		tail = newPtr;
	}
	itemCount++; //increases the number of items
	return true;
}

bool lkdBN::addFromTail(const int& anEntry)
{
	nNode* newPtr = new nNode(anEntry);
	if (tail != nullptr) {
		newPtr->prev = tail; //newPtr's previous pointer points to the node that the tail is pointing to 
		tail->next = newPtr; //tail's prev pointer points to the new pointer
		tail = newPtr; //tail points to the newPtr
	}
	else {
		head = newPtr;
		tail = newPtr;
	}
	itemCount++; //increases the number of items
	return true;
}

void lkdBN::displayNodes() const //prints the big number inside nodes
{
	nNode* currentPtr = head;
	while (currentPtr != nullptr) {
		cout << currentPtr->data << " ";
		currentPtr = currentPtr->next;
	}
}

void lkdBN::displayBN() const //prints the big number in correct order
{
	nNode* currentPtr = tail;
	while (currentPtr != nullptr) {
		cout << currentPtr->data << " ";
		currentPtr = currentPtr->prev;
	}
}

void lkdBN::clear() //clears the list
{
	{
		while (head != nullptr)
		{
			nNode* nodeToDeletePtr = head;
			head = head->next;
			nodeToDeletePtr->next = nullptr;
			delete nodeToDeletePtr;
		}
		itemCount = 0;
	}
}
