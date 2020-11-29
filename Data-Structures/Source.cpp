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

// Link-based binary tree class
template<class T>
class Tree {
private:
    BNode<T>* root;
    int gHeiHlp(BNode<T>* subTr) const; // get tree height recursive helper method
    int gNumOfNodesHlp(BNode<T>* subTr) const; // get number of nodes recursive helper method
    BNode<T>* balancedAdd(BNode<T>*& subTr, BNode<T>* nNode); //removes a target value from the tree
    BNode<T>* cpyTree(const BNode<T>* oldRt) const; //copies the tree rooted at oldRt and return ponter to the copy
    void destroyTree(BNode<T>*& subTr); //recursively deletes all nodes from the tree
    //Traversals
    void preorder(void visit(T&), BNode<T>* tr) const;
    void inorder(void visit(T&), BNode<T>* tr) const;
    void postorder(void visit(T&), BNode<T>* tr) const;
public:
    Tree() : root(NULL) { } // default ctor
    Tree(const T& rtItem) : root(new BNode<T>(rtItem, NULL, NULL)) {} //1 param ctor
    Tree(const T& rtItem, const BNode<T>*& lTr, const BNode<T>*& rTr) //3 param ctor
        : root(new BNode<T>(rtItem, cpyTree(lTr->root), cpyTree(rTr->root))) {}
    Tree(const Tree<T> & rhs) { root = cpyTree(rhs.root); } //copy ctor
    ~Tree() { destroyTree(root); }

    bool isEmpty() const { return root == NULL; } //checks if the tree is empty
    int gHei() const { return gHeiHlp(root); } //gets tree height
    int gNumOfNodes() const { return gNumOfNodesHlp(root); } //gets the number of nodes
    T gRtData() const throw(PrecondViolatedExcept); //gets root data
    void sRtData(const T& nData); //sets root data
    bool add(const T& nData); //calls balancedAdd(), adds a node
    void clear() { destroyTree(root); root = NULL; }
    BNode<T>* gEntHlp(BNode<T>* subTr,const T& target)const; //finds the location of an entry in the tree
    T gEnt(const T& anEnt) const throw(NotFoundExcept); // get entry
    //Traversals
    void preTrav(void visit(T&)) const { preorder(visit, root); }
    void inTrav(void visit(T&)) const { inorder(visit, root); }
    void postTrav(void visit(T&)) const { postorder(visit, root); }
};

//Function declaration
void visit(int& entry);

//---------------------------MAIN START---------------------------

int main() {

    //Testing default ctor, isEmpty(), and gRtData()
    Tree<int> tr1; 
    cout << "Tree1 is empty: " << tr1.isEmpty() << endl;
    cout << "Tree1 root: ";
    try {
        cout << tr1.gRtData() << endl;
    }
    catch (PrecondViolatedExcept error) {
        cout << error.what() << endl;
    }

    //Testing 1 param ctor
    Tree<int> tr2(10);
    cout << "Tree2 root: ";
    cout << tr2.gRtData() << endl;
  
    //Testing copy ctor
    Tree<int> tr3(tr2); 
    cout << "Tree3 root: ";
    cout << tr3.gRtData() << endl;

    //Testing sRtData()
    cout << "Tree3 root after setting root to 3: ";
    tr3.sRtData(3);
    cout << tr3.gRtData() << endl << endl;

    //Testing add()
    tr1.add(1);
    tr1.add(3);
    tr1.add(5);
    tr1.add(7);
    tr1.add(9);

    //Testing gHei()
    cout << "Tree1 height: " << tr1.gHei() << endl;

    //Testing gNumOfNodes()
    cout << "Tree1 # of nodes: " << tr1.gNumOfNodes() << endl;

    //Testing gEnt()
    cout << "Tree1 gEnt(9): ";
    try {
        cout << tr1.gEnt(9) << endl;
    }
    catch (NotFoundExcept error) {
        cout << error.what() << endl;
    }

    //Testing pre/in/post-order traversals
    cout << "Tree1 pre-order: ";
    tr1.preTrav(visit);
    cout << "\nTree1 in-order: ";
    tr1.inTrav(visit);
    cout << "\nTree1 post-order: ";
    tr1.postTrav(visit);

    //Testing clear()
    cout << "\nTree1 after clear: ";
    tr1.clear();
    cout << tr1.gNumOfNodes();

	system("pause");
	return 0;
}

