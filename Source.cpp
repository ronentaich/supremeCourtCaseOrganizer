// main file for implementation and insert/ delete managers

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "HashList.h"
#include "StackADT.h"
#include "BinarySearchTree.h"

using namespace std;

// function prototypes
void saveFile(HashList<Case>*);
void printCase(ostream&, Case&);
void writeCase(ostream&, Case&);
void reHash(HashList<Case>*&);
void readFile(HashList<Case>*, BinarySearchTree<Case>&, BinarySearchTree<Case>&);
void printCase(Case&);


void insertManager(HashList<Case>&, BinarySearchTree<Case>&, BinarySearchTree<Case>&);
void deleteManager(HashList<Case>&, BinarySearchTree<Case>&, BinarySearchTree<Case>&, Stack<Case>&);
void formatCaseName(string&);
void noNumbers(string);
void checkRange(int);
void removeExtraLetters(char);
void searchByCitation(HashList<Case>*, string);
void printListSub();
void searchByName(BinarySearchTree<Case>&);
void printUnSortedList(HashList<Case>*);
void printByCitation(BinarySearchTree<Case>&);
void printByName(BinarySearchTree<Case>&);
void printIndentedTree(BinarySearchTree<Case>&);
void printMenu();


void printMenu()
{
    cout << "Welcome to the Supreme Court Case Project! Please select an option" << endl;
    cout << "==================================================================" << endl;
    cout << "A - Add New Case" << endl;
    cout << "D - Delete Case" << endl;
    cout << "U - Undo Delete" << endl;
    cout << "S - Search Data" << endl;
    cout << "L - List" << endl;
    cout << "X - Statistics" << endl;
    cout << "F - Save to File" << endl;
    cout << "H - Help (Print Menu Again)" << endl;
    cout << "Q - Exit" << endl;
    cout << "------------------------------------------------------------------" << endl;
}

