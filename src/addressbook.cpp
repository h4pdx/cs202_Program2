
/* Ryan Hoover - 04/30/17
 * CS202 - K. Fant
 * PROGRAM 2 
 * addressbook.cpp *
 * addressbook.h function implementations */

#include "addressbook.h"

/*********************************************************************/

// node default
node::node()
{
    left = right = NULL;
}

//----------------------------------------------------------

// node copy constr
node::node(const contact & copyFrom)
{
    myContact.copy(copyFrom);
    left = right = NULL;
}
//----------------------------------------------------------

// node copy constr
node::node(const node & copyFrom)
{
    //contact(copyFrom);
    myContact.copy(copyFrom.myContact);
    //left = copyFrom.goLeft();
    //right = copyFrom.goRight();
    left = right = NULL;
}

//----------------------------------------------------------

// node destructor
node::~node()
{
    if (left)
    {
        //delete left;
        left = NULL;
    }
    if (right)
    {
        //delete right;
        right = NULL;
    }
}

//----------------------------------------------------------

// getter
node *& node::goLeft()
{
    return left;
}

//----------------------------------------------------------

// getter
node *& node::goRight()
{
    return right;
}

//----------------------------------------------------------

//setter
void node::connectLeft(node * setTo)
{
    left = setTo;
}

//----------------------------------------------------------
// setter
void node::connectRight(node * setTo)
{
    right = setTo;
}

//----------------------------------------------------------
//getter
char * node::getName()
{
    return myContact.getLastName();
}

//----------------------------------------------------------
// wrspper for contact display
int node::display()
{
    return myContact.display();
}

//----------------------------------------------------------
// comparison
int node::cmpName(char * compareTo)
{
    return myContact.cmpLastName(compareTo);
}

//----------------------------------------------------------
// wrapper
int node::copyContact(node *& copyFrom)
{
    return myContact.copy(copyFrom->myContact);
}

//----------------------------------------------------------
// wrapper
int node::retrieve(char * keyWord, contact & found)
{
    return myContact.retrieve(keyWord, found);
}
// wrapper
int node::create(char *aFirst, char*aLast, char*aPhone, char*aUser)
{
    return myContact.create(aFirst,aLast,aPhone,aUser);
}
// getter
contact & node::getContact()
{
    return myContact;
}
// wrapper
int node::write(ofstream & fout)
{
    return myContact.write(fout);
}

/*********************************************************************/
// default constructor, reads from file
addressBook::addressBook()
{
    root = NULL;
    contactCount = 0;
    if (readFile())
    {
        cout << "\nData loaded from file.\n";
    }
    else
    {
        cout << "\nData not loaded.\n";
    }
}

//----------------------------------------------------------

// desctructor, writes to file
addressBook::~addressBook()
{
    if (writeFile())
        cout << "\nData written to external file.\n";
    else cout << "\nData not written to file.\n";
    
    removeAll();
    if (root)
    {
        delete root;
        root = NULL;
    }
}

//----------------------------------------------------------

// Wrapper for recursive function below
int addressBook::insert(contact & toAdd)
{
    int success = insert(root,toAdd);
    return success;
}
//----------------------------------------------------------

// Inserts based on strcmp bewteen the current root title and the obj title to be inserted
int addressBook::insert(node * & root, contact & toAdd)
{
    int success = 0;
    // creates a new node when we traverse out of bounds from the correct subtree
    if (!root)
    {
        root = new node(toAdd);
        ++success;
        ++contactCount;
    }
    else
    {
        if (toAdd.cmpLastName(root->getName()) < 0)
        {
            success += insert(root->goLeft(),toAdd);
        }
        else if (toAdd.cmpLastName(root->getName()) > 0)
        {
            success += insert(root->goRight(),toAdd);
        }
        else
        {
            cout << "\nDuplicate data not yet supported!";
            return success;
        }
    }
    return success;
}

//----------------------------------------------------------

// Wrapper for recursive function below
int addressBook::displayAll()
{
    cout << "\nNumber of entries: " << contactCount << endl;
    return displayAll(root);
}

//----------------------------------------------------------

// Traverses left subtree, displays, traverses right subtree, Alphabetical order
int addressBook::displayAll(node * root)
{
    if (!root) return 0;
    int success = 0;
    if (root->goLeft())
    {
        success = displayAll(root->goLeft())+1;
    }
    success += root->display();
    if (root->goRight())
    {
        success = displayAll(root->goRight())+1;
    }
    return success;
}
//----------------------------------------------------------

// Wrapper for recursive function below
int addressBook::retrieve(char * keyWord, contact & found)
{
    return retrieve(root,keyWord,found);
}

// Pass in a poulated keyword contact from main, and and empty contact object to be filled by contact::retrieve
int addressBook::retrieve(node *& root, char * keyWord, contact & found)
{
    if (!root) return 0;
    int success = 0;
    success = root->retrieve(keyWord,found);
    success += retrieve(root->goLeft(),keyWord,found);
    success += retrieve(root->goRight(),keyWord,found);
    return success;
}
    
//----------------------------------------------------------

