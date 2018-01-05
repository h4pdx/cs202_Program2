# cs202_Program2

Program #2
CS 202 Programming Systems

In our first programming assignment, we experimented with the notion of OOP and breaking the problem down into multiple classes building a relatively large system for a maze-game. The purpose of that assignment was to get to know how we can create classes that have different relationships. In program #2 our focus shifts to getting experience developing a hierarchy that can be used with dynamic binding – so that the application program can use one line of code to call one of many functions. To get the full benefit of dynamic binding, we will look at a smaller problem with a predefined design.

Program #2 – General Information

How do people communicate with you? Is it by email, text, snapchat, facebook messenger, USmail (?!) or phone calls? Or others? I communicate almost exclusively with text and email. But, my daughter gives regular updates using snapchat and almost never uses email. That may be fine, but do you ever find that you miss something because you didn’t check your messages, or didn’t notice that there was an facebook messenger has alerted you that there was a message? As the ways in which we get information expands, the possibility of loosing some messages along the way increases.

Program #2 – Building a Hierarchy using Dynamic Binding

For your second program, you will be creating a C++ OOP solution to support at least four different ways that the user can receive communication (e.g., email, text, and two others of your choice).

The purpose of this assignment is to use and experience dynamic binding. The requirement for this application is to have at least four DIFFERENT forms of communication supported, derived from a common abstract base class! To use dynamic binding, there needs to be a self-similar interface among the derived class methods. In this case, for all types of communication that you support, the user would like to read a message, send a message, delete a message, and so on. In the real world, there will be some differences as well, although there shouldn’t be too many. For example, if you elect to support USMail, then there needs to be postage applied that makes no sense for the other forms of communication. Make sure to find at least one method that is different so that you can experience how to resolve such differences.

Program #2 – Data Structure Requirements

With program #2, our data structure should be of POINTERS to the ABSTRACT base class and then with upcasting cause each node to point to the appropriate type of communication. Implementation of the required data structure(s) requires full support of insert, removal, display, retrieval, and remove-all. Efficiency must be part of your data structure design.

You will need to implement data structures for:

1. Address Book – A binary search tree (BST) of contact information needed by the different forms of communication, organized by last name. For all data that matches (so everyone with the same last name), create a dynamically allocated array in the node for each. This means that each node will have unique data (e.g., “Smith” will not appear more than once in the BST).

2. Types of Communication – A circular linked list of abstract base class pointers pointing to the different objects that represent the user’s forms of communication. For example, the user may have 5 email addresses, 1 facebook account, and 2 phones (one that can accept text messages).

Program #2 – Important C++ Syntax

Remember to support the following constructs as necessary:
1. Every class should have a default constructor
2. Every class that manages dynamic memory must have a destructor
3. Every class that manages dynamic memory must have a copy constructor
4. If a derived class has a copy constructor, then it MUST have an initialization list to cause the base class copy constructor to be invoked
5. Make sure to specify the abstract base class’ destructor as virtual
IMPORTANT: OOP and dynamic binding are THE PRIMARY GOALS of this assignment!