int main() {
    
    // switch function for menu
    char choice = ' ';
    string targetCase = " ";
    BinarySearchTree<Case> citationTree;
    BinarySearchTree<Case> nameTree;

    printMenu();
    
    DList<Case> caseList;
    HashList<Case>* list = new HashList<Case>;
    readFile(list, citationTree, nameTree);
    Stack<Case> deleteStack; // Stack of deleted cases. Cases that are removed are pushed onto this stack
    srand(time(0));
    while(choice!='Q')
    {
        cin >> choice;
        choice=toupper(choice);
    
        removeExtraLetters(choice);
     
    
    switch(choice)
    {
     case 'A':
        //add new case
        insertManager(*list, citationTree, nameTree);
        break;
     
     case 'O':
         //inserts up to twenty random cases
         for (int i = 0; i < 20; i++) {
             int random = rand() % 99999;
             string randomCitation = to_string(random);
             Case * garbage = new Case(randomCitation, "Placeholder Name", "Judge", "OP", 2000);
             if (list->search(*garbage)== false) {
                 list->insert(*garbage);
                 citationTree.insert(*garbage);
                 nameTree.insertByName(*garbage);
                 if (list->getLoad() >= 75) // rehash if load exceeds 75%
                     reHash(list);
                 cout << "  Load Factor: " << setprecision(4) << list->getLoad() << '%' << endl;
             }
             else {
                 delete garbage;
             }
         }
    
         break;

    case 'D':
        //delete case
        deleteManager(*list, citationTree, nameTree, deleteStack);
        break;
    
    case 'U':
        //undo delete
        {
            Case* deletedCase = new Case;
        
            if(deleteStack.isEmpty())
                {
                    
                    cout << "\nYou have not deleted any cases, so there is nothing to undo!" << endl;
                    delete deletedCase;
                }
            else {
                deleteStack.pop(*deletedCase);
                citationTree.insert(*deletedCase);
                nameTree.insertByName(*deletedCase);
                list->insert(*deletedCase);

                cout << "\n" << deletedCase->getName() << " has been inserted back into the project!" << endl;
            }
            break;
        }
     
    case 'S':
        //search(with sub-menu)
            cout << endl;
            cout << "How would you like to search?" << endl;
            cout << "=============================" << endl;
            cout << "A - By Citation" << endl;
            cout << "B - By Name" << endl;
            cout << "-----------------------------" << endl;
            cin >> choice;
            cin.ignore();
            choice = toupper(choice);
            
            switch(choice)
            {
                case 'A':
                {
                    string caseCitation;
                    searchByCitation(list, caseCitation);
                    break;
                }
                case 'B':
                {
                    searchByName(nameTree);
                    break;
                }
                    
            }
            break;
        
    case 'L':
        //list (with sub-menu)
        
            while(!(choice == 'Q'))
            {
                cout << endl;
                printListSub();
                cin >> choice;
                cin.ignore();
                choice = toupper(choice);
            
            
                switch(choice)
                {
                    case 'A':
                    {
                        cout << endl;
                        cout << "Unsorted Hashlist" << endl;
                        cout << "=================" << endl;
                        printUnSortedList(list);
                        break;
                    }
                    case 'B':
                    {
                        cout << endl;
                        cout << "Tree By Citation" << endl;
                        cout << "================" << endl;
                        printByCitation(citationTree);
                        break;
                    }
                    case 'C':
                    {
                        cout << endl;
                        cout << "Tree By Name" << endl;
                        cout << "============" << endl;
                        printByName(nameTree);
                        break;
                    }
                    case 'D':
                    {
                        cout << endl;
                        cout << "Indented Tree By Citation" << endl;
                        cout << "=========================" << endl;
                        printIndentedTree(citationTree);
                        cout << endl;
                        cout << "Indented Tree By Name" << endl;
                        cout << "=====================" << endl;
                        printIndentedTree(nameTree);
                        break;
                    }
                        break;
                }
                break;
            }

        break;
     
    case 'X':
        {
            cout << endl;
            cout << "Statistics" << endl;
            cout << "=====================" << endl;
            cout << "Hash Size: " << list->getSize() << endl;
            cout << "Collisions : " << list->getCollide() << endl;
            cout << "Load Factor: " <<  setprecision(4) << list->getLoad() << '%' << endl;
            cout << "=====================" << endl;
        }
        break;
            
    case 'F':
        {
            Case tempCase;
            while(!deleteStack.isEmpty()){
                deleteStack.pop(tempCase);
            }
            saveFile(list); // look at this function, something needs to be changed
            cout << "------------------------" << endl;
            cout << "The file has been saved!" << endl;
            cout << "------------------------" << endl;
            break;
        }
            
            
    case 'H':
        {
            cout << endl;
            printMenu();
            break;
        }
            
     
    case 'Q':
        {
            cout << "================================" << endl;
            cout << "Thank you for using the program!" << endl;
            cout << "================================" << endl;
            break;
        }
      
    default:
        {
            cout << endl;
            cout << "That is not a valid option. Please enter one of the choices listed above" << endl;
            cout << "========================================================================" << endl;
            break;
        }
            
    }
    
    if(choice!='Q')
        {
            cout << endl;
            cout << "option (press Q to quit): ";
        }
    }
    
    saveFile(list);
    list->freeHash();
    delete list;

    return 0;
} // end of main


/****************************************************************************************
 FUNCTIONS USED WITHIN MAIN AND INSIDE THE SWITCH STATEMENTS
 ****************************************************************************************/

// Function writes the contents of the HashList to the file
void saveFile(HashList<Case>* list) {
    ofstream file("cases.txt"); // overwrites file
    if (!file) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }
    list->writeList(file, writeCase);
}

// Function creates a new HashList and inserts the pointers into the new list
void reHash(HashList<Case>*& oldList) {
    int size = oldList->getSize() * 2;
    int temp = 2;
    while (temp <= size / 2) {
        if (size % temp == 0) {
            size++;
            temp = 2;
        }
        else {
            temp++;
        }
    }
    HashList<Case>* newList = new HashList<Case>(size); // allocate new size list
    newList->rehash(*oldList);
    oldList->destroyHash(); // delete the memory inside the list, but leaves the Case objects intact
    delete oldList;
    oldList = newList; // assign the new list
}

