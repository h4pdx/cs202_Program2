
/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2 
 * inbox.cpp */

#include "communication.h"

/*********************************************************************/

cNode::cNode():
    method(NULL), next(NULL) {}

//----------------------------------------------------------

cNode::cNode(const cNode & copyFrom)
{
    //method->copy(*(copyFrom.method));
    //method = copyFrom->copy();
}

//----------------------------------------------------------
// node copy constructor with ABC argument, dynamic casting
cNode::cNode(const communication * copyFrom)
{
    method = copyFrom->copy();
}

//----------------------------------------------------------

// node destructor
cNode::~cNode()
{
    if (method)
    {
        delete method;
        method = NULL;
    }
}

//----------------------------------------------------------

// getter for next ptr
cNode *& cNode::goNext()
{
    return next;
}

//----------------------------------------------------------

// setter for next ptr
void cNode::setNext(cNode * setTo)
{
    next = setTo;
}

//----------------------------------------------------------

// getter for the ABC ptr
communication *& cNode::getMethod()
{
    return method;
}

//----------------------------------------------------------

// wrapper to set soemthing to the ABC ptr
void cNode::setMethod(communication * setTo)
{
    method  = setTo;
}

//----------------------------------------------------------

// wrapper for display
int cNode::display()
{
    return method->display();
}

//----------------------------------------------------------
// assigns the returned pointer to methods data, dynamically cast from main
void cNode::copy(const communication * copyFrom)
{
    //return method->copy(copyFrom);
    method = copyFrom->copy();
}

/*********************************************************************/

inbox::inbox():
    rear(NULL), inboxCount(0) {}

//----------------------------------------------------------

inbox::inbox(const inbox & copyFrom)
{
    copyAll(copyFrom);
}

//----------------------------------------------------------

inbox::~inbox()
{
    if (!removeAll())
        cout << "\nMemory not deallocated.\n";
}

//----------------------------------------------------------

// add at the end of the list
int inbox::enqueue(const communication * toAdd)
{
    // if no list yet
    int success = 0;
    if (!rear)
    {
        rear = new cNode(toAdd);
        if (rear)
            ++success;
        rear->setNext(rear);
    }
    // else add at the end and reconnect circularity
    else
    {
        cNode * temp = rear->goNext();
        rear->goNext() = new cNode(toAdd);
        rear = rear->goNext();
        rear->setNext(temp);
        ++success;
    }
    return success;
}

//----------------------------------------------------------

// remove from the front of the list, FIFO
int inbox::dequeue()
{
    if (!rear)
        return 0;
    return 0;
}

//----------------------------------------------------------

// recurisve delete all - wrapper
int inbox::removeAll()
{
    if (!rear)
        return 0;
    int counter = 0;
    // if only one node in list
    if (rear->goNext() == rear)
    {
        delete rear;
        rear = NULL;
        return 1;
    }
    // else, break circulatiry, and call recursive delete
    else
    {
        cNode * temp = rear;
        rear = rear->goNext();
        temp->setNext(NULL);
        counter = removeAll(rear, temp); // rear is now the head of the list
        return counter;
    }
}

//----------------------------------------------------------

// recursive delete all, deletes first cNode and recurses onto next
int inbox::removeAll(cNode *& rear, cNode *& temp)
{
    if (!rear)
        return 0;
    int counter = 0;
    // recurse to the end of the list (temp) and delete all on the way back
    counter += removeAll(rear->goNext(), temp);
    delete rear;
    rear = NULL;
    ++counter;
    // counts how many nodes removed, returns 0 if nothing is deleted
    return counter;
}

//----------------------------------------------------------

// public wrapper
int inbox::copyAll(const inbox & copyFrom)
{
    return copyAll(rear, copyFrom.rear);
}

//----------------------------------------------------------

// private wrapper, copies single node if list is one long,
// otherwise, break circularity, call copy, reconnect circulaity for new + old lists
int inbox::copyAll(cNode *& dest, cNode * source)
{
    if (!source) return 0;
    int counter = 0;
    if (source->goNext() == source)
    {
        dest = new cNode(*(source));
        dest->setNext(dest);
        return ++counter; // return 1
    }
    else
    {
        cNode * sTemp = source; // hold onto end of source list
        cNode * dTemp = NULL;   // will be set as last node in recursive call, reconnect after
        source = source->goNext();
        sTemp->setNext(NULL);
        counter = copyAll(dest, source, dTemp, sTemp); // actual recursive call
        sTemp->setNext(source); // reconnect soure list
        source = sTemp;
        if (dest)
        {
            dTemp->setNext(dest); // connect destination list
            dest = dTemp;
        }
    }
    return counter;
}

//----------------------------------------------------------

// actual recursive copy function
int inbox::copyAll(cNode *& dest, cNode * source, cNode *& dTemp, cNode * sTemp)
{
    if (!source) return 0;
    int counter = 0; // keep count of the copies, or return false(0)
    if (!dest)
    {
        dest = new cNode(*(source)); // jank that source node ptr into the copy constructor
        dest->setNext(NULL);
        ++counter;
    }
    counter += copyAll(dest->goNext(), source->goNext(), dTemp, sTemp);
    if (dest && !dest->goNext()) // after recursion and list is copied
    {
        dTemp = dest; // sets dTemp to the last node, so we can connect back in the wrapper
    }
    return counter;
}

//----------------------------------------------------------

// wrapper for recursive display
int inbox::displayAll()
{
    if (!rear) return 0;
    int counter = 0;
    if (rear->goNext() == rear)
        counter = rear->display();
    else
    {
        cNode * temp = rear;
        rear = rear->goNext();
        temp->setNext(NULL); // break circularity
        counter = displayAll(rear); // recursive call
        temp->setNext(rear); //reconnect
        rear = temp;
    }
    return counter;
}

//----------------------------------------------------------

// recursive display for list
int inbox::displayAll(cNode *& rear)
{
    if (!rear) return 0;
    int counter = 0;
    counter = rear->display();
    counter += displayAll(rear->goNext());
    return counter;
}


