
/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2 
 * communication.cpp *
 * communication.h function implementations */


#include "communication.h"

// Abstract base class constructors
communication::communication() {}
communication::~communication() {}

/*********************************************************************/

textMsg::textMsg()
{
    recipient = message = NULL;
}

//----------------------------------------------------------

textMsg::textMsg(const textMsg & copyFrom)
{
    copy(&copyFrom);
}

//----------------------------------------------------------

textMsg::~textMsg()
{
    clear();
}

//----------------------------------------------------------

// Explicit destructor, called to clear objects for reuse 
void textMsg::clear()
{
    if (recipient)
    {
        delete [] recipient;
        recipient = NULL;
    }
    if (message)
    {
        delete [] message;
        message = NULL;
    }
}

//----------------------------------------------------------

// sends object data from passed-in arguments
int textMsg::send(char * aRecipient, char * aMessage)
{
    clear();
    if (aRecipient)
    {
        recipient = new char[strlen(aRecipient)+1];
        strcpy(recipient, aRecipient);
    }
    else
        recipient = NULL;
    if (aMessage)
    {
        message = new char[strlen(aMessage)+1];
        strcpy(message, aMessage);
    }
    else
        message = NULL;
    // check to see if copy was success
    int success = 0;
    if (recipient && message)
        ++success;
    return success;
}

//----------------------------------------------------------

// reads input and stores info into its data members.
int textMsg::send()
{
    clear();
    char aRecipient[NAME], aMessage[MESSG];
    // Enter the first name
    cout << "\nSending to: ";
    cin.get(aRecipient,NAME,'\n'); cin.ignore(NAME,'\n');
    formatName(aRecipient);
    cout << "\nMessage body: ";
    cin.get(aMessage, MESSG,'\n'); cin.ignore(MESSG,'\n');
    // names are otherwise NULL, so this could return false
    int success = send(aRecipient, aMessage);
    return success;
}

//----------------------------------------------------------

// Called by table::display and from main with a retrieval
int textMsg::display()
{
    if (!recipient && !message)
        return 0;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"
         << "Sent to: " << recipient
         << "\n................\n" << message
         << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return 1;
}

//---------------------------------------------------------

// calls send(create data members) with copyFrom data members
int textMsg::copy(const textMsg * copyFrom) 
{
    clear();
    int success = send(copyFrom->recipient, copyFrom->message);
    return success; 
}

//----------------------------------------------------------

// returns pointer to object, allows for calling routine to dynamically access derived classes
communication * textMsg::copy()const
{
    textMsg * newText = new textMsg;
    newText->copy(this);
    return newText;
}

//----------------------------------------------------------

// Passes in populated matchingTerm array and empty reference object to be filled
int textMsg::retrieve(char * keyWord, communication *& found)
{
    if (!recipient || !keyWord)
        return 0;
    int success = 0;
    // If match will return true
    if (!strcmp(recipient, keyWord)) {
        found->clear();
        // Copy current object into empty argument
        //success = found->copyText(this);
        found = this->copy();
    }
    return success;
}

//----------------------------------------------------------

// Allow table access to comparison between object toAdd and root->data
int textMsg::cmpLastName(textMsg & compareTo)
{
    return strcmp(recipient,compareTo.recipient);
}

//----------------------------------------------------------

// Compare private textMsg data to a passed in keyWord in table
int textMsg::cmpLastName(char * compareTo)
{
    return strcmp(recipient,compareTo);
}

//----------------------------------------------------------

// can be used to input a char into an array outside the scope
char *& textMsg::getRecipient()
{
    return recipient;
}

//----------------------------------------------------------

// Paves the word as all lower case, then goes through again and capitalizes accordingly
void textMsg::formatName(char * aName)
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

// default constructor
email::email()
{
    recipient = subject = message = NULL;
}

//----------------------------------------------------------

email::email(const email & copyFrom)
{
    copy(&copyFrom);
}

//----------------------------------------------------------

