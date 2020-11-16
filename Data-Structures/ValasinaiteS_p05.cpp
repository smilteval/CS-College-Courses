/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	This program performs 5 sorting algorithms: bubble, select, insert, merge, and quick
	on integer and double arrays of 100, 1 000, 10 000, 100 000, and 500 000 elements.
	It also calculates the running time of each algorithm.
*/

#include <iostream>
#include <algorithm> //swap
#include <cstdlib>
#include <ctime>
#include <chrono> //timer

using namespace std;
using namespace std::chrono;

//Function prototypes
template <class T>
void bubbleSort(T a[], int n);

template <class T>
void selectSort(T a[], int n);

template <class T>
void insertSort(T a[], int n);

template <class T>
void merge(T a[], int left, int middle, int right);
template <class T>
void mergeSort(T a[], int left, int right);

template <class T>
int partition(T a[], int low, int high);
template <class T>
void quickSort(T a[], int low, int high);

void initIntArray(int a[], int n); //Initializes an integer array
void initDblArray(double a[], int n); //Initializes a double array

template<class T>
void printArray(T a[], int n); //Prints out an array

int generateRandomInt(int max); //Generates a random integer from 1 to max
double generateRandomDouble(); //Generates a random double from 1.0 to 1000.0

int main() {
	srand((unsigned)time(0));	

	//Creating pointers for dynamic arrays
	int* arrBubble;
	int* arrSelect;
	int* arrInsert;
	int* arrMerge;
	int* arrQuick;
	double* arrBubbleDouble;
	double* arrSelectDouble;
	double* arrInsertDouble;
	double* arrMergeDouble;
	double* arrQuickDouble;

	cout << "\n INTEGER ARRAYS \n";
	cout << "________________________________________________\n\n";

	for (int i = 10; i <= 1000000; i *= 10) {

		if (i == 1000000) { //uses 500k instead of 1m
			i /= 2;
		}

		//Creating and initializing dynamic integer arrays of i elements
		arrBubble = new int[i];
		arrSelect = new int[i];
		arrInsert = new int[i];
		arrMerge = new int[i];
		arrQuick = new int[i];
		initIntArray(arrBubble, i);
		initIntArray(arrSelect, i);
		initIntArray(arrInsert, i);
		initIntArray(arrMerge, i);
		initIntArray(arrQuick, i);

		//Testing sorting algorithms with integer arrays of 10 elements
		if (i == 10) {
			cout << "TESTING... \n\n";

			cout << "BubbleSort: \n\n";
			cout << "Initial integer array: "; 
			printArray(arrBubble, i);
			bubbleSort(arrBubble, i);
			cout << " Sorted integer array: ";
			printArray(arrBubble, i);

			cout << "\nSelectSort: \n\n";
			cout << "Initial integer array: "; 
			printArray(arrSelect, i);
			selectSort(arrSelect, i);
			cout << " Sorted integer array: ";
			printArray(arrSelect, i);

			cout << "\nInsertSort: \n\n";
			cout << "Initial integer array: "; 
			printArray(arrInsert, i);
			insertSort(arrInsert, i);
			cout << " Sorted integer array: ";
			printArray(arrInsert, i);
			
			cout << "\nMergeSort: \n\n";
			cout << "Initial integer array: "; 
			printArray(arrMerge, i);
			mergeSort(arrMerge, 0, i-1);
			cout << " Sorted integer array: ";
			printArray(arrMerge, i);
			
			cout << "\nQuickSort: \n\n";
			cout << "Initial integer array: ";
			printArray(arrQuick, i);
			quickSort(arrQuick, 0, i-1);
			cout << " Sorted integer array: ";
			printArray(arrQuick, i);
			
			cout << "________________________________________________\n";
			cout << "\nCALCULATING RUNNING TIME...\n";

			continue; //skip the time counting for array of 10 elements
		}

		//Calculating algorithms' running time on integer arrays with i elements

		cout << endl << i << " elements: \n\n";

		//Bubble Sort
		auto startArrBubble = high_resolution_clock::now();
		bubbleSort(arrBubble, i);
		auto stopArrBubble = high_resolution_clock::now();
		auto durationArrBubble = duration_cast<milliseconds>(stopArrBubble - startArrBubble);
		cout << "Time taken by the bubbleSort: " << durationArrBubble.count() << " milliseconds\n";

		//Selection Sort
		auto startArrSelect = high_resolution_clock::now();
		selectSort(arrSelect, i);
		auto stopArrSelect = high_resolution_clock::now();
		auto durationArrSelect = duration_cast<milliseconds>(stopArrSelect - startArrSelect);
		cout << "Time taken by the selectSort: " << durationArrSelect.count() << " milliseconds\n";

		//Insertion Sort
		auto startArrInsert = high_resolution_clock::now();
		insertSort(arrInsert, i);
		auto stopArrInsert = high_resolution_clock::now();
		auto durationArrInsert = duration_cast<milliseconds>(stopArrInsert - startArrInsert);
		cout << "Time taken by the insertSort: " << durationArrInsert.count() << " milliseconds\n";

		//Merge Sort
		auto startArrMerge = high_resolution_clock::now();
		mergeSort(arrMerge, 0, i-1);
		auto stopArrMerge = high_resolution_clock::now();
		auto durationArrMerge = duration_cast<milliseconds>(stopArrMerge - startArrMerge);
		cout << "Time taken by the mergeSort: " << durationArrMerge.count() << " milliseconds\n";

		//Quick Sort
		auto startArrQuick = high_resolution_clock::now();
		quickSort(arrQuick, 0, i-1);
		auto stopArrQuick = high_resolution_clock::now();
		auto durationArrQuick = duration_cast<milliseconds>(stopArrQuick - startArrQuick);
		cout << "Time taken by the quickSort: " << durationArrQuick.count() << " milliseconds\n";

		//Releases memory allocated for the integer arrays
		delete[]arrBubble;
		delete[]arrSelect;
		delete[]arrInsert;
		delete[]arrMerge;
		delete[]arrQuick;
	}

	cout << "________________________________________________\n";
	cout << "\n DOUBLE ARRAYS \n";
	cout << "________________________________________________\n\n";

	for (int i = 10; i <= 1000000; i *= 10) {

		if (i == 1000000) { //uses 500k instead of 1m
			i /= 2;
		}

		//Creating and initializing dynamic double arrays of i elements
		arrBubbleDouble = new double[i];
		arrSelectDouble = new double[i];
		arrInsertDouble = new double[i];
		arrMergeDouble = new double[i];
		arrQuickDouble = new double[i];
		initDblArray(arrBubbleDouble, i);
		initDblArray(arrSelectDouble, i);
		initDblArray(arrInsertDouble, i);
		initDblArray(arrMergeDouble, i);
		initDblArray(arrQuickDouble, i);

		//Testing sorting algorithms with double arrays of 10 elements
		if (i == 10) {
			cout << "TESTING... \n\n";

			cout << "BubbleSort: \n";
			cout << "\nInitial double array: ";
			printArray(arrBubbleDouble, i);
			bubbleSort(arrBubbleDouble, i);
			cout << " Sorted double array: ";
			printArray(arrBubbleDouble, i);

			cout << "\nSelectSort: \n";
			cout << "\nInitial double array: "; 
			printArray(arrSelectDouble, i);
			selectSort(arrSelectDouble, i);
			cout << " Sorted double array: ";
			printArray(arrSelectDouble, i);

			cout << "\nInsertSort: \n";
			cout << "\nInitial double array: ";
			printArray(arrInsertDouble, i);
			insertSort(arrInsertDouble, i);
			cout << " Sorted double array: ";
			printArray(arrInsertDouble, i);

			cout << "\nMergeSort: \n";
			cout << "\nInitial double array: ";
			printArray(arrMergeDouble, i);
			mergeSort(arrMergeDouble, 0, i - 1);
			cout << " Sorted double array: ";
			printArray(arrMergeDouble, i);

			cout << "\nQuickSort: \n";
			cout << "\nInitial double array: "; 
			printArray(arrQuickDouble, i);
			quickSort(arrQuickDouble, 0, i - 1);
			cout << " Sorted double array: ";
			printArray(arrQuickDouble, i);

			cout << "________________________________________________\n";
			cout << "\nCALCULATING RUNNING TIME...\n";

			continue; //skip the time counting for array of 10 elements
		}

		cout << endl << i << " elements: \n\n";

		//Bubble Sort
		auto startArrBubbleDouble = high_resolution_clock::now();
		bubbleSort(arrBubbleDouble, i);
		auto stopArrBubbleDouble = high_resolution_clock::now();
		auto durationArrBubbleDouble = duration_cast<milliseconds>(stopArrBubbleDouble - startArrBubbleDouble);
		cout << "Time taken by the bubbleSort: " << durationArrBubbleDouble.count() << " milliseconds\n";

		//Selection Sort
		auto startArrSelectDouble = high_resolution_clock::now();
		selectSort(arrSelectDouble, i);
		auto stopArrSelectDouble = high_resolution_clock::now();
		auto durationArrSelectDouble = duration_cast<milliseconds>(stopArrSelectDouble - startArrSelectDouble);
		cout << "Time taken by the selectSort: " << durationArrSelectDouble.count() << " milliseconds\n";

		//Insertion Sort
		auto startArrInsertDouble = high_resolution_clock::now();
		insertSort(arrInsertDouble, i);
		auto stopArrInsertDouble = high_resolution_clock::now();
		auto durationArrInsertDouble = duration_cast<milliseconds>(stopArrInsertDouble - startArrInsertDouble);
		cout << "Time taken by the insertSort: " << durationArrInsertDouble.count() << " milliseconds\n";

		//Merge Sort
		auto startArrMergeDouble = high_resolution_clock::now();
		mergeSort(arrMergeDouble, 0, i - 1);
		auto stopArrMergeDouble = high_resolution_clock::now();
		auto durationArrMergeDouble = duration_cast<milliseconds>(stopArrMergeDouble - startArrMergeDouble);
		cout << "Time taken by the mergeSort: " << durationArrMergeDouble.count() << " milliseconds\n";

		//Quick Sort
		auto startArrQuickDouble = high_resolution_clock::now();
		quickSort(arrQuickDouble, 0, i - 1);
		auto stopArrQuickDouble = high_resolution_clock::now();
		auto durationArrQuickDouble = duration_cast<milliseconds>(stopArrQuickDouble - startArrQuickDouble);
		cout << "Time taken by the quickSort: " << durationArrQuickDouble.count() << " milliseconds\n";

		//Releases memory allocated for the double arrays
		delete[]arrBubbleDouble;
		delete[]arrSelectDouble;
		delete[]arrInsertDouble;
		delete[]arrMergeDouble;
		delete[]arrQuickDouble;
	}

	system("pause");
	return 0;
}