//---------------------------MAIN END-----------------------------

void visit(int& entry)
{
    cout << entry << " ";
}

template<class T>
int Tree<T>::gHeiHlp(BNode<T>* subTr) const
{
    if (subTr == nullptr) {
        return 0;
    }
    else {
        return 1 + max(gHeiHlp(subTr->lChild), gHeiHlp(subTr->rChild));
    }
}

template<class T>
int Tree<T>::gNumOfNodesHlp(BNode<T>* subTr) const
{
    if (subTr == nullptr) {
        return 0;
    }
    else {
        return (1 + gNumOfNodesHlp(subTr->lChild) + gNumOfNodesHlp(subTr->rChild));
    }
}

template<class T>
BNode<T>* Tree<T>::balancedAdd(BNode<T>*& subTr, BNode<T>* nNode)
{
    if (subTr == nullptr) {
        return nNode; 
    }
    else {
        BNode<T>* lPtr = subTr->lChild;
        BNode<T>* rPtr = subTr->rChild;
        if (gHeiHlp(lPtr) > gHeiHlp(rPtr)) {
            rPtr = balancedAdd(rPtr, nNode);
            subTr->rChild = rPtr;
        }
        else {
            lPtr = balancedAdd(lPtr, nNode);
            subTr->lChild = lPtr;
        }
        return subTr;
    }
}

template<class T>
BNode<T>* Tree<T>::cpyTree(const BNode<T>* oldRt) const
{
    BNode<T>* nTree = nullptr;
    if (oldRt != nullptr) {
        nTree = new BNode<T>(oldRt->item, nullptr, nullptr);
        nTree->lChild = cpyTree(oldRt->lChild);
        nTree->rChild = cpyTree(oldRt->rChild);
    }
    return nTree;
}

template<class T>
void Tree<T>::destroyTree(BNode<T>*& subTr)
{
    if (subTr != nullptr) {
        destroyTree(subTr->lChild);
        destroyTree(subTr->rChild);
        delete subTr;
        subTr = nullptr;
    }
}

template<class T>
BNode<T>* Tree<T>::gEntHlp(BNode<T>* subTr, const T& target) const
{
    if (subTr != nullptr) {
        if (subTr->item == target) {
            return subTr;
        }
        else if(subTr->item > target){
            return gEntHlp(subTr->lChild, target);
        }
        else {
            return gEntHlp(subTr->rChild, target);
        }
    }
}

template<class T>
void Tree<T>::preorder(void visit( T&), BNode<T>* tr) const
{
    if (tr != nullptr) {
        T anItem = tr->item;
        visit(anItem);
        preorder(visit, tr->lChild);
        preorder(visit, tr->rChild);
    }
}

template<class T>
void Tree<T>::inorder(void visit(T&), BNode<T>* tr) const
{
    if (tr != nullptr) {
        inorder(visit, tr->lChild);
        T anItem = tr->item;
        visit(anItem);
        inorder(visit, tr->rChild);
    }
}

template<class T>
void Tree<T>::postorder(void visit(T&), BNode<T>* tr) const
{
    if (tr != nullptr) {
        postorder(visit, tr->lChild);
        postorder(visit, tr->rChild);
        T anItem = tr->item;
        visit(anItem);
    }
}

template<class T>
T Tree<T>::gRtData() const throw(PrecondViolatedExcept)
{
    if (root == nullptr) {
        throw(PrecondViolatedExcept("gRtData() called with an empty tree."));
    }
    else {
        return root->item;
    }
}

template<class T>
void Tree<T>::sRtData(const T& nData)
{
    if (root == nullptr) {
        root = new BNode<T>(nData);
    }
    else {
        root->item = nData;
    }
}

template<class T>
bool Tree<T>::add(const T& nData)
{
    BNode<T>* nn = new BNode<T>(nData);
    root = balancedAdd(root, nn);
    return true;
}

template<class T>
T Tree<T>::gEnt(const T& anEnt) const throw(NotFoundExcept)
{
    BNode<T>* nd = gEntHlp(root, anEnt);
    if (nd == nullptr) {
        throw NotFoundExcept("The entry was not found in the tree.");
    }
    else {
        return nd->item;
    }
}