/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	This program creates an ArrayBag class template which is an array of items of any type.
	The program can find union, intersection, and difference of two arrays of the same type.
*/

#include <iostream>
#include <vector>

using namespace std;

template <class T>

class ArrayBag {
private:
	static const int DEFAULT_CAPACITY = 100; //default capacity
	T items[DEFAULT_CAPACITY]; //array of bag items
	int itemCount; //current count of bag items
	int maxItems; //maximum capacity of the bag
	int getIndexOf(const T& target) const; //returns index of a specific item in a bag
public:
	ArrayBag(); //default constructor
	int getCurrentSize()const; //returns the number of items in the bag
	bool isEmpty()const; //checks if the bag is empty
	bool add(const T& newEntry); //adds a new item to a bag that is not full
	bool remove(const T& anEntry); //removes an item from a bag
	void clear(); //clears a bag 
	bool contains(const T& anEntry) const; //checks if a bag has a specific item
	int getFrequencyOf(const T& anEntry) const; //returns the number of times a given object occurs in a bag
	vector <T> toVector() const; //adds a bag's entries to a vector
	ArrayBag <T> Union(const ArrayBag<T> bag); //returns a bag containing the combined contents of the original two bags
	int leastFrequency(int freq, int freq2); //tells which bag has the same item repeating more times
	ArrayBag <T> Intersection(const ArrayBag<T> bag); //returns a new bag containing the entries that occur in both of the original two bags
	ArrayBag <T> Difference(const ArrayBag<T> bag); //returns a new bag containing the entries that would be left in one bag after removing those that also occur in the second
};

void display(ArrayBag<int>& bag); //displays contents of an integer bag

int main() {

	//Creating a bag of integers and placing items in it
	ArrayBag<int> bag1;
	bag1.add(1);
	bag1.add(3);
	bag1.add(3);
	bag1.add(2);
	bag1.add(9);
	bag1.add(2);

	//Displaying items in the bag
	cout << "Bag1"; 
	display(bag1);

	//Creating a second bag of integers and placing items in it
	ArrayBag<int> bag2;
	bag2.add(2);
	bag2.add(7);
	bag2.add(4);
	bag2.add(3);
	bag2.add(3);

	//Displaying items in the bag2
	cout << "Bag2"; 
	display(bag2);
	cout << endl;

	//Creating a union of bag1 and bag2
	ArrayBag<int> bag3;
	bag3 = bag1.Union(bag2);

	//Displaying items in the union bag
	cout << "Union Bag";
	display(bag3);
	cout << endl;

	//Creating an intersection of bag1 and bag2
	ArrayBag<int> bag4;
	bag4 = bag1.Intersection(bag2);

	//Displaying items in the intersection bag
	cout << "Intersection Bag";
	display(bag4);
	cout << endl;

	//Creating a difference of bag1 and bag2
	ArrayBag<int> bag5;
	bag5 = bag1.Difference(bag2);

	//Displaying items in the difference bag
	cout << "Difference Bag";
	display(bag5);
	cout << endl;

	system("pause");
	return 0;
}

template<class T>
int ArrayBag<T>::getIndexOf(const T& target) const //returns the index of a specific item in a bag
{
	bool found = false;
	int result = -1;
	int searchIndex = 0;

	while (!found && (searchIndex < itemCount))
	{
		if (items[searchIndex] == target) //if the item matches our target we set result to the item's index
		{
			found = true;
			result = searchIndex;
		}
		else
		{
			searchIndex++; //if not, continue to look
		} 
	} 
	return result;
}

template<class T>
ArrayBag<T>::ArrayBag() //default constructor
{
	itemCount = 0;
	maxItems = DEFAULT_CAPACITY;
}

template<class T>
int ArrayBag<T>::getCurrentSize() const //returns the number of items in the bag
{
	return itemCount;
}

template<class T>
bool ArrayBag<T>::isEmpty() const //checks if the bag is empty
{
	return itemCount == 0; 
}

template<class T>
bool ArrayBag<T>::add(const T& newEntry) //adds a new item to a bag that is not full
{
	bool hasRoom = itemCount < maxItems; 
	if (hasRoom) { //if there is room in the bag, we can add more items
		items[itemCount] = newEntry;
		itemCount++;
	}
	return hasRoom;
}

