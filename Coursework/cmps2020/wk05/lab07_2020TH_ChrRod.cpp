//Christian Rodriguez
#include <iostream>

using namespace std;

template <typename T>
double average(T array[], int size)
{
    T total = 0;
    // calculate and return the average
    for (int i = 0; i < size; i++)
    {
        total += array[i];
    }
    return (total / size);  
}

template <typename T>
void showArray(T arr[], int size)
{
    for(int i =0; i < size; i++)
    {
        if(i == (size - 1))
        {
            cout << arr[i];
        }else{
            cout << arr[i] << ", ";
        }
    }
}

template <>
void showArray(string array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }
}


template <typename T>               //function to call for Input values into array
void Input (T arr[], int size)
{
    for (int i = 0; i < 10; i++)
    {
        cout << i+1 << ". ";
        cin >> arr[i];
    }

}

int main()
{
    int idata[10];
    double ddata[10];
    string sdata[10];

    //input section
    cout << "Enter 10 integers: \n";
    Input<int>(idata, 10);
    cout << endl;

    cout << "Enter 10 doubles: \n";
    Input<double>(ddata, 10);
    cout << endl;

    cout << "Enter 10 strings: \n";
    Input<string>(sdata, 10);
    cout << endl;
    
    //show arrays

    //int array 
    showArray<int>(idata, 10);
    cout << endl;

    cout << "Your average of the int array is: " << average<int>(idata, 10) << endl;
    cout << endl;

    //doubles array
    showArray<double>(ddata, 10);
    cout << endl;

    cout << "Your average of the double array is: " << average<double>(ddata, 10) << endl;
    cout << endl;


    //string array
    showArray<string>(sdata, 10);
    cout << endl;

    return 0;
}
