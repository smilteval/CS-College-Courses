/*
	Smilte Valasinaite
	CSC 326 Fall 2020

	Program Description:
	This program creates link-based stack, queue, and deque class templates.
	It also includes two functions to identify letter-by-letter	and word-by-word
	palindromes using the classes mentioned above.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <algorithm>

using namespace std;

//PRECONDITION VIOLATED EXCEPTION CLASS

class PrecondViolatedExcept : public logic_error {
public:
	PrecondViolatedExcept(const string& msg = "") : logic_error("Precondition Violated Exception: " + msg) {}
};

//SINGLE-LINK NODE CLASS

template< class T>
class Node
{
private:
	T item;
	Node<T>* next;
public:
	Node() : next(nullptr) {}
	Node(const T& anItem) : item(anItem), next(nullptr) {}
	Node(const T& anItem, Node<T>* nextNodePtr) : item(anItem), next(nextNodePtr) {}
	void setItem(const T& anItem) { item = anItem; }
	void setNext(Node<T>* nextNodePtr) { next = nextNodePtr; }
	T getItem() const { return item; }
	Node<T>* getNext() const { return next; }
};

//DOUBLE-LINK NODE CLASS

template<class T>
class Dnode {
	T item;
	Dnode<T>* next;
	Dnode<T>* prev;
public:
	Dnode() :next(nullptr), prev(nullptr) { }
	Dnode(const T& anItem) :next(nullptr), prev(nullptr), item(anItem) { }
	Dnode(const T& anItem, Dnode<T>* nextNodePtr, Dnode<T>* prevNodePtr) :next(nextNodePtr), prev(prevNodePtr), item(anItem) { }
	void setItem(const T& anItem) { item = anItem; }
	void setNext(Dnode<T>* nextNodePtr) { next = nextNodePtr; }
	void setPrev(Dnode<T>* prevNodePtr) { prev = prevNodePtr; }
	T getItem() const { return item; }
	Dnode<T>* getNext() const { return next; }
	Dnode<T>* getPrev() const { return prev; }
};

//LINKED STACK CLASS DECLARATION

template <class T>
class LkdStack {
private:
	Node <T>* topPtr; //points to the top of the stack
public:
	LkdStack(); //default ctor
	LkdStack(const LkdStack<T>& rhs); //copy ctor
	~LkdStack(); //dtor
	bool isEmpty()const; //checks if the stack is empty
	bool push(const T& newItem); //adds an item to the stack
	bool pop(); //removes an item from the stack
	T peek()const throw(PrecondViolatedExcept); //shows the item on top of the stack
};

//LINKED QUEUE CLASS DECLARATION

template <class T>
class LkdQueue {
private:
	Node<T>* front; //points to the front of the queue
	Node<T>* back; //points to the back of the queue
public:
	LkdQueue(); //default ctor
	LkdQueue(const LkdQueue& rhs); //copy ctor
	~LkdQueue(); //dtor
	bool isEmpty() const; //checks if the queue is empty
	bool enqueue(const T& newEntry); //adds an item to the queue
	bool dequeue(); //removes an item from the queue
	T peekFront() const throw(PrecondViolatedExcept); //shows the item in the front of the queue
	T peekBack() const throw(PrecondViolatedExcept); //shows the item in the back of the queue
};

//LINKED DOUBLE-ENDED QUEUE CLASS DECLARATION

template <class T>
class LkdDeque {
private:
	Dnode<T>* front; //points to the front of the deque
	Dnode<T>* back; //points to the back of the deque
public:
	LkdDeque(); //default ctor
	LkdDeque(const LkdDeque<T>& rhs); //copy ctor
	~LkdDeque(); //dtor
	bool isEmpty() const; //checks if the deque is empty
	bool enqueueFront(const T& newEntry); //adds an item to the deque from the front
	bool enqueueBack(const T& newEntry); //adds an item to the deque from the back
	bool dequeueFront(); //removes an item from the deque from the front
	bool dequeueBack(); //removes an item from the deque from the back
	T peekFront()const throw(PrecondViolatedExcept); //shows the item in the front of the deque
	T peekBack()const throw(PrecondViolatedExcept); //shows the item in the back of the deque
}; 

//FUNCTION DECLARATIONS

bool letterPalindrome1(string str); //finds a letter-based palindrome using link-based stack and queue
bool letterPalindrome2(string str); //finds a letter-based palindrome using link-based deque
bool wordPalindrome1(string str); //finds a word-based palindrome using link-based stack and queue
bool wordPalindrome2(string str); //finds a word-based palindrome using link-based deque

//-------------------------------MAIN-------------------------------

int main() {

	string str1 = "I am going for a walk";
	string str2 = "Was it a car or a cat I saw";
	string str3 = "I really want coffee right now";
	string str4 = "Stressed was I ere I saw desserts";
	string str5 = "We can turn pizza into code";
	string str6 = "Was it a car or a cat I saw?";
	string str7 = "What is sleep?";
	string str8 = "You can cage a swallow, can't you, but you can't swallow a cage, can you?";

	//Testing letter palindrome using stack and queue
	cout << "letterPalindrome1:\n";

	if (letterPalindrome1(str1)) 
		cout << str1 << " is a palindrome\n";
	else 
		cout << str1 << " is not a palindrome\n";

	if (letterPalindrome1(str2))
		cout << str2 << " is a palindrome\n";
	else
		cout << str2 << " is not a palindrome\n";

	//Testing letter palindrome using deque
	cout << "\nletterPalindrome2:\n";

	if (letterPalindrome2(str3))
		cout << str3 << " is a palindrome\n";
	else
		cout << str3 << " is not a palindrome\n";

	if (letterPalindrome2(str4))
		cout << str4 << " is a palindrome\n";
	else
		cout << str4 << " is not a palindrome\n";

	//Testing word palindrome using stack and queue
	cout << "wordPalindrome1:\n";

	if (wordPalindrome1(str5))
		cout << str5 << " is a palindrome\n";
	else
		cout << str5 << " is not a palindrome\n";

	if (wordPalindrome1(str6))
		cout << str6 << " is a palindrome\n";
	else
		cout << str6 << " is not a palindrome\n";

	//Testing word palindrome using deque
	cout << "\nwordPalindrome2:\n";

	if (wordPalindrome2(str7))
		cout << str7 << " is a palindrome\n";
	else
		cout << str7 << " is not a palindrome\n";

	if (wordPalindrome2(str8))
		cout << str8 << " is a palindrome\n";
	else
		cout << str8 << " is not a palindrome\n";
	
	system("pause");
	return 0;
}

//-------------------------------MAIN-------------------------------

//LINKED STACK CLASS DEFINITION

template<class T>
LkdStack<T>::LkdStack() //default ctor
{
	topPtr = nullptr;
}

template<class T>
LkdStack<T>::LkdStack(const LkdStack<T>& rhs) //copy ctor
{
	Node <T>* oldCurr = rhs.topPtr;
	if (oldCurr == nullptr) {
		topPtr = nullptr;
	}
	else {
		topPtr = new Node<T>(oldCurr->getItem());
		Node<T>* newCurr = topPtr;
		oldCurr = oldCurr->getNext();
		while (oldCurr != nullptr) {
			Node<T>* newNodePtr = new Node<T>(oldCurr->getItem());
			newCurr->setNext(newNodePtr);
			newCurr = newCurr->getNext();
			oldCurr = oldCurr->getNext();
		}
		newCurr->setNext(nullptr);
	}
}

template<class T>
LkdStack<T>::~LkdStack() //dtor
{
	while (!isEmpty()) {
		pop();
	}
}

template<class T>
bool LkdStack<T>::isEmpty() const //checks if the stack is empty
{
	return topPtr == nullptr;
}

template<class T>
bool LkdStack<T>::push(const T& newItem) //adds an item to the stack
{
	Node<T>* newNodePtr = new Node<T>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}

template<class T>
bool LkdStack<T>::pop() //removes an item from the stack
{
	bool result = false;
	if (!isEmpty())
	{
		Node<T>* nodeToDelPtr = topPtr;
		topPtr = topPtr->getNext();
		nodeToDelPtr->setNext(nullptr);
		delete nodeToDelPtr;
		nodeToDelPtr = nullptr;
		result = true;
	}
	return result;
}

template<class T>
T LkdStack<T>::peek() const throw(PrecondViolatedExcept) //shows the item on top of the stack
{
	if (topPtr == nullptr) {
		string msg = "peek() called with an empty stack";
		throw(PrecondViolatedExcept(msg));
	}
	else {
		return topPtr->getItem();
	}
}

//LINKED QUEUE CLASS DEFINITION

template<class T>
LkdQueue<T>::LkdQueue() //default ctor
{
	front = nullptr; 
	back = nullptr; 
}

template<class T>
LkdQueue<T>::LkdQueue(const LkdQueue& rhs) //copy ctor
{
	Node <T>* oldCurr = rhs.front;

	if (oldCurr == nullptr) {
		front = nullptr;
		back = nullptr;
	}
	else {
		front = new Node<T>(oldCurr->getItem());
		Node<T>* newCurr = front;
		oldCurr = oldCurr->getNext();
		while (oldCurr != nullptr) {
			Node<T>* newNodePtr = new Node<T>(oldCurr->getItem());
			newCurr->setNext(newNodePtr);
			newCurr = newCurr->getNext();
			oldCurr = oldCurr->getNext();
			back = newNodePtr;
		}
		newCurr->setNext(nullptr);
	}
}

template<class T>
LkdQueue<T>::~LkdQueue() //dtor
{
	while (!isEmpty()) {
		dequeue();
	}
}

template<class T>
bool LkdQueue<T>::isEmpty() const //checks if the queue is empty
{
	return front == nullptr;
}

template<class T>
bool LkdQueue<T>::enqueue(const T& newEntry) //adds an item to the queue
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (front == nullptr) {
		front = newNodePtr;
	}
	else {
		back->setNext(newNodePtr);
	}
	back = newNodePtr;
	return true;
}

template<class T>
bool LkdQueue<T>::dequeue() //removes an item from the queue
{
	bool result = false;
	if (!isEmpty()) {
		Node <T>* nodeToDelPtr = front;
		if (front == back) {
			front = back = nullptr;
		}
		else {
			front = front->getNext();
		}
		nodeToDelPtr->setNext(nullptr);
		delete nodeToDelPtr;
		result = true;
	}
	return result;
}

template<class T>
T LkdQueue<T>::peekFront() const throw(PrecondViolatedExcept) //shows the item in the front of the queue
{
	if (front == nullptr) {
		string msg = "peekFront() called with an empty queue";
		throw(PrecondViolatedExcept(msg));
	}
	else {
		return front->getItem();
	}
}

template<class T>
T LkdQueue<T>::peekBack() const throw(PrecondViolatedExcept) //shows the item in the back of the queue
{
	if (front == nullptr) {
		string msg = "peekBack() called with an empty queue";
		throw(PrecondViolatedExcept(msg));
	}
	else {
		return back->getItem();
	}
}

//LINKED DOUBLE-ENDED QUEUE CLASS DECLARATION

template<class T>
LkdDeque<T>::LkdDeque() //default ctor
{
	front = nullptr;
	back = nullptr;
}

template<class T>
LkdDeque<T>::LkdDeque(const LkdDeque<T>& rhs) //copy ctor
{
	Dnode <T>* oldCurr = rhs.front;

	if (oldCurr == nullptr) {
		front = nullptr;
		back = nullptr;
	}
	else {
		front = new Dnode<T>(oldCurr->getItem());
		Dnode<T>* newCurr = front;
		oldCurr = oldCurr->getNext();
		while (oldCurr != nullptr) {
			Dnode<T>* newNodePtr = new Dnode<T>(oldCurr->getItem());
			newCurr->setNext(newNodePtr);
			newNodePtr->setPrev(newCurr);
			newCurr = newCurr->getNext();
			oldCurr = oldCurr->getNext();
			back = newNodePtr;
		}
		newCurr->setNext(nullptr);
	}
}

template<class T>
LkdDeque<T>::~LkdDeque() //dtor
{
	while (!isEmpty()) {
		dequeueFront();
	}
}

template<class t>
bool LkdDeque<t>::isEmpty() const //checks if the deque is empty
{
	return front == nullptr;
}

template<class T>
bool LkdDeque<T>::enqueueFront(const T& newEntry) //adds an item to the deque from the front
{
	Dnode<T>* newNode = new Dnode<T>(newEntry);
	if (front == nullptr) {
		front = newNode;
		back = newNode;
	}
	else {
		newNode->setNext(front);
		front->setPrev(newNode);
		front = newNode;
	}
	return true;
}

template<class T>
bool LkdDeque<T>::enqueueBack(const T& newEntry) //adds an item to the deque from the back
{
	Dnode<T>* newNode = new Dnode<T>(newEntry);
	if (front == nullptr) {
		front = newNode;
		back = newNode;
	}
	else {
		newNode->setPrev(back);
		back->setNext(newNode);
		back = newNode;
	}
	return true;
}

template<class T>
bool LkdDeque<T>::dequeueFront() //removes an item from the deque from the front
{
	if (front != nullptr) {
		Dnode<T>* currPtr = front;
		front = front->getNext();
		if (front == nullptr) {
			back = nullptr;
		}
		else {
			front->setPrev(nullptr);
		}
		delete currPtr;
		return true;
	}
	return false;
}

template<class T>
bool LkdDeque<T>::dequeueBack() //removes an item from the deque from the back
{
	if (back != nullptr) {
		Dnode<T>* currPtr = back;
		back = back->getPrev();
		if (back == nullptr) {
			front = nullptr;
		}
		else {
			back->setNext(nullptr);
		}
		delete currPtr;
		return true;
	}
	return false;
}

template<class T>
T LkdDeque<T>::peekFront() const throw(PrecondViolatedExcept) //shows the item in the front of the deque
{
	if (front == nullptr) {
		string msg = "peekFront() called with an empty deque";
		throw(PrecondViolatedExcept(msg));
	}
	else {
		return front->getItem();
	}
}

template<class T>
T LkdDeque<T>::peekBack() const throw(PrecondViolatedExcept) //shows the item in the back of the deque
{
	if (front == nullptr) {
		string msg = "peekBack() called with an empty deque";
		throw(PrecondViolatedExcept(msg));
	}
	else {
		return back->getItem();
	}
}

//FUNCTION DEFINITIONS

bool letterPalindrome1(string str) //finds a letter-based palindrome using link-based stack and queue
{
	LkdQueue<char> queue;
	LkdStack<char> stack;

	int size = str.length();
	
	for (int i = 0;i < size;i++) {
		//adds characters to the queue and stack in lowercase
		queue.enqueue(tolower(str[i]));
		stack.push(tolower(str[i]));
	}

	//compares contents inside stack and queue if they are not empty
	while (!queue.isEmpty() && !stack.isEmpty()) {
		if (queue.peekFront() == stack.peek()) { //if characters are equal
			queue.dequeue(); //removes them and compares the next two
			stack.pop();
		}
		else {
			return false;
		}
	}
	return true;
}

bool letterPalindrome2(string str) //finds a letter-based palindrome using link-based deque
{
	LkdDeque<char> deque;
	
	int size = str.length();

	for (int i = 0;i < size;i++) {
		//adds characters from the back of the queue in lowercase
		deque.enqueueBack(tolower(str[i]));
	}

	//compares contents inside two sides of the deque if more than one char is left
	while (size > 1) { 
		if (deque.peekFront() != deque.peekBack()) { 
			return false;
		}
		else { //if they are equal, removes those values and compares the next two
			deque.dequeueFront();
			deque.dequeueBack();
			size -= 2;
		}
	}
	return true;
}

bool wordPalindrome1(string str) //finds a word-based palindrome using link-based stack and queue
{
	LkdStack<string> stack;
	LkdQueue<string> queue;

	//Removes puctuation marks from the sentence except for '
	int len = str.size();
	for (int i = 0;i < len;i++) {
		if (ispunct(str[i]) && str[i] != '\'') {
			str.erase(i--, 1);
			len = str.size(); //updates the size of the string 
		}
	}

	stringstream sentence(str);
	string word;
	
	//Gets all the words separated by spaces
	while(sentence >> word){
		transform(word.begin(), word.end(), word.begin(), tolower); //makes the string lowercase
		//adds words to the queue and stack
		queue.enqueue(word);
		stack.push(word);
	}
	
	//compares contents inside stack and queue if they are not empty
	while (!queue.isEmpty() && !stack.isEmpty()) {
		if (queue.peekFront() == stack.peek()) { //if the words are equal
			queue.dequeue(); // removes them and compares the next two
			stack.pop();
		}
		else {
			return false;
		}
	}
	return true;
}

bool wordPalindrome2(string str) //finds a word-based palindrome using link-based deque
{
	LkdDeque<string> deque;
	
	//Removes puctuation marks from the sentence except for '
	int len = str.size();
	for (int i = 0;i < len;i++) {
		if (ispunct(str[i]) && str[i] != '\'') {
			str.erase(i--, 1);
			len = str.size(); //updates the size of the string 
		}
	}

	stringstream sentence(str);
	string word;
	int wordCount = 0;

	//Gets all the words separated by spaces
	while (sentence >> word) {
		wordCount++;
		transform(word.begin(), word.end(), word.begin(), tolower); //makes the string lowercase
		//adds words to the deque
		deque.enqueueBack(word);
	}

	//compares contents inside two sides of the deque if more than one word is left
	while (wordCount > 1) {
		if (deque.peekFront() != deque.peekBack()) { 
			return false;
		}
		else { //if they are equal, removes those values and compares the next two
			cout << deque.peekFront() << " ";
			cout << deque.peekBack() << endl;

			deque.dequeueFront();
			deque.dequeueBack();
			wordCount -= 2;
		}
	}
	return true;
}