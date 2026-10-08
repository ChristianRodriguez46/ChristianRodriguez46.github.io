//Christian Rodriguez
#include <iostream>

using namespace std;

struct DataNode
{
    string value;
    DataNode * next;
    DataNode * prev;
};

class Deque 
{
    protected:
        DataNode *head;
        DataNode *tail;

        DataNode * create()
        {
            DataNode * newnode;
            try
            {
                newnode = new DataNode;
                newnode->prev = NULL;
                newnode->next = NULL;
            }
            catch (bad_alloc)
            {
                newnode = NULL;
            }
            return newnode;
        }

        // USAGE: To create a new node, use as follows
        // DataNode * newnode = create();

        void deallocate ()
        {
            while(head != NULL)
            {
                DataNode * temp = head;
                head = head->next;
                delete temp;
            }
        }

        void addTohead (string value)
        {
            DataNode *newnode = create();
            newnode->value = value;

            if(head == NULL)
            {
                newnode->next = NULL;
                newnode->prev = NULL;
                head = newnode;
                tail = newnode;
             
            }
            else
            {
                newnode->prev = NULL;
                newnode->next = head;
                head = newnode;
                newnode->next->prev = head;

                // newnode->next = head;
                // head->prev = newnode;
                // head = newnode;
                
            }
        }

        string removeFromtail()
        {
            if (tail == NULL)
                return "";

            string value;

            if (tail == head)
            {
                value = tail->value;
                delete tail;
                head = NULL;
                tail = NULL;
            }
            else
            {
                DataNode *temp = tail->prev;
                value = tail->value;
                delete tail;
                temp->next = NULL;
                tail = temp;
            }
            return value;
        }

        void addTotail (string value)
        {
            DataNode *newnode = create();
            newnode->value = value;

            if(tail == NULL)
            {
                newnode->next = NULL;
                newnode->prev = NULL;
                head = newnode;
                tail = newnode;
            }
            else
            {
                newnode->next = NULL;
                newnode->prev = tail;
                tail = newnode;
                newnode->prev->next = tail;
            }
        }

        string removeFromhead()
        {
            if (head == NULL)
                return "";

            string value;

            if(head == tail)
            {   
                value = head->value;
                delete head;
                head = NULL;
                tail = NULL;
            }
            else
            {
                DataNode *temp = head->next;
                value = head->value;
                delete head;
                temp->prev = NULL;
                head = temp;
            }
            return value;
        }

    public:
        Deque() : head(NULL), tail(NULL) {}

        ~Deque() {
            deallocate();
            head = NULL;
            tail = NULL;
        }

        friend void show(Deque &Q);
};

class Queue : public Deque
{
    public:

        Queue &enqueue (string value)
        {
            addTohead(value);
            return *this;
        }

        Queue &dequeue()
        {
            removeFromtail();
            return *this;
        }
};

class Stack : public Deque
{
    public:
       
        Stack &push(string value)
        {
            addTohead(value);
            return *this;
        }

        Stack &pop() 
        {
            removeFromhead();
            return *this;
        }
};

void show(Deque &Q)
{
    // cout << "Deque contents:" << endl;
    DataNode * current = Q.head; 
    while (current != NULL)
    {
        cout << current->value << " ";
        current = current->next;
    }    
    cout << endl;
}

int main(){

   // Instantiate a Queue object
    Queue q;

    // Test enqueue function
    q.enqueue("Heaven").enqueue("Hell").enqueue("Limbo");
    cout << "Queue contents after enqueue:" << endl;
    show(q);

    cout << endl;

  
    // Test dequeue function
    q.dequeue();
    // Heaven should be dequeued
    cout << "Dequeue: " ;
    cout << "Queue contents after dequeue:" << endl;
    show(q);

    cout << endl;

    // Test enqueue function again
    q.enqueue("Purgatory").enqueue("Void");     //purgatory and void added to queue
    cout << "Queue contents after enqueue:" << endl;
    show(q);

    cout << endl;
    
    // Instantiate a Stack object
    Stack s;

    // Test push function
    s.push("Humpty").push("Dumpty");
    cout << "Stack contents after push:" << endl;
    show(s);

    cout << endl;

    // Test pop function
    s.pop();
    cout << "Stack contents after pop:" << endl;
    show(s);

    cout << endl;

    // Test push function again
    s.push("BO2").push("R6");
    cout << "Stack contents after push:" << endl;
    show(s);
    cout << endl;

    // Test pop function
    s.pop();
    cout << "Stack contents after pop:" << endl;
    show(s);

    cout << endl;

    return 0;
}
