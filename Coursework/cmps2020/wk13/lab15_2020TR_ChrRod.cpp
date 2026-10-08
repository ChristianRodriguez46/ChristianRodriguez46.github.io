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

        void deallocate(VisitNode * node)
        {
            // identify your base condition
            // NO LOOPS!
            if (node != NULL)
            {
                deallocate(node->next);
                delete node;
            }
         
        }

    public: 
        Stack()
        {
            head = NULL;
        };

        ~Stack()
        {
            deallocate(head);
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

        // string pop()
        // {
        //     if (head != NULL)
        //     {
        //         VisitNode * temp = head;
        //         head = temp->next;
               
        //         string name = temp->loc.name ;
               
        //         delete temp; 
            
        //         return  name;
        //     }else{
        //         return "";
        //     }
        // }

        friend void show(Stack &S);

        
};

//global function
void shownode(VisitNode *node)
{
    if (node != NULL)
    {
        cout << node->loc.name << " ";
        shownode(node->next);
    }
}

void show(Stack &S)
{
    shownode(S.head);
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
    // string top = browser.pop();
    // if (top!= "")
    //     cout << endl << "Clicked back from " << top << endl;
    // show(browser);

    // simulate clicking Back button
    // top = browser.pop();
    // if (top!= "")
    //     cout << endl << "Clicked back from " << top << endl;
    // show(browser);

    // simulate clicking Back button
    // top = browser.pop();
    // if (top!= "")
    //     cout << endl << "Clicked back from " << top << endl;
    // show(browser);

    cout << endl;
    return 0;
}