template<class T>
bool ArrayBag<T>::remove(const T& anEntry) //removes an item from a bag
{
	int locatedIndex = getIndexOf(anEntry);
	bool canRemove = !isEmpty() && (locatedIndex > -1); //checks if the bag is not empty and if entry is valid

	if (canRemove) {
		itemCount--;
		items[locatedIndex] = items[itemCount]; //swaps the "removed" item with the last item in the bag
	}
	return canRemove; 
}

template<class T>
void ArrayBag<T>::clear() //clears a bag 
{
	itemCount = 0;
}

template<class T>
bool ArrayBag<T>::contains(const T& anEntry) const //checks if a bag has a specific item
{
	bool found = false;
	int curIndex = 0;
	while (!found && (curIndex < itemCount)) {
		if (anEntry == items[curIndex]) { //returns true if the bag2 has the same item as bag1
			found = true;
		}
		else
			curIndex++; //if not, continue comparing other items
	}
	return found;
}

template<class T>
int ArrayBag<T>::getFrequencyOf(const T& anEntry) const //returns the number of times a given object occurs in a bag
{
	int frequency = 0;
	int curIndex = 0;
	while (curIndex < itemCount) {
		if (items[curIndex] == anEntry) { //increases frequency if the bag2 has the same item as bag1
			frequency++;
		}
		curIndex++;
	}
	return frequency;
} 

template<class T>
vector<T> ArrayBag<T>::toVector() const //adds a bag's entries to a vector
{
	vector<T> bagContents;
	for (int i = 0; i < itemCount; i++) {
		bagContents.push_back(items[i]);
	}
	return bagContents;
}

template<class T>
ArrayBag<T> ArrayBag<T>::Union(const ArrayBag<T> bag) //returns a new bag containing the combined contents of the original two bags
{
	ArrayBag <T> unionBag; //creates a new bag

	for (int i = 0; i < getCurrentSize(); i++) {
		unionBag.add(items[i]); //adds items from the first bag
	}
	for (int i = 0;i < bag.getCurrentSize();i++) {
		unionBag.add(bag.items[i]); //adds items from the second bag
	}

	return unionBag;
}

template<class ItemType>
int ArrayBag<ItemType>::leastFrequency(int freq, int freq2) { //tells which bag has the same item repeating more times
	if (freq > freq2) {
		return freq2;
	}
	return freq;
}

template<class T>
ArrayBag<T> ArrayBag<T>::Intersection(ArrayBag<T> bag) //returns a new bag containing the entries that occur in both of the original two bags
{
	ArrayBag<T> intersectionBag; //creates a new bag

	for (int i = 0; i < getCurrentSize(); i++) {
		int need = leastFrequency(getFrequencyOf(items[i]), bag.getFrequencyOf(items[i])); //how many times one item repeats
		int have = intersectionBag.getFrequencyOf(items[i]); //how many times the item already repeats in the new bag

		for (int j = have; j < need; j++) { //repeat the item as many times as we need
			intersectionBag.add(items[i]);
		}
	}

	return intersectionBag;
}


template<class T>
ArrayBag<T> ArrayBag<T>::Difference(const ArrayBag<T> bag) 
{
	ArrayBag<T> differenceBag;

	for (int i = 0; i < getCurrentSize(); i++) { 
		differenceBag.add(items[i]);
	}

	ArrayBag<T> intersectionBag = differenceBag.Intersection(bag); 
	vector<int> bagItems = intersectionBag.toVector();

	for (int i = 0; i < intersectionBag.getCurrentSize(); i++) { 
		differenceBag.remove(bagItems[i]);
	}

	return differenceBag;
}

void display(ArrayBag<int>& bag) //displays contents of an integer bag
{
	cout << " contains " << bag.getCurrentSize() << " items: ";
	
	vector<int> bagItems = bag.toVector(); //adds the bag's entries to a vector 
	int numberOfEntries = (int)bagItems.size(); //gets the size of the bag
	
	for (int i = 0; i < numberOfEntries; i++) { //prints bag's items
		cout << bagItems[i] << " ";
	}
	cout << endl;
}
