/*
    Smilte Valasinaite
    CSC 326 Fall 2020

    Program Description:
    This program creates a Binary Search Tree class template including
    pre-order, in-order, and post-order methods.
    It also includes algorithm for combining two heaps of arbitrary size.
*/

#include <iostream>
#include <algorithm>

using namespace std;

// NotFoundExcept class
class NotFoundExcept : public logic_error {
public:
    NotFoundExcept(const string& msg = "")
        : logic_error("Target not found: " + msg) { }
};

// PrecondViolatedExcept class
class PrecondViolatedExcept : public logic_error {
public:
    PrecondViolatedExcept(const string& msg = "")
        : logic_error("Precondition violated except: " + msg) { }
};

// Binary tree node class BNode, or Binary Node
template<class T>
class BNode {
public:
    T item;
    BNode<T>* lChild;
    BNode<T>* rChild;
    BNode() : lChild(NULL), rChild(NULL) { }
    BNode(const T& anItem) : item(anItem), lChild(NULL), rChild(NULL) { }
    BNode(const T& anItem, BNode<T>* left, BNode<T>* right) : item(anItem), lChild(left), rChild(right) { }
    bool isLeaf() const {
        if (lChild == NULL && rChild == NULL)
            return true;
        return false;
    }
};

//Binary Search Tree class
template< class T>
class BinarySearchTree {
private:
    BNode<T>* rootPtr;
protected:
    // Recursive helper methods for the public methods.
    BNode<T>* insertInorder(BNode<T>* subTr, BNode<T>* newNode);  //finds where the given node should be placed and inserts it in a leaf at that point
    BNode<T>* findMin(BNode<T>* subTr) const; //finds minimum value in the right subtree
    BNode<T>* removeValue(BNode<T>*& subTr, const T& target, bool& isSuccess); //removes a value from the tree
    BNode<T>* findNode(BNode<T>* subTr, const T& target) const; //returns a pointer to the node containing the given value
    BNode<T>* copyTree(const BNode<T>* oldRt) const; //copies the tree rooted at oldRt and returns ponter to the copy
    int getHeightHelper(BNode<T>* subTr) const; //gets tree height
    int getNumOfNodesHelper(BNode<T>* subTr) const; //gets the number of nodes 
    BNode<T>* getEntryHelper(BNode<T>* subTr, const T& target)const; //finds the location of an entry in the tree   
    void destroyTree(BNode<T>*& subTr); //deletes all nodes from the tree
    void preorder(void visit(T&), BNode<T>* subTr) const; //Visit Left Right
    void inorder(void visit(T&), BNode<T>* subTr) const; //Left Visit Right
    void postorder(void visit(T&), BNode<T>* subTr) const; //Left Right Visit
public:
    BinarySearchTree(); //default ctor
    BinarySearchTree(const T& rootItem); //1 param ctor
    BinarySearchTree(const BinarySearchTree<T>& tree); //copy ctor
    virtual ~BinarySearchTree(); //dtor
    
    bool isEmpty() const; //checks if the tree is empty
    int getHeight() const; //gets tree height
    int getNumberOfNodes() const; //gets the number of nodes
    T getRootData() const throw(PrecondViolatedExcept); //gets the item's value inside the root
    void setRootData(const T& newData); //set the item's value inside the root
    bool add(const T& newEntry); //adds a node to the tree
    bool remove(const T& anEntry); // removes a value from the tree
    void clear(); //clears the tree
    T getEntry(const T& anEntry) const throw(NotFoundExcept); //gets a value of an item
    bool contains(const T& anEntry) const; //checks if the item is in the tree
    void preorderTraverse(void visit(T&)) const; //visit left right
    void inorderTraverse(void visit(T&)) const; //left visit right
    void postorderTraverse(void visit(T&)) const; //left right visit
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& rightHandSide); //overloaded assignment operator
};

//Function definitions

void visit(int& entry); //prints out the node's item
template<class T>
void heapify(T arr[], int n, int idx); //puts maximum value at the root of the tree
template<class T>
void createHeap(T arr[], int n); //creates a max heap 
template<class T>
void combineHeaps(T HeapAB[],T heapA[],T heapB[], int n, int m); //combines two heaps into one

//----------------------------------MAIN----------------------------------

