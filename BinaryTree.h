// Binary tree abstract base class
// Created by A. Student
// Modified by: Jeremy Moudy
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"


template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree

public:
    // "admin" functions
     BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType>& tree) { rootPtr = 0; count = 0; }
    virtual ~BinaryTree() { }
   
    // common functions for all binary trees
     bool isEmpty() const    {return count == 0;}
    int size() const        {return count;}
    void clear()            {destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void printCase (ItemType &)) const {_preorder(printCase, rootPtr);}
    void inOrder(void printCase(ItemType &)) const  {_inorder(printCase, rootPtr);}
    void postOrder(void printCase(ItemType &)) const{_postorder(printCase, rootPtr);}
    void BreadthTraversal();
    void printByLevel(void printCase(ItemType&));


    // abstract functions to be implemented by derived class
    virtual bool insert( ItemType & newData) = 0;
    virtual bool remove( ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    virtual BinaryNode<ItemType>* arryToTree(Case* arr[], int start, int end);


private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void printCase(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void printCase(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void printCase (ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printByLevel(void printCase(ItemType &), BinaryNode <ItemType> * nodePtr, int level) const;
   
};

//Public wrapper for printByLevel function
template <class ItemType>
void BinaryTree<ItemType>::printByLevel(void printCase(ItemType&))
{
    int level = 0;
    _printByLevel(printCase, this->rootPtr, level);
}

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr == 0)
        return;

    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());

    cout << "Now deleting: " << nodePtr->getItem().getName() <<endl;
    delete nodePtr;

}

//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void printCase(ItemType &), BinaryNode<ItemType>* nodePtr) const
{

    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        printCase(item);
        _preorder(printCase, nodePtr->getLeftPtr());
        _preorder(printCase, nodePtr->getRightPtr());
    }
}

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void printCase(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType* item = nodePtr->getItem();
        _inorder(printCase, nodePtr->getLeftPtr());
        printCase(*item);
        _inorder(printCase, nodePtr->getRightPtr());
    }
}

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void printCase(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType *item = nodePtr->getItem();
        _postorder(printCase, nodePtr->getLeftPtr());
        _postorder(printCase, nodePtr->getRightPtr());
        printCase(*item);
    }
}

//Prints tree as an indented list level by level
template <class ItemType>
void BinaryTree<ItemType>::_printByLevel(void printCase (ItemType &), BinaryNode <ItemType> * nodePtr, int level) const
{

        if (nodePtr == 0)
            return;

        if (level == 0)
        {
            ItemType* item = nodePtr->getItem();
            printCase(*item);
            level++;
            _printByLevel(printCase, nodePtr->getLeftPtr(), level);
            _printByLevel(printCase, nodePtr->getRightPtr(), level);
        }
        else
        {
            cout << "\t";
            if ((nodePtr->getLeftPtr() == 0) && (nodePtr->getRightPtr() == 0))
                cout << '\t';

            ItemType *item = nodePtr->getItem();
            printCase(*item);
            level++;
            if ((nodePtr->getLeftPtr() != 0) && (nodePtr->getRightPtr() != 0))
                cout << '\t';

            _printByLevel(printCase, nodePtr->getLeftPtr(), level);
            level++;
            if ((nodePtr->getLeftPtr() != 0) && (nodePtr->getRightPtr() != 0))
                cout << '\t';

            _printByLevel(printCase, nodePtr->getRightPtr(), level);
            level++;
            
        }
    
}

//Traverses tree by breadth level
template<class ItemType>
void BinaryTree<ItemType>::BreadthTraversal()
{
    if (rootPtr == NULL)
        return;
    Queue <BinaryNode<ItemType>*> q;
    BinaryNode<ItemType>* pCur = rootPtr;

    q.enqueue(pCur);

    while (!q.isEmpty())
    {
        q.dequeue(pCur);
        ItemType item = pCur->getItem();
        printCase(item);

        if (pCur->getLeftPtr())
        {
            q.enqueue(pCur->getLeftPtr());
        }
        if (pCur->getRightPtr())
        {
            q.enqueue(pCur->getRightPtr());
        }
    }
}

template <class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::arryToTree(Case* arr[], int start, int end)
{
    if (start > end)
        return NULL;
    //cout << "&&&";

    int mid = (start + end) / 2;

    rootPtr->setItem(arr[mid]);

    rootPtr->setLeftPtr(arryToTree(arr, start, (mid - 1)));

    rootPtr->setRightPtr(arryToTree(arr, start, (mid+1)));

    return rootPtr;

}

#endif

