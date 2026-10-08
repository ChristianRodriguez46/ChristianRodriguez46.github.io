//Christian Rodriguez
#include <iostream>

using namespace std;

struct Item
{
    string name;    //data element
    int count;      //data element
    Item * next;    //pointer element   
        
};

int count(Item * head)
{
    int result = 0;
    Item * temp = head;     //copying head's value (an address)

    //traversal loop
    while(temp != NULL)
    {
        result++;
        temp = temp->next;      //traverse to next node
    }

    return result;
} 

void show(Item * head)
{
    Item * temp = head;     //copying head's value (an address)
   
    //traversal loop
    while(temp != NULL)
    {
        cout << temp->name << " (" << temp->count << ")" << endl;
        temp = temp->next;      //traverse to next node
    }

}

bool find(Item * head, string value)
{
    Item * temp = head;     //copying head's value (an address)
   
    //traversal loop
    while(temp != NULL)
    {
        if (temp->name == value)
        {
            return true;
        }
        temp = temp->next;      //traverse to next node
    }
    return false;
}

void setcounts(Item * head, int c)
{
    Item * temp = head;     //copying head's value (an address)
   
    //traversal loop
    while(temp != NULL)
    {
        temp->count = c;
        temp = temp->next;      //traverse to next node
    }
   
}

int main()
{
    //usally it is dynamicaly created but this is an example
    Item item1 { "bacon", NULL };
    Item item2 { "eggs", NULL };
    Item item3 { "chair", NULL };
    Item item4 { "soap", NULL };
    Item item5 { "airplane", NULL };

    Item * head;        //head points to nothing at this point
                        //not node but a ptr to the first node

    head = &item1;      //head now points to item1

    cout << head->name << endl;     //prints bacon
    cout << head->next << endl;     //prints 0

    //add item2 into the list
    item1.next = &item2;
    cout << count(head) << endl;
   
   
    //add item3 into the list
    item2.next = &item3;
    cout << count(head) << endl;
   
    //add item4 into the list
    item3.next = &item4;
   
    //add item5 into the list
    item4.next = &item5;
  
    //Challenge 3 - set all counts to 1
    //Chalenge 1 - show all the item names
    setcounts(head, 1);
    show(head);

    //Challenge 2 - ask user to enter string
    // see if string is in linked linst
    cout << "Search for: \n";
    string value;
    cin >> value;
 
   if( find(head, value))
       cout << "Found\n";
   else 
       cout << "Not found\n";


    
    return 0;
}
