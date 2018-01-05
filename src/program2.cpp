
/* Ryan Hoover - 3/10/17
 * CS163 - K. Fant
 * PROGRAM 4 
 * addressBook.cpp */

//#include "addressbook.h"
#include "communication.h"
int main()
{
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    srand(start_time.tv_usec);
    contact person;
    addressBook myContacts;
    communication * app;
    inbox myInbox;
    int menu = 0;
    char response;
    do
    {
        menu = mainMenu();
        switch(menu)
        {
            case 1:
                do // while (again())
                {
                    do // while (!confirm())
                    {
                        if (person.create())
                        {
                            cout << "\nEntry created.";
                            if (!person.display())
                            {
                                cout << "\nCould not display.";
                            }
                        }
                        else
                        {
                            cout << "\nEntry not created.";
                        }
                    }
                    while(!confirm());
                    if (myContacts.insert(person))
                    {
                        cout << "\nNew entry added to Address Book.";
                    }
                    else
                    {
                        cout << "\nEntry not added.";
                    }
                }
                while (again());
                //person.display();
                break;
            case 2:
                if (!myContacts.displayAll())
                    cout << "\nCould not display.";
                break;
            case 3:
                char toFind[NAME];
                cout << "\nSearch for a contact entry by Last name: ";
                cin.get(toFind,NAME,'\n'); cin.ignore(NAME,'\n');
                formatName(toFind);
                if (myContacts.retrieve(toFind, person))
                {
                    cout << "\nEntry found!: ";
                    if (!person.display())
                    {
                        cout << "\nCould not display.\n";
                    }
                }
                else
                {
                    cout << "\nEntry not found\n";
                }
                break;
            case 4:
                cout << "\nRemove all data.\n";
                if (confirm())
                {
                    if (myContacts.removeAll())
                    {
                        cout << "\nEverything deleted!\n";
                    }
                    else
                    {
                        cout << "\nNothing deleted. <error>\n";
                    }
                }
                else
                    break;
                break;
            case 5:
                char toRemove[NAME];
                do // while (again());
                {
                    cout << "\nRemove by matching keyword: ";
                    cin.get(toRemove, NAME, '\n'); cin.ignore(NAME,'\n');
                    formatName(toRemove);
                    if (myContacts.removeMatch(toRemove))
                    {
                        cout << "\nContact removed from Address Book.\n";
                    }
                    else
                    {
                        cout << "\nContact NOT removed.\n";
                    }
                }
                while (again());
                break;
            case 6:
                do {
                    cout << "\n >> What kind of app?"
                         << "\n'T' For text message."
                         << "\n'E' For an email message."
                         << "\n'M' For a message board post."
                         << "\n'P' For a post mail letter."
                         << "\nEnter a letter: ";
                    cin >> response; cin.ignore(100,'\n');
                    response = toupper(response);
                    switch (response)
                    {
                        case 'T':
                            app = new textMsg;
                            break;
                        case 'E':
                            app = new email;
                            break;
                        case 'M':
                            app = new msgBoard;
                            break;
                        case 'P':
                            app = new postMail;
                            break;
                        default:
                            app = new textMsg;
                            break;
                    }
                    if (app->send())
                        cout << "\nInput successful.\n";
                    else cout << "\nInput failed.\n";
                    app->display();
                    if (myInbox.enqueue(app))
                        cout << "\nSent to inbox!\n";
                    else cout << "\nNot sent to Inbox.\n";
                }while (again());
                break;
            case 7:
                if (myInbox.displayAll())
                    cout << "\nInbox is up to date.\n";
                else cout << "\nCould not display.\n";
                break;
        }
    } while(menu != 8 && backToMenu());

    return 0;
}
