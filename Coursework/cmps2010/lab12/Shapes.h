#ifndef SHAPES_H
#define SHAPES_H
#include <string>

// SHAPE CLASS DECLARATION
class Shape{
    protected:
        std::string label;

    public:
        virtual double getArea() const = 0;
        virtual std::string toString() = 0;

        void setLabel(std::string label){
            this->label = label;
        }
};

// RECTANGLE CLASS DECLARATION
class Rectangle : public Shape{
    protected:
        double width;
        double height;

    public:
        Rectangle(double width, double height){
            this->width = width;
            this->height = height;
            setLabel("Rectangle");
        }

        double getPerimeter() const;
        double getArea() const;
        std::string toString();

        bool operator== (const Rectangle&);
};

// SQUARE CLASS DECLARATION
class Square : public Rectangle {
    public:
        Square(double side) : Rectangle(side, side) {
            setLabel("Square");
        }
};

// TRIANGLE CLASS DECLARATION
class Triangle : public Shape {
    private:
        double base;
        double height;

    public:
        Triangle(double base, double height) {
            this->base = base;
            this->height = height;
            setLabel("Triangle");
        }

        double getArea() const;
        std::string toString();
};

// CIRCLE CLASS DECLARATION
class Circle : public Shape {
    private :
        double radius;

    public:
        Circle(double radius) {
            this->radius = radius;
            setLabel("Circle");
        }

        double getDiameter() const;
        double getCircum() const;
        double getArea() const;
        std::string toString();

};

#endif
