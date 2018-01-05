/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2 
 * contact.cpp */

/* CONTACT.H function implementations */

#include "contact.h"

/*********************************************************************/

contact::contact()
{
    firstName = lastName = phoneNum = userName = NULL;
}

//----------------------------------------------------------

contact::contact(const contact & copyFrom)
{
    copy(copyFrom);
}

//----------------------------------------------------------

contact::~contact()
{
    clear();
}

//----------------------------------------------------------

// Explicit destructor, called to clear objects for reuse 
void contact::clear()
{
    if (firstName)
    {
        delete [] firstName;
        firstName = NULL;
    }
    if (lastName)
    {
        delete [] lastName;
        lastName = NULL;
    }
    if (phoneNum)
    {
        delete [] phoneNum;
        phoneNum = NULL;
    }
    if (userName)
    {
        delete [] userName;
        userName = NULL;
    }
}

//----------------------------------------------------------

// creates object data from passed-in arguments
int contact::create(char * aFirstName, char * aLastName, char * aPhoneNum, char * aUserName)
{
    clear();
    if (aFirstName)
    {
        firstName = new char[strlen(aFirstName)+1];
        strcpy(firstName, aFirstName);
    }
    else
        firstName = NULL;
    if (aLastName)
    {
        lastName = new char[strlen(aLastName)+1];
        strcpy(lastName, aLastName);
    }
    else
        lastName = NULL;
    if (aPhoneNum)
    {
        phoneNum = new char[strlen(aPhoneNum)+1];
        strcpy(phoneNum, aPhoneNum);
    }
    else
        phoneNum = NULL;
    if (aUserName)
    {
        userName = new char[strlen(aUserName)+1];
        strcpy(userName, aUserName);
    }
    else
        userName = NULL;
    // check to see if copy was success
    int success = 0;
    if (firstName && lastName && phoneNum && userName)
        ++success;
    return success;
}

//----------------------------------------------------------

// reads input and stores info into its data members.
int contact::create()
{
    clear();
    char aFirstName[NAME], aLastName[NAME], aNum[NUM], aUserName[NAME];
    // Enter the first name
    cout << "\nEnter a first name: ";
    cin.get(aFirstName,NAME,'\n'); cin.ignore(NAME,'\n');
    formatName(aFirstName);
    // Enter a last name
    cout << "\nEnter a last name: ";
    cin.get(aLastName,NAME,'\n'); cin.ignore(NAME,'\n');
    formatName(aLastName);
    // Enter a phone number
    cout << "\nEnter 10-digit Phone number (format #########): ";
    cin.get(aNum, NUM,'\n'); cin.ignore(NUM,'\n');
    // enter an email/username
    cout << "\nEnter an email address: ";
    cin.get(aUserName, NAME,'\n'); cin.ignore(NAME,'\n'); 
    // names are otherwise NULL, so this could return false
    int success = create(aFirstName, aLastName, aNum, aUserName);
    return success;
}

//----------------------------------------------------------

// Called by table::display and from main with a retrieval
int contact::display()
{
    if (!firstName || !lastName)
        return 0;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"
        << lastName << ", " << firstName;
    int len = strlen(phoneNum);
    if (len == 10)
    {
        cout << "\n(";
        for (int i=0;i<3;++i)
            cout << phoneNum[i];
        cout << ")";
        for (int i=3;i<6;++i)
            cout << phoneNum[i];
        cout << "-";
        for (int i=6;i<10;++i)
            cout << phoneNum[i];
    }
    cout << "\n" << userName
        << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return 1;
}

//----------------------------------------------------------

// Copy from passed-in object into object that called it
int contact::copy(const contact & copyFrom) 
{
    clear();
    int success = create(copyFrom.firstName, copyFrom.lastName, copyFrom.phoneNum, copyFrom.userName);
    return success; 
}

//----------------------------------------------------------

// Passes in populated matchingTerm array and empty reference object to be filled
int contact::retrieve(char * keyWord, contact & found)
{
    if (!firstName || !lastName || !keyWord)
        return 0;
    int success = 0;
    // If match will return true
    if (!strcmp(lastName, keyWord))
    {
        found.clear();
        // Copy current object into empty argument
        success = found.copy(*this);
    }
    return success;
}

//----------------------------------------------------------

// Called by table::writeFile to output private data members
int contact::write(ofstream & fout)
{
    // return true if data written to file
    int success = 0;
    if (fout) {
        ++success;
        fout << firstName << ':';
        fout << lastName << ':';
        fout << phoneNum << ':';
        fout << userName << '\n';
    }
    return success;
}

//----------------------------------------------------------

// Allow table access to comparison between object toAdd and root->data
int contact::cmpLastName(contact & compareTo)
{
    return strcmp(lastName,compareTo.lastName);
}

//----------------------------------------------------------

// Compare private contact data to a passed in keyWord in table
int contact::cmpLastName(char * compareTo)
{
    return strcmp(lastName,compareTo);
}

//----------------------------------------------------------

char *& contact::getFirstName()
{
    return firstName;
}

//----------------------------------------------------------

char *& contact::getLastName()
{
    return lastName;
}

//----------------------------------------------------------

char *& contact::getNum()
{
    return phoneNum;
}

//----------------------------------------------------------

char *& contact::getUser()
{
    return userName;
}

//----------------------------------------------------------

// Paves the word as all lower case, then goes through again and capitalizes accordingly
void contact::formatName(char * aName)
{
    if (!aName) return;
    int t = strlen(aName);
    aName[0] = toupper(aName[0]);
    for (int i=1; i < t; ++i)
    {
        aName[i] = tolower(aName[i]);
    }
    for (int i=1; i < t; ++i)
    {
        if (aName[i] == ' ')
        {
            aName[i+1] = toupper(aName[i+1]);
        }
    }
}

/*********************************************************************/

