/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	This program creates a SafeArray (SA) class template that dynamically allocates
	an array of any type of thing it works on, rather than creating a set of type-specific arrays.
*/

#include <iostream>
#include <string>

using namespace std;

const int dSize = 10; //default array size

template <class T>

//Declaring SA class template
class SA {
private:
	T* pT; //pointer of T type
	int lIdx; //lowest index of the array
	int hIdx; //highest index of the array
public:
	//Constructors
	SA(); 
	SA(int n);
	SA(int l, int h);
	SA(const SA& rhs);

	//Destructor
	~SA();

	//Overloaded operators
	SA& operator=(const SA& rhs);
	T& operator[](int offset);
	const T& operator[](int offset) const;
	template<class T2>
	friend ostream& operator<< (ostream& output, const SA<T2>& rhs);

	//Accessor
	int getSize() const;
};

//Declaring Cat class
class Cat {
private:
	string name;
	int age;
	int weight;
public:
	//Constructors
	Cat();
	Cat(string n, int a, int w);

	//Overloaded operator
	friend ostream& operator<< (ostream& output, const Cat& obj);
};

int main() {
	//Testing an array of integers and default constructor
	SA<int> intArr;

	for (int i = 0;i < intArr.getSize();i++) { 
		intArr[i] = i;
	}

	cout << "intArr: \n" << intArr << endl; 

	//Testing an array of cats and 1 parameter constructor
	SA<Cat> catArr(3); 

	for (int i = 0; i < 3; i++) {
		catArr[i] = Cat("Cat", i + 1, (i + 1) * 5);
	}

	cout << "catArr(3): \n" << catArr << endl;

	//Testing an array of doubles and 2 parameter constructor
	SA<double> doubleArr(2,6); 

	for (int i = 2;i <= 6;i++) { 
		doubleArr[i] = i + 0.1;
	}

	cout << "doubleArr(2,6): \n" << doubleArr << endl; 

	//Testing copy constructor
	SA<int> intArr2(intArr);

	cout << "intArr2(intArr): \n" << intArr2 << endl; 

	//Testing overloaded = operator
	SA<int> intArr3(6); 

	for (int i = 0;i < intArr3.getSize();i++) {
		intArr3[i] = 0;
	}

	cout << "intArr3(6): \n" << intArr3 << endl; 

	intArr3 = intArr2;

	cout << "intArr3 = intArr2: \n" << intArr3 << endl; 

	//Testing overloaded [] operator (read)
	cout << "catArr[2]: \n" << catArr[2] << endl << endl; 

	//Testing overloaded [] operator (write)
	doubleArr[3] = 1.1;

	cout << "doubleArr[3] = 1.1: \n" << doubleArr << endl; 
	
	//Testing array index out of bounds
	cout << "doubleArr[0]: \n";
	cout << doubleArr[0] << endl;

	//All the "cout <<" lines test the overloaded << operator

	system("pause");
	return 0;
}

//Defining SA class template

template <class T>
SA<T>::SA() { //Default constructor
	lIdx = 0;
	hIdx = dSize - 1;
	pT = new T[dSize];
}

template <class T>
SA<T>::SA(int n) { //1 Parameter constructor
	lIdx = 0;
	hIdx = n - 1;
	pT = new T[n];
}

template <class T>
SA<T>::SA(int l, int h) { //2 Parameter constructor
	lIdx = l;
	hIdx = h;
	pT = new T[hIdx+1];
}

template <class T>
SA<T>::SA(const SA& rhs) { //Copy constructor
	lIdx = rhs.lIdx;
	hIdx = rhs.hIdx;
	pT = new T[getSize()]; //creates a new array of the same size as the rhs
	
	for (int i = rhs.lIdx; i <= rhs.hIdx; i++){ //copies all the values from the rhs array
		pT[i] = rhs[i]; 
	}
}

template<class T>
SA<T>& SA<T>::operator=(const SA<T>& rhs) // Overloaded = operator
{
	if (this != &rhs) {
		lIdx = rhs.lIdx;
		hIdx = rhs.hIdx;
		delete[] pT; //deletes a pointer to this array
		pT = new T[getSize()]; //creates a new array of the same size as the rhs

		for (int i = rhs.lIdx; i <= rhs.hIdx; i++) { //copies all the values from the rhs array
			pT[i] = rhs[i];
		}
	}
	return *this; //returns an object
}

template<class T>
SA<T>::~SA() { //Destructor
	delete[]pT;
}

template<class T>
T& SA<T>::operator[](int offset) //Overloaded [] operator (write)
{
	if (offset >= lIdx && offset <= hIdx) { //Checks if the array index is out of bounds 
		return pT[offset];
	}
	else {
		cout << "The array index is out of bounds" << endl;
		exit(0);
	}
}

template<class T>
const T& SA<T>::operator[](int offset) const //Overloaded operator [] (read)
{
	return pT[offset];
}

template<class T>
int SA<T>::getSize() const //Returns the size of the array
{
	return (hIdx - lIdx + 1);
}


template<class T2>
ostream& operator<< (ostream& output, const SA<T2>& rhs) //Overloaded << operator
{
	for (int i = rhs.lIdx; i <= rhs.hIdx; i++) {
		output << "[" << i << "] = " << rhs[i] << endl;
	}
	return output;
}

//Defining Cat class

Cat::Cat() { //Default constructor 
	name = "Kitty";
	age = 1;
	weight = 3;
}

Cat::Cat(string n, int a, int w) //3 Parameter constructor
{
	name = n;
	age = a;
	weight = w;
}

ostream& operator<<(ostream& output, const Cat& obj) //Overloaded << operator
{
	output  << "name: " << obj.name << ", age: " << obj.age << ", weight: " << obj.weight;
	return output; 
}