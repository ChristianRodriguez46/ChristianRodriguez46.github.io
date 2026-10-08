//Christian Rodriguez
#include <iostream>

using namespace std;

class RingBuffer
{
    private:
        int size; 
        string * names;
        int front;
        int back;

        //Function to check if the queue is empty
        bool isEmpty()
        { 
            return front == back ? true : false; 
        }

        //Function to check if queue is empty
        bool isFull ()
        {
            return (back + 1) % size == front ? true : false;
        }

    public:
        RingBuffer (int size)
        {
            this->size = size;
            names = new string[size]; //dynamic string array for names
            front = 0; //make front to 0
            back  = 0; //make front to 0

            //make all elements in 'names' array empty strings
            for (int i = 0; i < size; i++)
            {
                names[i] = "";
            }
        }

        ~RingBuffer()
        {
            delete[] names;
        }

        //Enque a name into RingBuffer
        bool enqueue(string name)
        {
            //check if queue is not full
            if (!isFull())
            {
                names[back] = name; //adds the name given to back of queue
                back = (back + 1) % size; //update back index
                return true;
            }
            return false;
        }

        string dequeue()
        {
            if (isEmpty()) //check if queue is empty
            {
                return "";
            }

            string name = names[front]; //get name from front
            front = (front + 1) % size; //update front index
            return name; //return dequeued name
        }

        friend void show(RingBuffer & rb);
};

void show(RingBuffer & rb)
{
    int counter = rb.front; //make a counter with it starting at front

    while (counter != rb.back) //loop array front to back
    {
        cout << rb.names[counter] << " "; //display name at current index
        counter = (counter + 1) % rb.size; //update front index
    }

    cout << endl;

}

int main(){

    RingBuffer buffer(4);
    char action;
    string name = "";
    bool added;

    do
    {
        cout << "e - Enqueue" << endl;
        cout << "d - Dequeue" << endl;
        cout << "q - Quit" << endl;
        cout << "Action: ";
        cin >> action;

        if (action == 'e')
        {
            cout << "Name: ";
            cin >> name;
            if (buffer.enqueue(name))
            {
                cout << "Added " << name << endl;
            }
            else
            {
                cout << name << " was not added. Queue full" << endl;
            }
        } else if (action == 'd')
        {
            name = buffer.dequeue();
            if (name == "")
            {
                cout << "Queue is empty" << endl;
            }
            else
            {
                cout << "Dequeued " << name << endl;
            }
        }
        show(buffer);
        cout << "-------------" << endl;

    } while (action != 'q');

    return 0;
}
