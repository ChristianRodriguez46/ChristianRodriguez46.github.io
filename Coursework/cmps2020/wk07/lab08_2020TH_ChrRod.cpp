//Christian Rodriguez
#include <iostream>

using namespace std;

struct Location
{
  string name;
  string url;
};

struct VisitNode
{
  Location loc;
  VisitNode * next;
};

class Stack{
    private:
        VisitNode * head;

        VisitNode * create()
        {
            VisitNode * newnode;
            try
            {
                newnode = new VisitNode;
            }
            catch (bad_alloc)
            {
                newnode = NULL;
            }
            return newnode;
        }

        void deallocate() 
        {
            VisitNode * temp;

            while( head->next != NULL )
            {
                temp = head;
                head = temp->next;
                delete temp;
            }
            
        }

    public: 
        Stack()
        {
            head = NULL;
        };

        ~Stack()
        {
            deallocate();
            head = NULL;
        }

        bool push (string name, string url)
        {
            VisitNode * newNode = create();

            newNode->loc.name = name;
            newNode->loc.url = url;

            if (head == NULL)//empty
            { 
                head = newNode;
                newNode->next = NULL; 
            }
            else 
            {
                VisitNode * temp = head;
                head = newNode;
                newNode->next = temp;

            }

            return newNode == NULL ? true : false;
        }

        string pop()
        {
            if (head != NULL)
            {
                VisitNode * temp = head;
                head = temp->next;
               
                string name = temp->loc.name ;
               
                delete temp; 
            
                return  name;
            }else{
                return "";
            }
        }

        friend void show(Stack &S);

};

void show(Stack &S)
{
    VisitNode * temp = S.head; 
    while( temp != NULL )
    {
        cout << temp->loc.name << " ";
        temp = temp->next;
    }

}
int main(){

    Stack browser;

    // simulate a browser history
    browser.push("Google", "//google.com");
    browser.push("Amazon", "//amazon.com");
    browser.push("LinkedIn", "//LinkedIn.com");
    browser.push("Reddit", "//reddit.com");

    show(browser);   // this should show the entire history

    // simulate clicking Back button
    string top = browser.pop();
    if (top != "")
        cout << endl << "Clicked back from " << top << endl;
    show(browser);

    // simulate clicking Back button
    top = browser.pop();
    if (top != "")
        cout << endl << "Clicked back from " << top << endl;
    show(browser);

    // simulate clicking Back button
    top = browser.pop();
    if (top != "")
        cout << endl << "Clicked back from " << top << endl;
    show(browser);

    cout << endl;

    return 0;
}