int main() {

    //Testing Binary Search Tree class' methods

    //Testing default ctor, isEmpty(), and getRootData()
    BinarySearchTree<int> bst1;
    cout << "bst1 is empty: " << bst1.isEmpty() << endl;
    cout << "bst1 root: ";
    try {
        cout << bst1.getRootData() << endl;
    }
    catch (PrecondViolatedExcept error) {
        cout << error.what() << endl;
    }

    //Testing 1 param ctor
    BinarySearchTree<int> bst2(10);
    cout << "bst2 root: ";
    cout << bst2.getRootData() << endl;

    //Testing copy ctor
    BinarySearchTree<int> bst3(bst2);
    cout << "bst3 root: ";
    cout << bst3.getRootData() << endl;

    //Testing setRootData()
    cout << "bst3 root after setting root to 3: ";
    bst3.setRootData(3);
    cout << bst3.getRootData() << endl << endl;

    //Testing = op
    cout << "bst3 root after bst3 = bst2: ";
    bst3 = bst2;
    cout << bst3.getRootData() << endl;

    //Testing add()
    bst1.add(1);
    bst1.add(3);
    bst1.add(5);
    bst1.add(7);
    bst1.add(9);

    //Testing getHeight()
    cout << "bst1 height: " << bst1.getHeight() << endl;

    //Testing getNumberOfNodes()
    cout << "bst1 # of nodes: " << bst1.getNumberOfNodes() << endl;

    //Testing getEntry()
    cout << "bst1 getEntry(7): ";
    try {
        cout << bst1.getEntry(7) << endl;
    }
    catch (NotFoundExcept error) {
        cout << error.what() << endl;
    }
    cout << "bst1 getEntry(2): ";
    try {
        cout << bst1.getEntry(2) << endl;
    }
    catch (NotFoundExcept error) {
        cout << error.what() << endl;
    }

    //Testing contains()
    cout << "bst1 contains(3): ";
    cout << bst1.contains(3) << endl;

    //Testing pre/in/post-order traversals
    cout << "\nbst1 pre-order: ";
    bst1.preorderTraverse(visit);
    cout << "\nbst1 in-order: ";
    bst1.inorderTraverse(visit);
    cout << "\nbst1 post-order: ";
    bst1.postorderTraverse(visit);

    //Testing remove()

    cout << "\nbst1 in-order after remove(7): ";
    bst1.remove(7);
    bst1.inorderTraverse(visit);

    //Testing clear()
    cout << "\n\nbst1 after clear (# of nodes): ";
    bst1.clear();
    cout << bst1.getNumberOfNodes() << endl << endl;

    //Testing the algorithm for combining heaps

    int heap1[] = { 10,5,6,2 };
    int heap2[] = { 12,7,9 };

    int combined[7];

    combineHeaps(combined, heap1, heap2, 4, 3);

    cout << "Heap 1: ";
    for (int i = 0;i < 4;i++) {
        cout << heap1[i] << " ";
    }
    cout << "\nHeap 2: ";
    for (int i = 0;i < 3;i++) {
        cout << heap2[i] << " ";
    }
    cout << "\nHeap 1 + Heap 2: ";
    for (int i = 0;i < 7;i++) {
        cout << combined[i] << " ";
    }

    system("pause");
    return 0;
}

//------------------------------MAIN END----------------------------------