email::~email()
{
    clear();
}

//----------------------------------------------------------

// Explicit destructor, called to clear objects for reuse 
void email::clear()
{
    if (recipient)
    {
        delete [] recipient;
        recipient = NULL;
    }
    if (subject)
    {
        delete [] subject;
        subject = NULL;
    }
    if (message)
    {
        delete [] message;
        message = NULL;
    }
}

//----------------------------------------------------------

// sends object data from passed-in arguments
int email::send(char * aRecipient, char * aSubject, char * aMessage)
{
    clear();
    if (aRecipient)
    {
        recipient = new char[strlen(aRecipient)+1];
        strcpy(recipient, aRecipient);
    }
    else
        recipient = NULL;
    if (aSubject)
    {
        subject = new char[strlen(aRecipient)+1];
        strcpy(subject, aSubject);
    }
    else
        subject = NULL;
    if (aMessage)
    {
        message = new char[strlen(aMessage)+1];
        strcpy(message, aMessage);
    }
    else
        message = NULL;
    // check to see if copy was success
    int success = 0;
    if (recipient && message)
        ++success;
    return success;
}

//----------------------------------------------------------

// reads input and stores info into its data members.
int email::send()
{
    clear();
    char aRecipient[NAME], aMessage[MESSG], aSubject[NAME];
    // Enter the first name
    cout << "\nSending to: ";
    cin.get(aRecipient,NAME,'\n'); cin.ignore(NAME,'\n');
    formatName(aRecipient);
    cout << "Subject: ";
    cin.get(aSubject, NAME, '\n'); cin.ignore(NAME,'\n');
    cout << "\nMessage body: ";
    cin.get(aMessage, MESSG,'\n'); cin.ignore(MESSG,'\n');
    // names are otherwise NULL, so this could return false
    int success = send(aRecipient, aSubject, aMessage);
    return success;
}

//----------------------------------------------------------

// Called by table::display and from main with a retrieval
int email::display()
{
    if (!recipient && !message)
        return 0;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"
         << "Sent to: " << recipient
         << "\nSubject: " << subject
         << "\n................\n" << message
         << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return 1;
}

//---------------------------------------------------------

// Copy from passed-in object into object that called it
int email::copy(const email * copyFrom) 
{
    clear();
    // send fucntion can be used for copying
    int success = send(copyFrom->recipient, copyFrom->subject, copyFrom->message);
    return success; 
}

// copies itself into an empty object and returns that value
communication * email::copy()const
{
    email * newEmail = new email;
    newEmail->copy(this);
    return newEmail;
}

//----------------------------------------------------------

// Passes in populated matchingTerm array and empty reference object to be filled
int email::retrieve(char * keyWord, communication *& found) {
    if (!recipient || !keyWord)
        return 0;
    int success = 0;
    // If match will return true
    if (!strcmp(recipient, keyWord)) {
        found->clear();
        // empty object is assigned the value of the this->copy() return value
        found = this->copy();
    }
    return success;
}

//----------------------------------------------------------

// Allow table access to comparison between object toAdd and root->data
int email::cmpLastName(email & compareTo)
{
    return strcmp(recipient,compareTo.recipient);
}

//----------------------------------------------------------

// Compare private email data to a passed in keyWord in table
int email::cmpLastName(char * compareTo)
{
    return strcmp(recipient,compareTo);
}

//----------------------------------------------------------

// can be used to input a char into an array outside the scope
char *& email::getRecipient()
{
    return recipient;
}

//----------------------------------------------------------

// Paves the word as all lower case, then goes through again and capitalizes accordingly
void email::formatName(char * aName)
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
// default constructor
msgBoard::msgBoard()
{
    postID = 0;
    userName = message = NULL;
}

//----------------------------------------------------------

// copy constructor
msgBoard::msgBoard(const msgBoard & copyFrom)
{
    copy(&copyFrom);
}

//----------------------------------------------------------

