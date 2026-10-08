//Christian Rodriguez
#include <iostream>

using namespace std;
struct Window
{
    string appname;
    Window *next;
    Window *prev;
};

class WindowManager
{
    private: 
        Window * current;
        Window * dummy;

        Window * create()
        {
            Window * newnode;
            try
            {
                newnode = new Window;
            }
            catch (bad_alloc)
            {
                newnode = NULL;
            }
            return newnode;
        }

        void deallocate()
        {
            Window *temp = dummy->next;

            while (temp != dummy)
            {
                Window * nextN = temp->next;
                delete temp;
                temp = nextN;
            }
            delete dummy;

        }

    public: 
        WindowManager() 
        {
            dummy = create();
            dummy->appname = "";
            dummy->next = dummy;
            dummy->prev = dummy;

            // current = dummy; //make current point to a valid node
        }
        ~WindowManager()
        {
            deallocate();
            dummy = NULL;
        }
 
        bool startApp (string name)
        {
            Window * newnode = create();

            if (newnode == NULL)
                return false;

            newnode->appname = name;
            newnode->next = dummy;
            newnode->prev = dummy->prev;
            dummy->prev->next = newnode;
            dummy->prev = newnode;
            current = newnode;

            return true;
        }

        Window * findApp (string name)
        {

            Window *temp = dummy->next;

            while (temp != dummy)
            {
                if (name == temp->appname)
                    return temp;

                temp = temp->next;
            }

            return NULL;
        }

        string getCurrent()
        {
            return current == NULL ? "" : current->appname;
        }

        bool closeApp (string name)
        {

            Window *closeApp = findApp(name);   //find app to close

            if (closeApp == NULL)
                return false;

            //if current is being closed, set current to next app
            // if (current == closeApp)
            // {
                current = closeApp->next;

                if(current == dummy)    //skip dummy
                    current = current->next;
            // }

            // Remove the app from the circular linked list
            closeApp->prev->next = closeApp->next;
            closeApp->next->prev = closeApp->prev;

            // Delete the node
            delete closeApp;

            //If the queue is empty, set current to NULL
            if (dummy->next == dummy)
                current = NULL;
            return true;
        }

        string next()
        {
            if (current == NULL)
                return "";

            //make current to next app & skips dummy node
            current = current->next == dummy ? dummy->next : current->next;
            return current->appname;
        }

        string previous()
        {
            if (current == NULL)
                return "";

            //make current to next app & skips dummy node
            current = current->prev == dummy ? dummy->prev : current->prev;
            return current->appname;
        }
};


int main(){

    WindowManager winman;

    // simulate some apps running
    winman.startApp("Microsoft Word");
    winman.startApp("Firefox");
    winman.startApp("Halo");
    winman.startApp("Calculator");

    // at this point, Calculator is the last app launched
    // and should be the value of current in winman
    int action;
    do
    {
        cout << "1 - Launch new app" << endl;
        cout << "2 - Close current app" << endl;
        cout << "3 - Find app, then close it" << endl;
        cout << "4 - Go to next app" << endl;
        cout << "5 - Go to previous app" << endl;
        cout << "0 - Shutdown" << endl;
        cin >> action;

        // fill in the rest of the necessary code to perform 
        // menu actions
        switch (action)
        {
            case 1:
                {
                    string appName;
                    cout << "Enter app name: ";
                    cin >> appName;
                    if (winman.startApp(appName))
                        cout << "App started: " << appName << endl;
                    else
                        cerr << "Failed to start app." << endl;
                    break;
                } 
            case 2:
                {
                    string currentApp = winman.getCurrent();

                    if( currentApp != "")
                    {
                        cout << "Closing app: " << currentApp << endl;
                        winman.closeApp(currentApp);
                        cout << "New current app: " << winman.getCurrent() << endl;
                    }
                    else
                    {
                        cout << "No apps running.\n";
                    }
                    break;
                }
            case 3:
                {
                    string appName;
                    cout << "Enter app name to close: ";
                    cin >> appName;

                    Window * app = winman.findApp(appName);

                    if ( app != NULL)  
                    {

                        if(winman.closeApp(appName))
                            cout << "App closed: " << appName << endl;
                        cout << "New current app: " << winman.getCurrent() << endl;
                    }
                    else
                    {
                        cout << "App not found.\n";
                    }
                    break;
                }
            case 4:
                {
                    cout << "Current app: " << winman.next() << endl;
                    break;
                }
            case 5:
                {
                    cout << "Current app: " << winman.previous() << endl;
                    break;
                }
            default:
                // cout << "Invalid option. Try again.\n";
                break;

        }
    }
    while (action != 0);

    cout << "Shutting down..." << endl;
    return 0;
}