template<class T>
BNode<T>* BinarySearchTree<T>::insertInorder(BNode<T>* subTreePtr, BNode<T>* newNode) //finds where the given node should be placed and inserts it in a leaf at that point
{
    if(subTreePtr == nullptr) {
        return newNode;
    }
    else if (subTreePtr->item == newNode->item) {
        return subTreePtr;
    }
    else if (subTreePtr->item > newNode->item) {
        subTreePtr->lChild = insertInorder(subTreePtr->lChild, newNode);
    }
    else {
        subTreePtr->rChild = insertInorder(subTreePtr->rChild, newNode);
    }
    return subTreePtr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::findMin(BNode<T>* subTr) const //finds minimum value in the right subtree
{
    if (subTr == nullptr) {
        return nullptr;
    }

    BNode<T>* curr = subTr;
    while (curr->lChild != nullptr) {
        curr = curr->lChild;
    }

    return curr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::removeValue(BNode<T>*& subTr, const T& target, bool& isSuccess) //removes a value from the tree
{
    if (subTr == nullptr) {
        isSuccess = false;
        return nullptr;
    }
    else if (subTr->item > target) {
        subTr->lChild = removeValue(subTr->lChild, target, isSuccess);
    }
    else if (subTr->item < target) {
        subTr->rChild = removeValue(subTr->rChild, target, isSuccess);
    }
    else {
        //no children
        if (subTr->lChild == nullptr && subTr->rChild == nullptr) {
            delete subTr;
            subTr = nullptr;
            isSuccess = true;
        }
        //one child
        else if (subTr->lChild == nullptr) {
            BNode<T>* tmp = subTr;
            subTr = subTr->rChild;
            delete tmp;
            isSuccess = true;
        }
        else if (subTr->rChild == nullptr) {
            BNode<T>* tmp = subTr;
            subTr = subTr->lChild;
            delete tmp;
            isSuccess = true;
        }
        //two children
        else {
            BNode<T>* tmp = findMin(subTr->rChild);
            subTr->item = tmp->item;
            subTr->rChild = removeValue(subTr->rChild, tmp->item, isSuccess);
        }
    }
    return subTr;
}

template<class T>
BNode<T>* BinarySearchTree<T>::findNode(BNode<T>* treePtr, const T& target) const //returns a pointer to the node containing the given value
{
    if (treePtr == nullptr)
        return nullptr;
    else if (treePtr->item == target)
        return treePtr;
    else if (treePtr->item > target)
        return findNode(treePtr->lChild, target);
    else
        return findNode(treePtr->rChild, target);
}

template<class T>
BNode<T>* BinarySearchTree<T>::copyTree(const BNode<T>* oldRt) const //copies the tree rooted at oldRt and returns ponter to the copy
{
    BNode<T>* nTree = nullptr;
    if (oldRt != nullptr) {
        nTree = new BNode<T>(oldRt->item, nullptr, nullptr);
        nTree->lChild = copyTree(oldRt->lChild);
        nTree->rChild = copyTree(oldRt->rChild);
    }
    return nTree;
}

template<class T>
int BinarySearchTree<T>::getHeightHelper(BNode<T>* subTr) const //gets tree height
{
    if (subTr == nullptr) {
        return 0;
    }
    else {
        return 1 + max(getHeightHelper(subTr->lChild), getHeightHelper(subTr->rChild));
    }
}

template<class T>
int BinarySearchTree<T>::getNumOfNodesHelper(BNode<T>* subTr) const //gets the number of nodes 
{
    if (subTr == nullptr) {
        return 0;
    }
    else {
        return (1 + getNumOfNodesHelper(subTr->lChild) + getNumOfNodesHelper(subTr->rChild));
    }
}

template<class T>
BNode<T>* BinarySearchTree<T>::getEntryHelper(BNode<T>* subTr, const T& target) const //finds the location of an entry in the tree  
{
    if (subTr == nullptr) {
        return nullptr;
    }
    if (subTr->item == target) {
        return subTr;
    }

    BNode<T>* resLeft = getEntryHelper(subTr->lChild, target);

    if (resLeft != nullptr) {
        return resLeft;
    }

    BNode<T>* resRight = getEntryHelper(subTr->rChild, target);
    return resRight;
}

template<class T>
void BinarySearchTree<T>::destroyTree(BNode<T>*& subTr) //deletes all nodes from the tree
{
    if (subTr != nullptr) {
        destroyTree(subTr->lChild);
        destroyTree(subTr->rChild);
        delete subTr;
        subTr = nullptr;
    }
}

template<class T>
void BinarySearchTree<T>::preorder(void visit(T&), BNode<T>* tr) const //Visit Left Right
{
    if (tr != nullptr) {
        T anItem = tr->item;
        visit(anItem);
        preorder(visit, tr->lChild);
        preorder(visit, tr->rChild);
    }
}

template<class T>
void BinarySearchTree<T>::inorder(void visit(T&), BNode<T>* tr) const //Left Visit Right
{
    if (tr != nullptr) {
        inorder(visit, tr->lChild);
        T anItem = tr->item;
        visit(anItem);
        inorder(visit, tr->rChild);
    }
}

template<class T>
void BinarySearchTree<T>::postorder(void visit(T&), BNode<T>* tr) const //Left Right Visit
{
    if (tr != nullptr) {
        postorder(visit, tr->lChild);
        postorder(visit, tr->rChild);
        T anItem = tr->item;
        visit(anItem);
    }
}

template<class T>
BinarySearchTree<T>::BinarySearchTree() //default ctor
{
    rootPtr = nullptr;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const T& rootItem) //1 param ctor
{
    rootPtr = new BNode<T>(rootItem, nullptr, nullptr);
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree) //copy ctor
{
    rootPtr = copyTree(tree.rootPtr);
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() //dtor
{
    destroyTree(rootPtr);
}

template<class T>
bool BinarySearchTree<T>::isEmpty() const //checks if the tree is empty
{
    return rootPtr == nullptr;
}

template<class T>
int BinarySearchTree<T>::getHeight() const //gets tree height
{
    return getHeightHelper(rootPtr);
}

template<class T>
int BinarySearchTree<T>::getNumberOfNodes() const  //gets the number of nodes
{

    return getNumOfNodesHelper(rootPtr);
}

template<class T>
T BinarySearchTree<T>::getRootData() const throw(PrecondViolatedExcept) //gets the item's value inside the root
{
    if (rootPtr == nullptr) {
        throw(PrecondViolatedExcept("getRootData() called with an empty tree."));
    }
    else {
        return rootPtr->item;
    }
}

template<class T>
void BinarySearchTree<T>::setRootData(const T& newData) throw(PrecondViolatedExcept) //sets the item's value inside the root
{
    if (rootPtr == nullptr) {
        rootPtr = new BNode<T>(newData);
    }
    else {
        rootPtr->item = newData;
    }
}

template<class T>
bool BinarySearchTree<T>::add(const T& newEntry) //adds a node to the tree
{
    BNode<T>* newNodePtr = new BNode<T>(newEntry);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    return true;
}

template<class T>
bool BinarySearchTree<T>::remove(const T& anEntry) //removes a value from the tree
{
    bool isSuccess = false;
    rootPtr = removeValue(rootPtr, anEntry, isSuccess);
    return isSuccess;
}

template<class T>
void BinarySearchTree<T>::clear() //clears the tree
{ 
    destroyTree(rootPtr);
}

template<class T>
T BinarySearchTree<T>::getEntry(const T& anEntry) const throw(NotFoundExcept) //gets a value of an item
{
    BNode<T>* nd = getEntryHelper(rootPtr, anEntry);
    if (nd == nullptr) {
        throw NotFoundExcept("The entry was not found in the tree.");
    }
    else {
        return nd->item;
    }
}

template<class T>
bool BinarySearchTree<T>::contains(const T& anEntry) const //checks if the item is in the tree
{
    if (findNode(rootPtr, anEntry) == nullptr) {
        return false;
    }
    return true;
}

template<class T>
void BinarySearchTree<T>::preorderTraverse(void visit(T&)) const //visit left right
{
    preorder(visit, rootPtr);
}

template<class T>
void BinarySearchTree<T>::inorderTraverse(void visit(T&)) const //left visit right
{
    inorder(visit, rootPtr);
}

template<class T>
void BinarySearchTree<T>::postorderTraverse(void visit(T&)) const //left right visit
{
    postorder(visit, rootPtr);
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& rightHandSide) //overloaded assignment operator
{
    if (this != &rightHandSide) {
        if (rootPtr!= nullptr) {
            destroyTree(rootPtr);
        }
        if (rightHandSide.rootPtr == nullptr) {
            rootPtr = nullptr;
        }
        else {
            rootPtr = copyTree(rightHandSide.rootPtr);
        }
    }
    return *this;
}

//function definitions

void visit(int& entry) //prints out the node's item
{
    cout << entry << " ";
}

template<class T>
void heapify(T arr[], int n, int index) //puts maximum value at the root of the tree
{
    if (index >= n) {
        return;
    }
    
    int max;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && arr[left] > arr[index]) {
        max = left;
    }
    else {
        max = index;
    }

    if (right < n && arr[right] > arr[max]) {
        max = right;
    }
       
    if (max != index) {
        swap(arr[max], arr[index]);
        heapify(arr, n, max);
    }
}

template<class T>
void createHeap(T arr[], int n) //creates a max heap 
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

template<class T>
void combineHeaps(T heapAB[], T heapA[], T heapB[], int n, int m) //combines two heaps into one
{
    for (int i = 0; i < n; i++) {
        heapAB[i] = heapA[i];
    }
    for (int i = 0; i < m; i++) {
        heapAB[n + i] = heapB[i];
    }
    
    createHeap(heapAB, n + m);
}