// Specification file for ListNode class
// Written By: Alan Kashiwagi
// IDE: Visual Studio

#ifndef LISTNODE_H
#define LISTNODE_H
#include "SupremeCase.h"

template <class T>
class ListNode {
private:
    T* itemPointer = 0;
    ListNode* next = NULL;
    ListNode* prev = NULL;
public:

    //getters
    T* getItemPointer() { return itemPointer; }
    ListNode* getNext() { return next; }
    ListNode* getPrev() { return prev; }

    //setters
    void setItemPointer(T* theItem) { itemPointer = theItem; }
    void setNext(ListNode* nextPtr) { next = nextPtr; }
    void setPrev(ListNode* prevPtr) { prev = prevPtr; }
};

#endif
