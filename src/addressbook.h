
/* Ryan Hoover - 3/10/17
 * CS163 - K. Fant
 * PROGRAM 4 
 * addressBook.cpp */

/* Binary Search Tree Function implementations.
 * Recursive Calls kept in private section, public wrappers used for implemenation
 * Stores node object data (contact class) in bst addressBook
 * Search, Remove, Insert, Display ,and efficiency report */

/*********************************************************************/

#ifndef _ADDRESSBOOK_H_
#define _ADDRESSBOOK_H_
#include "contact.h"

/*********************************************************************/

class node
{
    public:
        node();
        node(const node & copyFrom);
        node(const contact & copyFrom);
        ~node();
        void setThis(node * setTo);
        node *& goLeft();
        node *& goRight();
        void connectLeft(node * setTo);
        void connectRight(node * setTo);
        char * getName();
        int display();
        int copyContact(node * & copyFrom);
        int cmpName(char * compareTo);
        int retrieve(char * keyWord, contact & found);
        contact & getContact();
        int create(char*,char*,char*,char*);
        int write(ofstream & fout);
    protected:
        //contact * contactList;
        contact myContact;
        node * left;
        node * right;
};

/*********************************************************************/

class addressBook
{
    public:
        addressBook();        // Read in from external file
        ~addressBook();       // Save to external file
        int insert(contact & toAdd);       // Client program enters new data
        int removeMatch(char * keyWord);    // Search and delete by keyword(title)
        int retrieve(char * keyWord, contact & found);     // Search for data by keyword
        int getHeight();    // Return the height of the tree as an int, used in isEfficient
        bool isEfficient();  // uses getHeight on the subtrees to find balance at each level
        int displayAll();   // In sorted order by keyword
        int displayRange(char * loRange, char * hiRange); // Two arguemnts, display all info between those two (K thru P)
        int removeAll();    // explicit destructor
        int readFile();     // read data from an external file and store it in the addressBook
        int writeFile();    // calls contact::write() in a recursive loop thru the entire tree
    private:
        node * root;    // pointer to node
        int contactCount;  // number of nodes, incremented after each insertion, decremented after each removal
        /* Recursive functions */
        int insert(node * & root, contact & toAdd);
        int removeMatch(node * & root, char * keyWord);
        int removeAll(node * & root);
        int displayAll(node * root);
        int retrieve(node * & root, char * keyWord, contact & found);
        int displayRange(node * root, char * loRange, char * hiRange);
        int getHeight(node * root);
        bool isEfficient(node * root);
        int writeFile(node * root, ofstream & fout);
};

/*********************************************************************/

#endif //_ADDRESSBOOK_H_

