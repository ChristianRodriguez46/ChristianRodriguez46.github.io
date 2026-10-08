#include <iostream>
#include "Shapes.h"
using namespace std;

int main(){
    Rectangle r1(10, 5);
    Rectangle r2(10, 5);
    cout << r1.toString() << endl;
    cout << r2.toString() << endl;

    if(r1 == r2){
        cout << "The rectangles are equal!\n";
    }else{
        cout << "The rectangles are not equal!\n";
    }

    cout << endl;

    // UNCOMMENT THE FOLLOWING LINES OF CODE
    // ONCE YOU ARE DONE DEFINING YOUR CLASSES

     Square s1(10);
     cout << s1.toString() << endl;

     Triangle t1(10, 5);
     cout << t1.toString() << endl;

     Circle c1(10);
     cout << c1.toString() << endl;

    return 0;
}
