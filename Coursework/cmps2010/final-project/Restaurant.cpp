#include <string>
#include "Restaurant.h"

// default constructor
Restaurant::Restaurant(){
    name = "";
    type = "";
    style = "";
    numLocations = 0;
    score = 0.0;
};

std::string Restaurant::toCSV(){ 
    /*std::string output = name + "," + type + "," + style + "," + std::to_string(numLocations) + "," + std::to_string(score); 
    return output;*/
    return name + "," + type + "," + style + "," + std::to_string(numLocations) + "," + std::to_string(score); 
};


//this-> is referring to the class member
//SETTERS
void Restaurant::setName(std::string name){ this->name = name;}
void Restaurant::setType(std::string type){ this->type = type;}
void Restaurant::setStyle(std::string style){ this->style = style;}
void Restaurant::setNumLocations(unsigned short numLocations){ this->numLocations = numLocations;}
void Restaurant::setScore(float score){ this->score = score;}

