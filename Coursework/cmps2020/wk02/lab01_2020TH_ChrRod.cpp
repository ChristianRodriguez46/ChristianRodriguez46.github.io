#include <iostream>

using namespace std;
class point
{
    private:
        double x,y;
    public:
        point(double _x, double _y)
        {
            x = _x;
            y = _y;
        }

        point operator<(int rhs) //object is from the point class
        {
            double _x = x;

            _x -= rhs;
            point result(_x,y);
            return result;
        }
        point operator>(int rhs) //object is from the point class
        {
            double _x = x;

            _x += rhs;
            point result(_x,y);
            return result;
        }

       friend ostream & operator<<(ostream & lhs, point rhs)
        {
            lhs << "(" << rhs.x << "," << rhs.y << ")";
            return lhs;
        }

        friend double operator*(point lhs, point rhs);
};

double operator* (point lhs, point rhs)
{
    return abs(lhs.x - rhs.x) * abs(lhs.y - rhs.y);
}

int main()
{
    point p1(5,5), p2(10,10);

    p1 = p1 < 1;    //p1 is now (4,5)
    p2 = p2 > 3;    //p2 is now (13,10)

    cout << p1 << endl;     //shows (4,5)
    cout << p2 << endl;     //shows(13,10)

    double area = p1 * p2;

    cout << "Area bounded by p1 and p2 is " << area << endl; //45

    return 0;
}
