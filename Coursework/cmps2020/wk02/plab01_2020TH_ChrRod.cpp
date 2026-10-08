#include <iostream>

using namespace std;

class Point
{
    private: 
        double x, y;
    public:
        void setCoords(double _x, double _y) 
        {
            x = _x;
            y = _y;
        }

        double get_X(){ return x;}
        double get_Y(){ return y;}
};

class Map
{
    private:
        Point tl, br;
    public:
        Map(Point _tl, Point _br)
        {
            tl = _tl;
            br = _br;
        }
        double calArea()
        {
           
            return abs( tl.get_X() - br.get_X() ) * abs( tl.get_Y() - br.get_Y() );
        }
};

int main(){

    Point p1, p2;

    p1.setCoords(3, 3);
    p2.setCoords(6, 7);

    //instantiate a map object
    Map m1(p1, p2);
    //display total area bounded by p1 and p2
    
    cout << m1.calArea() << endl;
    return 0;

}
