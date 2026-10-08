#include <iostream>

using namespace std;
//struct properties are public by default, and class properties are private by default
class Height
{
    private:        //access-specifier 
        double feet, inches;        //data members, properties, attributes
    public:
        void setFeet(double f)      //setter / accessor
        {
            feet = f
        }
        void setInches(double i)      //setter / accessor
        {
            inches = i
        }
};

int main()
{
    Height h1;      //h1 is an instance of Height
                    //h1 is an object of type Height
                    //Height is a class, h1 is an object/instance
                    //Height instantiates h1

//    h1.feet = 6;
    h1.setFeet(6);
    // h1.inches = 2;
    h1.setInches(2);

    cout << h1.feet << " feet " << h1.inches << " in\n";

    return 0;
}