// implicit destructor, just calls explicit
msgBoard::~msgBoard()
{
    clear();
}

//----------------------------------------------------------

// Explicit destructor, called to clear objects for reuse 
void msgBoard::clear()
{
    if (postID)
    {
        postID = 0;
    }
    if (userName)
    {
        delete [] userName;
        userName = NULL;
    }
    if (message)
    {
        delete [] message;
        message = NULL;
    }
}

//----------------------------------------------------------

// sends object data from passed-in arguments
int msgBoard::send(int aPostID, char * aUserName ,char * aMessage)
{
    clear();
    if (aPostID)
    {
        postID = aPostID;
    }
    if (aUserName)
    {
        userName = new char[strlen(aUserName)+1];
        strcpy(userName, aUserName);
    }
    else
        userName = NULL;
    if (aMessage)
    {
        message = new char[strlen(aMessage)+1];
        strcpy(message, aMessage);
    }
    else
        message = NULL;
    // check to see if copy was success
    int success = 0;
    if (postID && message)
        ++success;
    return success;
}

//----------------------------------------------------------

// reads input and stores info into its data members.
int msgBoard::send()
{
    clear();
    char aMessage[MESSG], aUserName[NAME];
    int aPostID;
    do {
        aPostID = rand() % 100000;
    } while(aPostID == 0);
    cout << "\nUser Name (@email address): ";
    cin.get(aUserName, NAME, '\n'); cin.ignore(NAME, '\n');
    // Enter the first name
    cout << "\nWrite your post: ";
    cin.get(aMessage, MESSG,'\n'); cin.ignore(MESSG,'\n');
    // names are otherwise NULL, so this could return false
    int success = send(aPostID, aUserName, aMessage);
    return success;
}

//----------------------------------------------------------

// Called by table::display and from main with a retrieval
int msgBoard::display()
{
    if (!postID && !userName && !message) return 0;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"
         << "\nPost ID: " << postID
         << "\nUser " << userName << " said:"
         << "\n................\n" << message
         << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return 1;
}

//---------------------------------------------------------

// Copy from passed-in object into object that called it
int msgBoard::copy(const msgBoard * copyFrom) 
{
    clear();
    // send fucntion can be used for copying
    int success = send(copyFrom->postID, copyFrom->userName, copyFrom->message);
    return success; 
}

//---------------------------------------------------------

// copies itself into an empty object and returns that value
communication * msgBoard::copy()const
{
    msgBoard * newPost = new msgBoard;
    newPost->copy(this);
    return newPost;
}

//----------------------------------------------------------

// Passes in populated matchingTerm array and empty reference object to be filled
int msgBoard::retrieve(char * keyWord, communication *& found) {
    if (!userName || !keyWord)
        return 0;
    int success = 0;
    // If match will return true
    if (!strcmp(userName, keyWord)) {
        found->clear();
        // empty object is assigned the value of the this->copy() return value
        found = this->copy();
    }
    return success;
}

//----------------------------------------------------------

// Allow table access to comparison between object toAdd and root->data
int msgBoard::cmpLastName(msgBoard & compareTo)
{
    return strcmp(userName,compareTo.userName);
}

//----------------------------------------------------------

// Compare private msgBoard data to a passed in keyWord in table
int msgBoard::cmpLastName(char * compareTo)
{
    return strcmp(userName ,compareTo);
}

//----------------------------------------------------------

// can be used to input a char into an array outside the scope
char *& msgBoard::getRecipient()
{
    return userName;
}

//----------------------------------------------------------

// Paves the word as all lower case, then goes through again and capitalizes accordingly
void msgBoard::formatName(char * aName)
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


postMail::postMail()
{
    postage = 0;
    recipient = address = message = NULL;
}

//----------------------------------------------------------

postMail::postMail(const postMail & copyFrom)
{
    copy(&copyFrom);
}

//----------------------------------------------------------

postMail::~postMail()
{
    clear();
}

//----------------------------------------------------------

