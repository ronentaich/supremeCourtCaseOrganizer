// Binary Search Tree ADT
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "SupremeCase.h"


template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    BinaryNode<ItemType>* _insertByName(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr);
   
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    BinaryNode<ItemType>* _removeByCitation(BinaryNode<ItemType>* nodePtr,
    const ItemType target, bool & success);
   
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType *& successor);
    BinaryNode<ItemType>* removeRightmostNode(BinaryNode<ItemType>* nodePtr, ItemType*& successor);
   
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    BinaryNode<ItemType>* findNodeByName(BinaryNode<ItemType>* nodePtr, const ItemType& target) const;
   
public:
    // insert a node at the correct location
    bool insert( ItemType& newEntry);
    // remove a node if found
    bool remove( ItemType & anEntry);
    //remove a node if found using secondary key
    bool removeByCitation(const ItemType & target);
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    // find the smallest node
    bool findSmallest(ItemType& smallest);
    //find the largest node
    bool findLargest(ItemType& largest);
    //void arryToTree(Case arr[], int start, int end);
    bool insertByName( ItemType & newEntry);
    bool getEntryByName(const ItemType& anEntry, ItemType& returnedItem) const;
};

///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert( ItemType & newEntry)
{
    ItemType* pointer = &newEntry;
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(pointer);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

//Finds the smallest node in the tree
template <class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType& smallest)
{
    BinaryNode<ItemType>* smallestNode;
    smallestNode = removeLeftmostNode(this->rootPtr, smallest);

    return true;
}

//Finds the largest node in the tree
template <class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType& largest)
{
    BinaryNode<ItemType>* largestNode;
    largestNode = removeRightmostNode(this->rootPtr, largest);

    return true;
}


//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove( ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

//removing items within a tree by comparing the citations
template<class ItemType>
bool BinarySearchTree<ItemType>::removeByCitation(const ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _removeByCitation(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* found = findNode(this->rootPtr, anEntry);

    if (found != NULL)
    {
        returnedItem = found->getItem();
        return true;
    }

    return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntryByName(const ItemType& anEntry, ItemType& returnedItem) const
{
    BinaryNode<ItemType>* found = findNodeByName(this->rootPtr, anEntry);

    if (found != NULL)
    {
        returnedItem = found->getItem();
        return true;
    }

    return false;
}


//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
    {
        nodePtr = newNodePtr;
        this->count++;
        return newNodePtr;
    }
    else
    {
        if (*(nodePtr->getItem()) < *(newNodePtr->getItem()))
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        
        else
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    }

    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insertByName(BinaryNode<ItemType>* nodePtr,
    BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
    {
        nodePtr = newNodePtr;
        this->count++;
        return newNodePtr;
    }
    else
    {
        if (nodePtr->getItem()->getName() < newNodePtr->getItem()->getName())
            nodePtr->setRightPtr(_insertByName(nodePtr->getRightPtr(), newNodePtr));
        else
            nodePtr->setLeftPtr(_insertByName(nodePtr->getLeftPtr(), newNodePtr));
    }

    return nodePtr;
}
//Implementation for the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                            const ItemType&  target) const
{
    BinaryNode<ItemType>* found = NULL;
    BinaryNode<ItemType>* pWalk = nodePtr;

    while (pWalk != NULL && found == NULL)
    {
        if (*(pWalk->getItem()) > target)
            pWalk = pWalk->getLeftPtr();
        else
        {
            if (*(pWalk->getItem()) < target)
                pWalk = pWalk->getRightPtr();
            else
                found = pWalk;
        }
    }

    return found;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNodeByName(BinaryNode<ItemType>* nodePtr,
    const ItemType& target) const
{
    BinaryNode<ItemType>* found = NULL;
    BinaryNode<ItemType>* pWalk = nodePtr;

    while (pWalk != NULL && found == NULL)
    {
        if (pWalk->getItem()->getName() > target.getName())
            pWalk = pWalk->getLeftPtr();
        else
        {
            if (pWalk->getItem()->getName() < target.getName())
                pWalk = pWalk->getRightPtr();
            else
                found = pWalk;
        }
    }

    return found;
}


////////////////////////////////////////////////////////////////////////
// The follwoing functions will be needed for the team project
//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem()->getName() > target.getName())
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem()->getName() < target.getName())
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}


////////////////////////////////////////////////////////////////////////
// The follwoing functions will be needed for the team project
//Implementation of the remove operation by comparing the name (secondary key)
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeByCitation(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem()->getCaseCitation() > target.getCaseCitation())
        nodePtr->setLeftPtr(_removeByCitation(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem()->getCaseCitation() < target.getCaseCitation())
        nodePtr->setRightPtr(_removeByCitation(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}


//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType* newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}
//Implementation to remove the left leaf
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType *& successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}
//Implementation to remove the right leaf
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeRightmostNode(BinaryNode<ItemType>* nodePtr, ItemType*& successor)
{
    if (nodePtr->getRightPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setRightPtr(removeRightmostNode(nodePtr->getRightPtr(), successor));
        return nodePtr;
    }
    
}

template <class ItemType>
bool BinarySearchTree<ItemType>::insertByName( ItemType& newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(&newEntry);
    this->rootPtr = _insertByName(this->rootPtr, newNodePtr);
    return true;
}


#endif