// Function writes the case information in a table
void printCase(ostream& outstream, Case& c) {
    outstream << setw(3) << "" << left << setw(33) << c.getName() << setw(8) << c.getYear() << setw(12) << c.getCaseCitation() << endl;
}

// Function writes the case information as five lines for file operations
void writeCase(ostream& outstream, Case& c) {
    outstream << c;
}

// Function reads from a file and inserts each item into the binary trees and the hash list
/*=== Added BinarySearchTree to parameter list -Jeremy ===*/
void readFile(HashList<Case>* list, BinarySearchTree<Case>& bst1, BinarySearchTree<Case>& bst2) {
    ifstream file("cases.txt");
    if (!file) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    string s;
    int year, lines = 0;
    while (getline(file, s)) { // count number of lines
        lines++;
    }

    int num = lines / 5 * 2;  // five lines for each Case object; then then multiply by two and find the next prime
    int temp = 2;
    while (temp < num) {
        if (num % temp == 0) {
            num++;
            temp = 2;
        }
        temp++;
    }

    list->createHash(num); // build the HashList with array size num
    file.clear();
    file.seekg(0, file.beg);
    for (int i = lines/5; i > 0; i--) {
        Case* item = new Case;
        getline(file, s);
        item->setCaseCitation(s);
        getline(file, s);
        item->setName(s);
        getline(file, s);
        item->setChiefJustice(s);
        getline(file, s);
        item->setOpWriter(s);
        file >> year;
        file.ignore(); // ignore the newline after year
        item->setYear(year);
        list->insert(*item); // insert into HashList
        if (list->getLoad() >= 75)
            reHash(list);
        bst1.insert(*item); // insert into BinarySearchTree
        bst2.insertByName(*item);

    }
}

// function that allows the user to search cases by their name using the nameTree bst
void searchByName(BinarySearchTree<Case>& nameTree)
{
    string name;
    
    while(name!="Q"||name!="q")
    {
        cout << endl;
        cout << "Enter the name of a case (press Q to quit):" << endl;
        cout << "===========================================" << endl;
        getline(cin, name);
        if(name == "Q"||name == "q") {return;}
        
        Case temp("", name, "", "", 0);
        cout << endl;
        Case returned;
        
        while (nameTree.getEntryByName(temp, returned))
        {
            cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl;
            cout << right << setw(8) << "====" << setw(32) << "====" << setw(13) << "========" << endl;
            // Table for printing Cases
            
            printCase(returned);
            cout << endl;
            cout << right << setw(17) << "Chief Justice" << setw(30) << "Opinion Writer" << endl;
            cout << right << setw(17) << "=============" << setw(30) << "==============" << endl;
            cout << setw(3) << "" << left << setw(29) << returned.getChiefJustice() << setw(30) << returned.getOpWriter() << endl << endl << endl;
            nameTree.remove(returned);
            nameTree.getEntryByName(temp, returned);
        }
    }

}


// Function prints the case information in a table (for bst)
void printCase(Case& c)
{
    cout << setw(3) << "" << left << setw(33) << c.getName()  << setw(8) << c.getYear() << setw(12) << c.getCaseCitation() << endl;
}

// this for loop removes all extra letters in the entry and only registers the first one
void removeExtraLetters(char choice)
{
    for(int i=0; i<=sizeof(choice); i++)
    {
        if(i>0)
        cin.ignore(80, '\n');
    }
}