// Wrapper for recursive function below
int addressBook::removeAll()
{
    int success = 0;
    success = removeAll(root);
    return success;
}

//Explicit destructor, clears entire addressBook of all data, resets addressBook::contactCount to 0
int addressBook::removeAll(node * & root)
{
    if (!root)
    {
        return 0;
    }
    int success = 0;
    success += removeAll(root->goLeft());
    success += removeAll(root->goRight());
    delete root;
    root = NULL;
    if (!root)
    {
        ++success;
        --contactCount;
    }
    return success;
}

//----------------------------------------------------------

// Wrapper for recursive function below
int addressBook::removeMatch(char * keyWord)
{
    return removeMatch(root, keyWord);
}

// Finds a title based on a keyWord argument, passed in by client
int addressBook::removeMatch(node * & root, char * keyWord)
{
    if (!root)
    {
        return 0;
    }
    int counter = 0;
    //int success = 0;
    // Compare private data members
    if (!root->cmpName(keyWord))
    {
        // If match, look for one of 4(5) sub cases
        // Node is a leaf
        if (!root->goLeft() && !root->goRight())
        {
            cout << "\nRemoval, condition 1 met.\n";
            delete root;
            root = NULL;
            ++counter;
            --contactCount;
        }
        // Root has a left subtree ONLY
        else if (!root->goRight() && root->goLeft())
        {
            cout << "\nRemoval, condition 2 met.\n";
            node * temp = root->goLeft();
            delete root;
            root = temp;
            ++counter;
            --contactCount;
            return -1;
        }
        // Root has a right subtree ONLY
        else if (!root->goLeft() && root->goRight())
        {
            cout << "\nRemoval, condition 3 met.\n";
            node * temp = root->goRight();
            delete root;
            root = temp;
            ++counter;
            --contactCount;
            return -1;
        }
        // Root has two subtrees
        else if (root->goLeft() && root->goRight())
        {
            // Find the in-order-successor and reassign root->data
            node * temp = root->goRight();
            // If the right subtree of Root doesn't have a Left subtree
            if (!temp->goLeft())
            {
                cout << "\nRemoval, condition 4.1 met.\n";
                root->copyContact(temp);
                root->connectRight(temp->goRight());
                // cleared root, moved successor's data to root, now temp is a duplicate
                delete temp;
                temp = NULL;
                ++counter;
                --contactCount;
            }
            else
            {
                cout << "\nRemoval, condition 4.2 met.\n";
                // If right subtree has two subtrees, find the successor down the left subtree
                node * current = temp;
                node * previous = NULL;
                while (current->goLeft())
                {
                    previous = current;
                    current = current->goLeft();
                }
                previous->connectLeft(current->goRight());
                root->copyContact(current);
                delete current;
                current = NULL;
                ++counter;
                --contactCount;
            } 
        } 
    } // if (root->data.cmpChar(keyWord) == 0)
    else
    {
        if (root->cmpName(keyWord) > 0)
        {
            counter = removeMatch(root->goLeft(), keyWord);
        }
        else
        {
            counter = removeMatch(root->goRight(), keyWord);
        }
    }
    return counter;
}

//----------------------------------------------------------

// Creates and then deletes a temp node ptr to take in obj data from file
int addressBook::readFile(){
    int success = 0;
    char aFirstName[NAME], aLastName[NAME], aNum[NUM], aUser[NAME];
    ifstream fin;
    node * temp = new node;
    fin.open("contacts.txt");
    if (fin){
        ++success;
        fin.get(aFirstName, NAME, ':'); fin.ignore(NAME, ':');
        while (fin && !fin.eof())
        {
            fin.get(aLastName, NAME, ':'); fin.ignore(NAME, ':');
            fin.get(aNum, NUM, ':'); fin.ignore(NUM, ':');
            fin.get(aUser,NAME,'\n'); fin.ignore(NAME,'\n');
            // Uses addressBook fucntions for insertion
            if (temp->create(aFirstName,aLastName,aNum,aUser)){
                if (!insert(temp->getContact())){
                    cout << "\nData not properly read in from file.\n";
                }
            }
            fin.get(aFirstName, NAME, ':'); fin.ignore(NAME, ':');
        }
        fin.clear();
        fin.close();
        delete temp; temp = NULL;
    }
    return success;
}


//----------------------------------------------------------

// Wrapper for recursive function below, keeps the file open and passes fout by ref
int addressBook::writeFile()
{
    // fout passed by ref to recursive func & contact write func
    ofstream fout;
    fout.open("contacts.txt");
    int success = writeFile(root,fout);
    if (fout)
    {
        fout.clear();
        fout.close();
    }
    return success;
}

//----------------------------------------------------------

// Takes &fout obj and passes it to contact class write file for the private data members
int addressBook::writeFile(node * root, ofstream & fout){
    if (!root) return 0;
    int success = 0;
    if (fout && !fout.eof())
    {
        success = root->write(fout);
        // Recursive calls for pre-order writing
        success += writeFile(root->goLeft(),fout);
        success += writeFile(root->goRight(),fout);
    }
    return success;
}

//----------------------------------------------------------

