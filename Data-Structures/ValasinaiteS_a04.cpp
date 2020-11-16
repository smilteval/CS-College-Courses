/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	This program creates a dynArrStack class template. We can add and remove items from a stack,
	copy stacks, assign them to others, get the top and second to top items of the stack. 
	Also, we have a function that uses dynArrStack to evaluate a postfix expression consisting of double numbers.
	Inside main function, we run tests to check if our methods and functions work properly.
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cctype> 

using namespace std;

class PrecondViolatedExcept : public logic_error {
public:
	PrecondViolatedExcept(const string& message = " ");
};

template<class T>
class dynArrStack {
	static const int deCap = 30; //default capacity
	int top; //index of the top of the stack
	T* items; // array in the dynamic memory storage
public:
	dynArrStack() : top(-1) { items = new T[deCap]; } //default ctor
	dynArrStack(const dynArrStack<T>& rhs); //copy ctor
	~dynArrStack() { delete[] items; top = -1; } //destructor
	dynArrStack<T>& operator=(const dynArrStack<T>& rhs); //overloaded = op
	bool isEmpty() const; //checks if the stack is empty
	bool push(const T& nEntry); //adds an item to the stack
	bool pop(); //takes an item out of the stack
	T peek() const throw(PrecondViolatedExcept); //returns the item on the top of the stack
	T peek2() const throw(PrecondViolatedExcept); //return the item second to the top of the stack
	int size() const { return top + 1; } //returns the size of the stack
};

double evaluatePostfix(string& expression); //returns the value of a postfix expression

int main() {

	//TESTING METHODS
	cout << "Testing dynArrStack methods: \n\n";

	dynArrStack<double> stack1;
	stack1.push(5.1); //testing push()
	stack1.push(9.9);
	dynArrStack<double> stack2(stack1);
	dynArrStack<double> stack3 = stack1;

	cout << "stack1.isEmpty(): " << stack1.isEmpty() << endl; //testing default ctor and isEmpty()
	cout << "          stack1: " << stack1.peek() << " " << stack1.peek2() << endl; //testing peek() and peek2()
	cout << "  stack2(stack1): " << stack2.peek() << " " << stack2.peek2() << endl; //testing copy ctor
	cout << " stack3 = stack1: " << stack3.peek() << " " << stack2.peek2() << endl; //testing =op

	stack3.pop(); //testing pop
	stack3.pop();

	cout << "   stack3.peek(): throws an exception " << stack3.peek() << endl; //testing peek() exception
	cout << "  stack3.peek2(): throws an exception " << stack3.peek2() << endl; //testing peek2() exception

	//TESTING POSTFIX CALCULATION
	cout << "___________________________________________________\n";
	cout << "\nTesting postfix evaluation function: \n\n";

	string expression1 = "5 3 2 * + 4 - 5 + q";
	string expression2 = "25.4 3.0 10.2 * + 9.5 - q";
	string expression3 = "3.2 4.4 + 2.0 * 8.0 / q";
	cout << expression1 << " = " << evaluatePostfix(expression1) << endl;
	cout << expression2 << " = " << evaluatePostfix(expression2) << endl;
	cout << expression3 << " = " << evaluatePostfix(expression3) << endl << endl;

	system("pause");
	return 0;
}

PrecondViolatedExcept::PrecondViolatedExcept(const string& message) : logic_error("precondition violated exception: " + message) {} //exception

template<class T>
dynArrStack<T>::dynArrStack(const dynArrStack<T>& rhs) //copy ctor
{
	top = rhs.top;
	items = new T[deCap];
	for (int i = 0;i <= top;i++) { //copy all the elements from the right side
		items[i] = rhs.items[i];
	}
}

template<class T>
dynArrStack<T>& dynArrStack<T>::operator=(const dynArrStack<T>& rhs) //overloaded = op
{
	if (&rhs != this) { 
		delete[] items; //delete everything on the left side
		top = rhs.top; 
		items = new T[deCap];
		for (int i = 0;i <= top;i++) { //copy all the elements from the right side
			items[i] = rhs.items[i];
		}
	}
	return *this;
}

template<class T>
bool dynArrStack<T>::isEmpty() const //checks if the stack is empty
{
	return top < 0;
}

template<class T>
bool dynArrStack<T>::push(const T& nEntry) //adds an item to the stack
{
	bool result = false;
	if (top < deCap - 1) { //checks if there is space in the stack 
		top++;
		items[top] = nEntry;
		result = true;
	}
	return result;
}

template<class T>
bool dynArrStack<T>::pop() //takes an item out of the stack
{
	bool result = false;
	if (!isEmpty()) {
		top--;
		result = true;
	}
	return result;
}

template<class T>
T dynArrStack<T>::peek() const throw(PrecondViolatedExcept) //returns the item on the top of the stack
{
	if (isEmpty()) {
		throw PrecondViolatedExcept("peek() called with empty stack");
	}
	return items[top];
}

template<class T>
T dynArrStack<T>::peek2() const throw(PrecondViolatedExcept) //return the item second to the top of the stack
{
	if (size() < 2) {
		throw PrecondViolatedExcept("peek2() called with a stack that contains fewers than 2 items");
	}
	return items[top-1];
}

double evaluatePostfix(string& expression) //returns the value of a postfix expression
{
	dynArrStack<double> dStack; //create a stack of double numbers
	stringstream expressionStream(expression); //convert to a stringstream for easier parsing
	string item; //stores each item from the string
	double right, left; //stores left and right operands
	double result; //stores the result of the operation

	expressionStream >> item;

	do {
		if (item[0] == 'q') { //if q, exit the loop
			break;
		}
		else if (isdigit(item[0])) { //if the item is a digit push it on the stack
			dStack.push(stod(item)); 
		}
		else { //if the item is an operator

			left = dStack.peek2(); //get the left operand
			right = dStack.peek(); //get the right operand
			dStack.pop(); // pop out the two operands from the stack
			dStack.pop();

			if (item[0] == '+') {
				result = left + right; //get the sum
				dStack.push(result); //push it onto the stack
			}
			else if (item[0] == '-') {
				result = left - right; //get the difference
				dStack.push(result); //push it onto the stack
			}
			else if (item[0] == '*') {
				result = left * right; //get the product
				dStack.push(result); //push it onto the stack
			}
			else if (item[0] == '/') {
				result = left / right; //get the quotient
				dStack.push(result); //push it onto the stack
			}
		}
	} while (expressionStream >> item); //keep looping until there is something to read

	return dStack.peek(); //returns the top item on the stack which is the result of the expression
}
