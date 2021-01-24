// Specification file for the HashList class
// Written By: Alan Kashiwagi
// IDE: Visual Studio

#ifndef HASH_H
#define HASH_H
#include "DList.h"
#include <iostream>
#include <fstream>

template <class T>
class HashList {
private:
    DList<T>* list;
    int size;

    // Hash function requires object conversion to string
    void hash(int&, string);
public:
    HashList();
    HashList(int);

    // Builds the list
    void createHash(int);

    // Manualy destroys the list
    void freeHash(); // Frees all memory
    void destroyHash(); // Frees memory for the DLists and Nodes but not T objects

    // Rehash
    void rehash(HashList<T>& oldlist);

    // Getters
    int getCollide();
    double getLoad();
    int getSize() { return size; }

    // Operations
    void insert(T&);
    bool search(T&);
    bool deleteItem(T&);
    void writeList(std::ostream&, void display(std::ostream&, T&));

    // Overloaded operator
    DList<T>& operator[](const int&);

};

// Constructor
template <class T>
HashList<T>::HashList() {
    list = 0;
    size = -1;
}
// Overloaded constructor allocates the hash array with size = s
template <class T>
HashList<T>::HashList(int s) {
    size = s;
    list = new DList<T>[size];
}

// Function deletes memory except leaves the T objects intact
template <class T>
void HashList<T>::destroyHash() {
     for (int i = size - 1; i >= 0; i--) {
         list[i].destroyList();
     }
     delete[] list;
}

 // Function inserts each pointer from the oldList into the current list
 template <class T>
 void HashList<T>::rehash(HashList<T> &oldList) {
     for (int i = oldList.getSize() - 1; i >= 0; i--) {
         for (int j = oldList[i].getCount() - 1; j >= 0; j--) {
             this->insert(*(oldList[i][j]->getItemPointer()));
         }
     }
 }
// Function dynamically allocates the hash array of DList objects with size = s
 template <class T>
void HashList<T>::createHash(int s) {
    size = s;
    list = new DList<T>[size];
}

// Function deletes all the memory allocated in the list including the T objects
template<class T>
void HashList<T>::freeHash()
{
    for (int i = size - 1; i >= 0; i--) {
        list[i].freeList();
    }
    delete[] list;
}

// Function traverses the HashList and outputs each T object to the stream using the function pointer
template <class T>
void HashList<T>::writeList(std::ostream& stream, void display(std::ostream&, T&))  {
    for (int i = 0; i < size; i++) {
        list[i].writeItems(stream, display);
    }
}

// Function returns the DList in the HashList at the index
template <class T>
DList<T>& HashList<T>::operator[](const int& index) {
    return list[index];
}

// Function calculates number of collisions
template <class T>
int HashList<T>::getCollide() {
    int num = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].getCount() > 1) { // Only count DLists with more than one item
            num += (list[i].getCount() - 1);
        }
    }
    return num;
}

// Function calculates load factor
template <class T>
double HashList<T>::getLoad() {
    double load = 0;
    for (int i = 0; i < size; i++) {
        load += !!list[i].getCount(); // add 1 if a list has a size greater than zero
    }
    return load/size*100;
}

// Hash function will convert the T object to a string and generate a key
// Key = sum of (char + index)^2
template <class T>
void HashList<T>::hash(int& key, string s) {
        for (unsigned i = 0; i < s.length(); i++) {
        key += (s[i] + i) * (s[i] + i);
    }
    key = key % size;
}

// Worse hash function
// Key = sum of (char)
//template <class T>
//void HashList<T>::hash(int& key, T& item) {
//    string s = item;
//    for (unsigned i = 0; i < s.length(); i++) {
//        key += s[i];
//    }
//    key = key % size;
//}

// Function generates a key for the T object, then inserts the pointer into the hash array
template <class T>
void HashList<T>::insert(T& newItem) {
    int key = 0;
    hash(key, newItem);
    list[key].insertNode(newItem);
}

// Function deletes the T object from the hash array while copying the item into the parameter
template <class T>
bool HashList<T>::deleteItem(T& target){
    int key = 0;
    hash(key, target);
    if (list[key].deleteNode(target))
        return true;
    return false;
}

// Function searches for the T object in the hash array and copies it into the parameter
template <class T>
bool HashList<T>::search(T& target) {
    int key = 0;
    hash(key, target);
    if (list[key].searchList(target))
        return true;
    return false;
}

#endif
