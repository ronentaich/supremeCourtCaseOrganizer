// Specification file for the DList class

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "ListNode.h"

template <class T>
class DList{
private:

    ListNode<T> *head;
    int count;
    
public:
    DList();   // Constructor
    
    // Linked list operations
    int getCount() const { return count; }
    bool isEmpty() const { return !count;}
    void insertNode(T&);
    bool deleteNode(T&);
    bool searchList(T&) const;
    void destroyList(); // Deletes Nodes, but not T objects
    void freeList(); // Deletes all memory
    void writeItems(std::ostream&, void display(std::ostream&, T&)); // traverses the DList and writes each item to the stream using the function pointer
    ListNode<T>* operator[](const int&); // traverses the DList, and returns the desired ListNode treating the first node as index 0
};



//**************************************************
// Constructor for DList
// Allocates and initializes a sentinel node for the cicular doubly linked list
// head.next and head.prev point to head
//**************************************************
template <class T>
DList<T>::DList()
{
    head = new ListNode<T>();
    head->setNext(head);
    head->setPrev(head);
    count = 0;
}


// SearchList function requires only one parameter
// and returns true if found while copying the data into the parameter
template <class T>
bool DList<T>::searchList(T& target) const
{
    ListNode<T>* pCur = head->getNext();

    while (pCur != head && *(pCur->getItemPointer()) < target) {
        pCur = pCur->getNext();
    }

    if (pCur != head && *(pCur->getItemPointer()) == target)
    {
        target = *pCur->getItemPointer();
        return true;
    }

    return false;
}

// Function deletes all memory allocated including the T object memory
template<class T>
 void DList<T>::freeList()
{
    ListNode<T>* pCur;
    //cout << "DUBUG - This list had " << count << " nodes" << endl;
    pCur = head->getNext();
    while (pCur != head)
    {
        pCur = pCur->getNext();
        //cout << "DEBUG - Destructor: Now deleting " << pCur->getPrev()->getItemPointer()->getName() << endl;
        delete pCur->getPrev()->getItemPointer();
        delete pCur->getPrev();
    }
    // cout << "DEBUG - Destructor: Now deleting the sentinel node: " << endl;
    delete head;
}

// Function traverses the list and outputs to the stream using the function pointer
template <class T>
void DList<T>::writeItems(std::ostream& outstream, void display(std::ostream&, T&))
{
    ListNode<T>* pCur;
    pCur = head->getNext();
    while (pCur != head)
    {
        display(outstream, *(pCur->getItemPointer()));
        pCur = pCur->getNext();
    }
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
//**************************************************
template <class T>
void DList<T>::insertNode(T& dataIn)
{
    ListNode<T>* newNode;
    ListNode<T>* pCur;

    newNode = new ListNode<T>;
    newNode->setItemPointer(&dataIn);
    pCur = head->getNext();
    while (pCur != head && *(pCur->getItemPointer()) < dataIn)
    {
        pCur = pCur->getNext();
    }
    pCur->getPrev()->setNext(newNode);
    newNode->setNext(pCur);
    newNode->setPrev(pCur->getPrev());
    pCur->setPrev(newNode);
    count++;
}

// Function traverses the linked list and returns the node at the index, treating the first item as index 0
template <class T>
ListNode<T>* DList<T>::operator[](const int& index)
{
    ListNode<T>* pCur = head->getNext();
    for (int i = index; i > 0; i--) {
        pCur = pCur->getNext();
    }
    if (pCur == head) // return null ptr if pCur lands on head
        return 0;
    return pCur;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
// In addition, the information will be copied to the parameter
//**************************************************
template <class T>
bool DList<T>::deleteNode(T& target)
{
    ListNode<T>* pCur;
    bool deleted = false;

    pCur = head->getNext();
    while (pCur != head && *(pCur->getItemPointer()) < target)
    {
        pCur = pCur->getNext();
    }

    if (pCur != head && *(pCur->getItemPointer()) == target)
    {
        target = *(pCur->getItemPointer());
        pCur->getPrev()->setNext(pCur->getNext());
        pCur->getNext()->setPrev(pCur->getPrev());
        delete pCur;
        deleted = true;
        count--;
    }
    return deleted;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
// Does not free the memory of the T objects
//**************************************************
template <class T>
void DList<T>::destroyList()
{
    ListNode<T>* pCur;
    //cout << "DUBUG - This list had " << count << " nodes" << endl;
    pCur = head->getNext();
    while (pCur != head)
    {
        pCur = pCur->getNext();
        //cout << "DEBUG - Destructor: Now deleting " << pCur->getPrev()->getItemPointer()->getName() << endl;
        delete pCur->getPrev();
    }
    // cout << "DEBUG - Destructor: Now deleting the sentinel node: " << endl;
    delete head;
}


#endif

