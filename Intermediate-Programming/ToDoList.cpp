/*
	Smilte Valasinaite
	CSC 211 Spring 2020

	Program Description:
	This program allows users to add tasks to their list and mark them as done,
	as well as view the list and start a new one.
*/

#include <iostream>
#include <string>

using namespace std;

class ToDo {
private:
	string name;
	string label;
	int priority;
	bool done;

public:
	//Default Constructor
	ToDo();

	//Getters
	string getName();
	string getLabel();
	int getPriority();
	bool getDone();

	//Setters
	void setName(string n);
	void setLabel(string l);
	void setPriority(int p);
	void setDone(bool d);

	//Overloaded Operator
	friend ostream& operator <<(ostream& output, ToDo& obj);
};

class ToDoList {

private:
	ToDo* p;
	int size;

public:
	//Default Constructor
	ToDoList();

	//Setters
	void setName(int index, string name);
	void setLabel(int index, string label);
	void setPriority(int index, int priority);
	void setDone(int index, bool done);

	//Adds a task to the list
	void addToDo(string name, string label, int priority, int index);

	//Prints the list
	void printList(int count);

	//Deletes the list
	void deleteList();

	//Destructor
	~ToDoList();
};

//Function definitions
void printMenu();
void getToDoInfo(string& taskName, string& taskLabel, int& taskPriority);

int main() {
	int menuOption = 0;
	int taskNum = 0; //the number of tasks added
	int taskIndex; //index of the task to be marked as done
	string taskName;
	string taskLabel;
	int taskPriority;
	ToDoList myList; //a list of To-Do tasks 

	cout << "\n Welcome to the To-Do List Application!\n\n";
	cout << "------------------------------------------------------------\n";

	while (menuOption != 5) {

		//Print the menu and get user input regarding menu choice

		printMenu();
		cin >> menuOption;
		cout << endl;

		//Process input and call appropriate functions

		if (menuOption == 1) { //Display To-Do List

			cout << "------------------------------------------------------------\n\n";
			cout << "                         To-Do List                         \n\n";
			myList.printList(taskNum);
			cout << "------------------------------------------------------------\n\n";

		}
		else if (menuOption == 2) { //Add a To-Do item to the list

			//Get user input
			getToDoInfo(taskName, taskLabel, taskPriority);

			//Update task info in the list
			myList.addToDo(taskName, taskLabel, taskPriority, taskNum);

			//Update the counter
			taskNum++;

		}
		else if (menuOption == 3) { //Mark a To-Do item as done

			cout << "Which task number would you like to mark as completed? ";
			cin >> taskIndex;

			myList.setDone(taskIndex, 1);

			cout << "\nTask marked as done!\n\n";

		}
		else if (menuOption == 4) { //Delete all To-Do items

			taskNum = 0;
			myList.deleteList();

		}
		else if (menuOption == 5) { //Exit

			break;
		}
		else {
			cout << "\nThe option you entered is not available\n";
		}
	}

	system("pause");
	return 0;
}

void printMenu()
{
	cout << "Please select an option from below: \n\n";
	cout << "1. Display To-Do List\n\n";
	cout << "2. Add a To-Do item to the list(Task Name, Label, Priority)\n\n";
	cout << "3. Mark a To-Do item as done/completed\n\n";
	cout << "4. Clear/Delete all To-Do items\n\n";
	cout << "5. Exit\n\n";
}

void getToDoInfo(string& taskName, string& taskLabel, int& taskPriority)
{
	cout << "Please enter task name : ";
	cin.ignore();
	getline(cin, taskName);

	cout << "Please enter task label : ";
	getline(cin, taskLabel);

	cout << "Please enter task priority(1 - 3) : ";
	cin >> taskPriority;

	cout << endl;
}

ToDo::ToDo()
{
	name = "name";
	label = "label";
	priority = 1;
	done = 0;
}

string ToDo::getName()
{
	return name;
}

string ToDo::getLabel()
{
	return label;
}

int ToDo::getPriority()
{
	return priority;
}

bool ToDo::getDone()
{
	return done;
}

void ToDo::setName(string n)
{
	name = n;
}

void ToDo::setLabel(string l)
{
	label = l;
}

void ToDo::setPriority(int p)
{
	priority = p;
}

void ToDo::setDone(bool d)
{
	done = d;
}

ostream& operator<<(ostream& output, ToDo& obj)
{
	output << "Task name: " << obj.getName() << endl;
	output << "Task label: " << obj.getLabel() << endl;
	output << "Task priority: " << obj.getPriority() << endl;
	output << "Task done: " << obj.getDone() << endl << endl;
	return output;
}

ToDoList::ToDoList()
{
	size = 100;
	p = new ToDo[size];
}

void ToDoList::setName(int index, string name)
{
	p[index].setName(name);
}

void ToDoList::setLabel(int index, string label)
{
	p[index].setLabel(label);
}

void ToDoList::setPriority(int index, int priority)
{
	p[index].setPriority(priority);
}

void ToDoList::setDone(int index, bool done)
{
	p[index - 1].setDone(done);
}

void ToDoList::printList(int count)
{
	for (int i = 0;i < count;i++) {
		cout << i + 1 << ". \n\n";
		cout << p[i];
	}
}

void ToDoList::deleteList()
{
	for (int i = 0;i < size;i++) {
		p[i].setName("");
		p[i].setLabel("");
		p[i].setPriority(1);
		p[i].setDone(0);
	}
}

void ToDoList::addToDo(string name, string label, int priority, int index)
{
	setName(index, name);
	setLabel(index, label);
	setPriority(index, priority);
}

ToDoList::~ToDoList()
{
	delete[]p;
}