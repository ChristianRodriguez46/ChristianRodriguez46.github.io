#include <string>
#include "Shapes.h"

const double PI = 3.14159;

// RECTANGLE FUNCTION DEFINITIONS
double Rectangle::getPerimeter() const {
    return (height + width) * 2;
}

double Rectangle::getArea() const {
    return width * height;
}

std::string Rectangle::toString() {
    std::string output = "";

    output += "SHAPE: " + label + "\n";
    output += "WIDTH: " + std::to_string(width) + "\n";
    output += "HEIGHT: " + std::to_string(height) + "\n";
    output += "AREA: " + std::to_string(getArea()) + " (square units)\n";
    output += "CIRC: "   + std::to_string(getPerimeter()) + "\n";

    return output;
}

bool Rectangle::operator== (const Rectangle &r){
   if(this->height == r.height && this->width == r.width) {
    return true;
   }else{
    return false;
   }
}

// TRIANGLE FUNCTION DEFINITIONS
double Triangle::getArea() const {
    return base * height * 0.5;
}

std::string Triangle::toString() {
    std::string output = " ";

    output += "SHAPE: " + label + "\n";
    output += "BASE: " + std::to_string(base)  + "\n";
    output += "HEIGHT: " + std::to_string(height) + "\n";
    output += "AREA: " + std::to_string(getArea()) + "\n";

    return output;
}
// CIRCLE FUNCTION DEFINITIONS
double Circle::getDiameter() const {
    return 2 * radius;
}
double Circle::getCircum() const {
    return PI * getDiameter() ;
}
double Circle::getArea() const {
    return PI * radius * radius;
}

std::string Circle::toString() {
    std::string output = "";

    output += "SHAPE: " + label  + "\n";
    output += "RADIUS: " + std::to_string(radius) + "\n";
    output += "DIAMETER: " + std::to_string(getDiameter())  + "\n";
    output += "CIRCUMFERENCE: " + std::to_string(getCircum())  + "\n";
    output += "AREA: " + std::to_string(getArea())  + "\n";

    return output;
}


