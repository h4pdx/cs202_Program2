
/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2 
 * communication.h */

/* this header file contains the class declarations of the abstarct base class, commnication
 * and its derived classes, text, email, message board, and post mail
 * these classes implement the pure virtual functions of the abstract class.
 * the inbox class is a circularly linked list that takes data of the abstract base class type
 * with upcasting, the derived classes can be inserted into the inbox CLL.
 * node class contains and has wrappers for the abstract class fruther details are in the .cpp files
 * with their fucntion headers, and along the ay within the file */



#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_
#include "addressbook.h"
const int MESSG = 181;

/*********************************************************************/

// abstarct base class
class communication
{
    public:

        communication();
        virtual ~communication();
        virtual int send() = 0;
        virtual int display() = 0;
        virtual int retrieve(char * keyword, communication *& found) = 0;
        virtual void clear() = 0;
        virtual communication * copy()const = 0;
    protected:
};

/*********************************************************************/

// standard send/recieve messages
class textMsg: public communication
{
    public:
        textMsg();
        textMsg(const textMsg & copyFrom);
        ~textMsg();
        int send();
        int display();
        void formatName(char * aName);
        char *& getRecipient();
        int cmpLastName(char * compareTo);
        int cmpLastName(textMsg & compareTo);
        int retrieve(char * keyWord, communication *& found);
        communication * copy()const;
        int copy(const textMsg * copyFrom);
        int send(char * aRecipient, char * aMessage);
        void clear();
    protected:
        char * message;
        char * recipient;
};

/*********************************************************************/

// apply postage, rand()
class postMail: public communication
{
    public:
        postMail();
        postMail(const postMail & copyFrom);
        ~postMail();
        int send();
        int display();
        void formatName(char * aName);
        char *& getRecipient();
        int cmpLastName(char * compareTo);
        int cmpLastName(postMail & compareTo);
        int retrieve(char * keyWord, communication *& found);
        communication * copy()const;
        int copy(const postMail * copyFrom);
        int send(int aPostID, char * aRecipient, char * aAddress, char * aMessage);
        void clear();
    protected:
        int postage;
        char * recipient;
        char * address;
        char * message;
};

/*********************************************************************/

// will just post stuff and check for new posts.
// timestamp?
class msgBoard: public communication
{
    public:
        msgBoard();
        msgBoard(const msgBoard & copyFrom);
        ~msgBoard();
        int send();
        int display();
        void formatName(char * aName);
        char *& getRecipient();
        int cmpLastName(char * compareTo);
        int cmpLastName(msgBoard & compareTo);
        int retrieve(char * keyWord, communication *& found);
        communication * copy()const;
        int copy(const msgBoard * copyFrom);
        int send(int aPostID, char * aUserName, char * aMessage);
        void clear();
    protected:
        int postID;
        char * userName;
        char * message;
};

/*********************************************************************/


class email: public communication
{
    public:
        email();
        email(const email & copyFrom);
        ~email();
        int send();
        int display();
        void formatName(char * aName);
        char *& getRecipient();
        int cmpLastName(char * compareTo);
        int cmpLastName(email & compareTo);
        int retrieve(char * keyWord, communication *& found);
        int copy(const communication * copyFrom);
        int copy(const email * copyFrom);
        int send(char * aRecipient, char * aSubject, char * aMessage);
        void clear();
        communication * copy()const;
    protected:
        char * recipient;
        char * subject;
        char * message;
};


/*********************************************************************/

class cNode
{
    public:
        cNode();
        cNode(const cNode & copyFrom);
        cNode(const communication * copyFrom);
        ~cNode();
        cNode *& goNext();
        void setNext(cNode * setTo);
        communication *& getMethod();
        void setMethod(communication * setTo);
        int display();
        void copy(const communication * copyFrom);
    protected:
        communication * method;
        cNode * next;
};

/*********************************************************************/

class inbox
{
    public:
        inbox();
        inbox(const inbox & copyFrom);
        ~inbox();
        int enqueue(const communication * toAdd);
        int dequeue();
        int removeAll();
        int copyAll(const inbox & copyFrom);
        int displayAll();
    protected:
        cNode * rear;
        int inboxCount;
        int removeAll(cNode *& rear, cNode *& temp);
        int copyAll(cNode *& dest, cNode * source);
        int copyAll(cNode *& dest, cNode * source, cNode *& dTemp, cNode * sTemp);
        int displayAll(cNode *& rear);
};

/*********************************************************************/
int mainMenu();
bool again();
bool backToMenu();
bool confirm();
#endif // _COMMUNICATION_H_

