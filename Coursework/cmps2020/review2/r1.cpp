//Christian Rodriguez
#include <iostream>

using namespace std;

class SmartArray
{
    private: 
        string * array;
        int size;
        int pos;

        void resize()
        {
            int oldsize = size;
            size = size *2;
            string * newarray = new string[size * 2];

            for (int i = 0; i < oldsize; i++)
            {
                newarray[i] = array[i];
            }

            delete [] array;
            array = newarray;
        }
    public: 
        SmartArray(int s)
        {
            size = s;
            pos = 0;
            array = new string[s];
        }
        ~SmartArray()
        {
            delete [] array;
        }
        
        void add(string value)
        {
            if (pos == size)
            {
                resize();
            }
            array[pos] = value;
            pos++;
        }

        void show()
        {
            for (int i =0; i < pos; i++ )
            {
                cout << array[i] << endl;
            }
            cout << "-----\n";
        }
};

int main(){

    SmartArray sa(3);
    
    sa.add("hi");
    sa.add("hi");
    sa.add("hi");
    sa.show();
    sa.add("hello");
    sa.add("hello");
    sa.add("hello");
    sa.add("hello");
    sa.show();


    for (int i = 0; i < 5; i++)
    {
        sa.add("hi");
    }

    return 0;
}
