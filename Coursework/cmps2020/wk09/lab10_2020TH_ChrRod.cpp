//Christian Rodriguez
#include <iostream>


using namespace std;
struct JobNode
{
    string name;
    JobNode * next;
};

class Queue 
{
    private:
        JobNode * head;

        JobNode * create()
        {
            JobNode * newnode;
            try
            {
                newnode = new JobNode;
            }
            catch (bad_alloc)
            {
                newnode = NULL;
            }
            return newnode;
        }

        void deallocate ()
        {
            // find a way to deallocate everything

            while(head != NULL)
            {
                JobNode * temp = head;
                head = head->next;
                delete temp;
            }
        }
    public:
        Queue()
        {
            head = NULL;
        }
        ~Queue()
        {
          // cout << "in deconstructor\n"; 
            deallocate();
            head = NULL;
        }

        bool enqueue (string name)
        {
            JobNode * newnode = create();

           // cout << "inside of enqueue\n";
            if (newnode == NULL)
            {
                cerr << "new node was not created\n";
                return false;
            }



            if (head == NULL)
            {

                newnode->name = name;
                newnode->next = NULL;
                head = newnode;
            }
            else
            {
                newnode->name = name;
                newnode->next = head;
                head = newnode;
            }

            return true;
        }

        string dequeue()
        {
           // cout << "in deque\n";
            string data;

            if (head == NULL)
            {
                return "";
            }


            if(head->next == NULL)
            {
                //ONE NODE SITUATION
               
               // cout << "in denqueue check 1\n";
                data = head->name;
                delete head;
                head = NULL;

            }
            else if (head->next->next == NULL)
            {
                //TWO NODE SITUATION
             //   cout << "in denqueue check 2\n";
                JobNode * temp = head->next;
                data = temp->name;
                delete temp;
                head->next = NULL;
            }
            else
            {
               // cout << "in denqueue check 3\n";
                JobNode * current = head;  
                JobNode * prev = NULL;  

                while (current->next != NULL)
                {
                    prev = current;
                    current = current->next;
                } 

                data = current->name;

                prev->next = NULL;

                delete current;
            }
        
            return data;
        }

       friend void show(Queue &Q);
};

void show(Queue & Q)
{
    JobNode * temp = Q.head;
    while (temp != NULL)
    {
        //cout << "in show check 1\n";
        cout << temp->name << endl;
        temp = temp->next;
    }
}



int main()
{
  Queue spooler;

  // simulate a printer spooler
  spooler.enqueue("Comm100 Paper.docx");
  spooler.enqueue("Fwd: Direct Deposit");
  spooler.enqueue("document(1).doc");
  spooler.enqueue("lab9.cpp");

  cout << "Pending jobs: " << endl;
  show(spooler);   // this shows all jobs

  // simulate the printer completing the jobs
  string oldest;
  do
  {
    oldest = spooler.dequeue();
    cout << endl;
    if (oldest != "")
    {
      cout << "Printing..." << endl;
      cout << oldest << " printed" << endl;

      cout << endl << "Pending jobs:" << endl; 
      show(spooler);     
    }
  } while (oldest != "");

  cout << "No jobs" << endl;

  return 0;
}