// this function allows the user to search the project using the case citation
void searchByCitation(HashList<Case>* list, string caseCitation)
{
    while(caseCitation!="Q"|| caseCitation!="q")
    {
        cout << "Please enter the citation. Press 'Q' to go back:" << endl;
        cout << "================================================" << endl;
        getline(cin, caseCitation);
        if(caseCitation=="Q"|| caseCitation=="q") {return;}
        
        
        Case neededCase;
        neededCase.setCaseCitation(caseCitation);
        
            if (list->search(neededCase))
                {
                cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl;
                cout << right << setw(8) << "====" << setw(32) << "====" << setw(13) << "========" << endl;
                // Table for printing Cases

                printCase(neededCase);
                cout << endl;
                cout << right << setw(17) << "Chief Justice" << setw(30) << "Opinion Writer" << endl;
                cout << right << setw(17) << "=============" << setw(30) << "==============" << endl;
                cout << setw(3) << "" << left << setw(29) << neededCase.getChiefJustice() << setw(30) << neededCase.getOpWriter() << endl;
                cout << endl;
                }
        
            else
                {
                    cout << "--------------" << endl;
                    cout << "Item Not Found" << endl;
                    cout << "--------------" << endl;
                }
        
    }
}

// this function prints the sub menu for the list option
void printListSub()
{
    cout << "How would you like to see the list? Press Q to go back" << endl;
    cout << "=======================================================" << endl;
    cout << "A - Unsorted" << endl;
    cout << "B - Sorted by citation" << endl;
    cout << "C - Sorted by Name" << endl;
    cout << "D - Sorted as an Indented Tree" << endl;
    cout << "===================================" << endl;
}

// this function prints the list unsorted using a hash list
void printUnSortedList(HashList<Case>* list)
{
    cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl; // Table for printing Cases
    cout << "=====================================================" << endl;
    list->writeList(cout, printCase);
    cout << "-----------------------------------------------------" << endl;
}

// this function prints the cases sorted by citation using a binary search tree
void printByCitation(BinarySearchTree<Case>& citationTree)
{
    cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl; // Table for printing Cases
    cout << "=====================================================" << endl;
    citationTree.inOrder(printCase);
    cout << "-----------------------------------------------------" << endl;
}

// this function prints the cases sorted by their name using a binary search tree
void printByName(BinarySearchTree<Case>& nameTree)
{
    cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl; // Table for printing Cases
    cout << "=====================================================" << endl;
    nameTree.inOrder(printCase);
    cout << "-----------------------------------------------------" << endl;
}

// this function prints the cases in an indented tree a binary search tree using the primary key (citation)
void printIndentedTree(BinarySearchTree<Case>& citationTree)
{
    cout << right << setw(8) << "Name" << setw(32) << "Year" << setw(13) << "Citation" << endl; // Table for printing Cases
    cout << "=====================================================" << endl;
    citationTree.printByLevel(printCase);
    cout << "-----------------------------------------------------" << endl;
}

//formatting function that makes the first letter of the entry capital
void formatCaseName(string &str)
{
    if(!str.empty())
    {
        str[0] = toupper(str[0]); // make first letter uppercase
        for(int i=1; i<str.length(); i++)
        {
            str[i] = tolower(str[i]); // makes the rest of the letters lowercase
            if(str[i] == ' ') // check if there is a space in the string
            {
                if(!(str[i+1] == 'v' && str[i+2] == '.'))
                {
                str[i+1] = toupper(str[i+1]);
                i++;
                }
            }
         }
    }
}


// function that checks to see if there are any numbers in the case name
void noNumbers(string targetString)
{
    for(int count=0; count< targetString.length(); count++) // makes sure there are no numbers in the case name
    {
        while(isdigit(targetString[count]))
        {
            do
            {
                cout << endl;
                cout << "There is a number in your entry. Only use letters: " << endl;
                cout << "==================================================" << endl;
                getline(cin, targetString);
            }
            while(cin.fail());
        }
    }
}

// function that checks the range of the year
void checkRange(int year)
{
    while(year<1700 || year>2020)
    {
        cout << endl;
        cout << "This year is out of range. Enter a year within 1700-2020: " << endl;
        cout << "==========================================================" << endl;
        cin >> year;
        cin.ignore();
    }
}

//this function checks to see if the user entered anything
void validateString(string str)
{
    while(str.empty())
    {
        cout << endl;
        cout << "You haven't entered anything. Please enter again:" << endl;
        cout << "=================================================" << endl;
        getline(cin, str);
    }
}


