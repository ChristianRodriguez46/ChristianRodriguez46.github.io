#include <iostream>
using namespace std;
int multiply(int x);

int main()
{
    int number;
#ifdef UNIT_TEST
    number = 5;
#else
    cout << "Enter a number: ";
    cin >> number;
#endif
    int result = multiply(number);
    cout << result << endl;
#ifdef UNIT_TEST
    if (result != 500)
        cout << "ERROR - in multiply function!\n";
    else
        cout << "multiply function - ok\n";
#endif

    return 0;
}

int multiply (int x)
{
    return x * 100;
}