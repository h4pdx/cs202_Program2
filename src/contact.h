/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2
 * contact.h */

/*********************************************************************/
/* This file contains the contact class, which reside inside the addressbook nodes
 * these are seearchable and have the fucntions to manage its own data, coipy itself,
 * create data from input, and return infor to the node and to the tree thru getters 
 * everything else includes this file, downward like a chain, to all have access to the libraries
 * and client side functions */

#ifndef _CONTACT_H_
#define _CONTACT_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <sys/time.h>
using namespace std;

/*********************************************************************/

const int SIZE = 100;
const int NAME = 41; // accidentally truncated a few definitions, but mostly big enough
const int NUM = 11;     // phone number


/*********************************************************************/

class contact
{
    public:
        contact();
        contact(const contact & copyFrom);
        ~contact();
        void clear(); // Explicit destructor
        int create(char*aFirstName,char*aLastName,char*aPhoneNum,char*aUserName);
        // Copy arguments into private data members
        //int create(char * aFirstName, char * aLastName, char * aNum, char * email); // Copy arguments into private data members
        int create(); // reads directly from user
        int display();  // display contents of object
        int copy(const contact & copyFrom);  // Takes populated obj argument and fills data members
        int retrieve(char * matchingLastName, contact & found); // Returns true if match and populates passed in empty obj
        int write(ofstream & fout); // Called by table::writeFile, writes data members to file with ofstream& obj
        int cmpLastName(contact & compareTo);  // Compares the titles of two contact objects
        int cmpLastName(char * compareTo);    // Compares current contact object title with a char keyword, for search
        void formatName(char * aName);
        char *& getFirstName();
        char *& getLastName();
        char *& getNum();
        char *& getUser();
    protected:
        char * firstName;   // First Name
        char * lastName;    // Last Name
        char * phoneNum;    // Phone Number
        char * userName;   // Email Address
};

/*********************************************************************/

// Client-side function prototypes
int mainMenu();
bool again();
bool confirm();
bool backToMenu();
int formatName(char * aName);
//int formatDef(char * aDef);

/*********************************************************************/

#endif //_CONTACT_H_

