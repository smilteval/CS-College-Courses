/*
	Smilte Valasinaite
	CSC 211 Spring 2019 

	Program Description:
	The program prompts the user for their name,
	followed by the courses they are taking this semester.
	The program then outputs all this info to a HTML file
	which can be rendered in a web browser as a web page.
*/

// Originally From:
// CSC 211 Spring 2018
// Dr. Sturm

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//Function prototypes
void outputHtmlTitle(ofstream& fout, string title); //sets up the title of the page
void outputHtmlFooter(ofstream& fout); //sets up the footer of the page
void outputHtmlList(ostream& fout, string courses[], int courseNum); //prints out the course list

void main(int argc, char** argv) {

	ofstream htmlFile("myIntro.html");
	string title, name;
	string courses[10]; //holds the names of the courses
	int courseNum; //the number of courses the student is taking

	//Prompts the user to enter information
	cout << "Please enter the title: "; getline(cin, title);
	cout << "Please enter your name: "; getline(cin, name);
	cout << "How many courses are you taking? Enter a number: "; cin >> courseNum; 
	cout << "Please enter the courses you are taking; one per line" << endl;
	
	cin.ignore();
	for (int i = 0; i < courseNum; i++) { //stores names of the courses into the array 
		getline(cin, courses[i]); 
	}

	//Prints out the whole page
	outputHtmlTitle(htmlFile, title);
	htmlFile << "<h2>" << "My name is " << name << "</h2>" << endl;
	htmlFile << "<h3>" << "This semester I am taking: " << "</h3>" << endl;
	outputHtmlList(htmlFile, courses, courseNum);
	outputHtmlFooter(htmlFile);

}
void outputHtmlTitle(ofstream& fout, string title) {
	fout << "<!DOCTYPE html>" << endl;
	fout << "<body style = \"background-color:#ADD8E6;\">" << endl;
	fout << "<html>" << endl;
	fout << "<title>" << endl;
	fout << title << endl;
	fout << "</title>" << endl;
}

void outputHtmlFooter(ofstream& fout) {
	fout << "</body>" << endl;
	fout << "</html>" << endl;
}

void outputHtmlList(ostream& fout, string courses[], int courseNum) {
	fout << "<ul>" << endl;
	for (int i = 0; i < courseNum; i++) { //prints a list item for every course 
		fout << "\t<li>" << courses[i] << "</li>" << endl;
	}
	fout << "\t</ul>" << endl;
}