//Function definitions

template <class T>
void bubbleSort(T a[], int n) { //sorts an array by comparing adjacent items and exchanging them if they are out of order
	for (int i = 1;i < n;i++) {
		for (int j = 0;j < n - i;j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}

template <class T>
void selectSort(T a[], int n) { //sorts an array by repeatedly finding the minimum element from unsorted part and putting it at the beginning
	int minIndex = 0;
	for (int i = 0;i < n;i++) {
		minIndex = i;
		for (int j = i + 1;j < n;j++) {
			if (a[j] < a[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(a[minIndex], a[i]);
		}
	}
}

template <class T>
void insertSort(T a[], int n) { //sorts an array by splitting it into a sorted and an unsorted part
								//values from the unsorted part are picked and placed at the correct position in the sorted part
	int loc;
	for (int i = 1;i < n;i++) {
		T next = a[i];
		loc = i;
		while (loc > 0 && a[loc - 1] > next) {
			a[loc] = a[loc - 1];
			loc--;
		}
		a[loc] = next;
	}
}

template <class T>
void merge(T a[], int left, int middle, int right) //merges the two halves of an array
{
	int size1 = middle - left + 1;
	int size2 = right - middle;
	T* leftTemp = new T[size1];
	T* rightTemp = new T[size2];
  
	for (int i = 0; i < size1; i++) {
		leftTemp[i] = a[left + i];
	}
	for (int j = 0; j < size2; j++) {
		rightTemp[j] = a[middle + 1 + j];
	}

	int i = 0, j = 0;
	int k = left;

	while (i < size1 && j < size2){
		if (leftTemp[i] <= rightTemp[j]){
			a[k] = leftTemp[i];
			i++;
		}
		else{
			a[k] = rightTemp[j];
			j++;
		}
		k++;
	}
	while (i < size1){
		a[k] = leftTemp[i];
		i++;
		k++;
	}
	while (j < size2){
		a[k] = rightTemp[j];
		j++;
		k++;
	}
}

template <class T>
void mergeSort(T a[], int left, int right){ //sorts an array by dividing the array into two halves and calling itself for those two halves and merging them
	if (left < right){
		int middle = left + (right - left) / 2;

		mergeSort(a, left, middle);
		mergeSort(a, middle + 1, right);
		merge(a, left, middle, right);
	}
}

template <class T>
int partition(T a[], int low, int high){ //takes last element as pivot, places its element at correct position in sorted array, 
										 //and places all smaller values than the pivot to the left of if and all greater - to the right
	T pivot = a[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++){
		if (a[j] < pivot){
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[high]);
	return (i + 1);
}

template <class T>
void quickSort(T a[], int low, int high){ //sorts an array by picking an element as pivot and partitions the given array around it
	if (low < high){
		int pi = partition(a, low, high);
  
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high);
	}
}

void initIntArray(int a[], int n) { //Initializes an integer array
	for (int i = 0;i < n;i++) {
		a[i] = generateRandomInt(n);
	}
}

void initDblArray(double a[], int n) { //Initializes a double array
	for (int i = 0;i < n;i++) {
		a[i] = generateRandomDouble();
	}
}

template<class T>
void printArray(T a[], int n) { //Prints out an array
	for (int i = 0;i < n;i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int generateRandomInt(int max) { //generates a random integer from 1 to max
	return rand() * rand() % max + 1; //RAND_MAX = 32767 was too small for this program, so multiply it with itself to get a larger number
}

double generateRandomDouble() {//generates a random double from 1.0 to 1000.0
	return 1.0 + (double)rand() / RAND_MAX * (1000.0-1.0);
}