// Explicit destructor, called to clear objects for reuse 
void postMail::clear()
{
    if (recipient)
    {
        delete [] recipient;
        recipient = NULL;
    }
    if (address)
    {
        delete [] address;
        address = NULL;
    }
    if (message)
    {
        delete [] message;
        message = NULL;
    }
}

//----------------------------------------------------------

// sends object data from passed-in arguments
int postMail::send(int aPostage, char * aRecipient, char * aAddress, char * aMessage)
{
    clear();
    if (aPostage)
    {
        postage = aPostage;
    }
    if (aRecipient)
    {
        recipient = new char[strlen(aRecipient)+1];
        strcpy(recipient, aRecipient);
    }
    else
        recipient = NULL;
    if (aAddress)
    {
        address = new char[strlen(aAddress)+1];
        strcpy(address, aAddress);
    }
    else
        address = NULL;
    if (aMessage)
    {
        message = new char[strlen(aMessage)+1];
        strcpy(message, aMessage);
    }
    else
        message = NULL;
    // check to see if copy was success
    int success = 0;
    if (postage && recipient && address && message)
        ++success;
    return success;
}

//----------------------------------------------------------

// reads input and stores info into its data members.
int postMail::send()
{
    clear();
    char aMessage[MESSG], aRecipient[NAME], aAddress[MESSG];
    int aPostage;
    // apply a random number for postage
    do {
        aPostage = rand() % 1000;
    } while(aPostage == 0);
    // fill out char *s
    cout << "\nWho is the letter for: ";
    cin.get(aRecipient, NAME, '\n'); cin.ignore(NAME, '\n');
    cout << "\nTheir Address: ";
    cin.get(aAddress, MESSG,'\n'); cin.ignore(MESSG,'\n');
    cout << "\nLetter contents: ";
    cin.get(aMessage, MESSG,'\n'); cin.ignore(MESSG,'\n');
    // names are otherwise NULL, so this could return false
    int success = send(aPostage, aRecipient, aAddress, aMessage);
    return success;
}

//----------------------------------------------------------

// Called by inbox::display and from main with a retrieval
int postMail::display()
{
    if (!postage && !recipient && !address && !message) return 0;
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"
         << "\nPostage applied (stamp #): " << postage
         << "\nSend letter to " << recipient
         << "\nAddress: " << address
         << "\n................\n" << message
         << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    return 1;
}

//---------------------------------------------------------

// Copy from passed-in object into object that called it
int postMail::copy(const postMail * copyFrom) 
{
    clear();
    // send fucntion can be used for copying
    int success = send(copyFrom->postage, copyFrom->recipient, copyFrom->address, copyFrom->message);
    return success; 
}

//---------------------------------------------------------

// copies itself into an empty object and returns that newly filled object
communication * postMail::copy()const
{
    postMail * newMail = new postMail;
    newMail->copy(this);
    return newMail;
}

//----------------------------------------------------------

// Passes in populated matchingTerm array and empty reference object to be filled
int postMail::retrieve(char * keyWord, communication *& found) {
    if (!recipient || !keyWord)
        return 0;
    int success = 0;
    // If match will return true
    if (!strcmp(recipient, keyWord)) {
        found->clear();
        // empty object is assigned the value of the this->copy() return value
        found = this->copy();
    }
    return success;
}

//----------------------------------------------------------

// Allow table access to comparison between object toAdd and root->data
int postMail::cmpLastName(postMail & compareTo)
{
    return strcmp(recipient,compareTo.recipient);
}

//----------------------------------------------------------

// Compare private postMail data to a passed in keyWord in table
int postMail::cmpLastName(char * compareTo)
{
    return strcmp(recipient, compareTo);
}

//----------------------------------------------------------

// can be used to input a char into an array outside the scope
char *& postMail::getRecipient()
{
    return recipient;
}

//----------------------------------------------------------

// Paves the word as all lower case, then goes through again and capitalizes accordingly
void postMail::formatName(char * aName)
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