/********************************************************************************
 INSERT MANAGER AND  DELETE MANAGER
 ********************************************************************************/

// insert manager that manages the addition of new cases
void insertManager(HashList<Case> &list, BinarySearchTree<Case> &citationTree, BinarySearchTree<Case> &nameTree)
{
    string targetCaseName = "";
    string targetCitation = "";
    string targetCheifJustice = "";
    string targetOpWriter = "";
    int targetYear = 0;
    
    while(!(targetCaseName == "Q"||targetCaseName == "q"))
    {
        if(targetCaseName!= "Q")
        cout << "\nEnter the name of the case you would like to add (or Q to quit) : \n";
        cout << "================================================================\n";
        getline(cin,targetCaseName);
        validateString(targetCaseName);
        noNumbers(targetCaseName);
        formatCaseName(targetCaseName);
        
        if(!(targetCaseName == "Q"||targetCaseName == "q"))
        {
            cout << "\nEnter the citation number of the case (or Q to quit) :\n";
            cout << "======================================================\n";
            getline(cin, targetCitation);
            validateString(targetCitation);
            
            cout << "\nEnter the year when the case took place (or Q to quit) : \n";
            cout << "==========================================================\n";
            cin >> targetYear;
            cin.ignore();
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Please enter a valid year:" << endl;
                cout << "==========================" << endl;
                cin>>targetYear;
                cin.ignore();
            }
            checkRange(targetYear);
        
            
        if(!(targetCaseName == "Q"||targetCaseName == "q"))
        {
            cout << "\nEnter the name of the Chief Justice of the case\n";
            cout << "===============================================" << endl;
            getline(cin, targetCheifJustice);
            validateString(targetCheifJustice);
            noNumbers(targetCheifJustice);
            formatCaseName(targetCheifJustice);
        }
        
        if(!(targetCaseName == "Q"||targetCaseName == "q"))
        {
           cout << "\nEnter the name of the Opinion Writer of the case\n";
            cout << "=================================================" << endl;
            getline(cin, targetOpWriter);
            validateString(targetOpWriter);
            noNumbers(targetOpWriter);
            formatCaseName(targetOpWriter);
        }
        
            Case *targetCase = new Case(targetCitation, targetCaseName, targetCheifJustice, targetOpWriter, targetYear);
            
            if(list.search(*targetCase)==true)
            {
                cout << endl;
                cout << "This information is already in the project! It will be rejected." << endl;
                delete targetCase;
            }
            
            else
            {
                list.insert(*targetCase);
                citationTree.insert(*targetCase);
                nameTree.insertByName(*targetCase);
                cout << endl;
                cout << targetCaseName << " has been added to the project!" << endl;
            }
        }
    }
}

// delete manager that manages the deletion of cases
void deleteManager(HashList<Case> &list, BinarySearchTree<Case> &citationTree, BinarySearchTree<Case> &nameTree, Stack<Case> &deleteStack)
{
    string targetCaseName = "";
    string targetCitation;
    string targetCheifJustice;
    string targetOpWriter;
    int targetYear = 0;
    
    while(!(targetCitation == "Q"|| targetCitation == "q"))
    {
        cout << endl;
        cout << "Enter the citation of the case you want to delete(or Q for stop deleting) :" << endl;
        cout  << "===========================================================================" << endl;
        getline(cin, targetCitation);
        
        Case targetCase(targetCitation, targetCaseName, targetCheifJustice, targetOpWriter, targetYear);
        
        if(!(targetCitation == "Q"|| targetCitation == "q"))
        {
            list.search(targetCase);
            if(citationTree.removeByCitation(targetCase) && nameTree.remove(targetCase) && list.deleteItem(targetCase))
            {
                cout << endl;
                cout << "Case " << targetCitation << " has been deleted!\n";
                cout << endl;
                deleteStack.push(targetCase);
            }
            else
            {
                cout << endl;
                cout << "Case " << targetCitation << " was not found in this list. " << endl;
                cout << endl;
            }
        }
        
    }
    
}

