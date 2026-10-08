//Christian Rodriguez
//Lab 11
//CMPS 2010
//4-18-23

#include <string>
#include "GLOBALS.h"
#include "Monster.h"

// CONSTRUCTORS
Monster::Monster(){
    //TODO 1:
    //  Assign attributes using private gen methods
    this->name = genName();
    this->type = genType();
    this->color = genColor();
    this->eyes = genRandom(1,15);
    this->arms = genRandom(1,15);
    this->type = genRandom(1,15);

}

Monster::Monster(std::string mName, std::string mType, std::string mColor,
                 int mEyes, int mArms, int mLegs){
    //TODO 2:
    //  Assign attributes using parameters
    this->name = mName;
    this->type = mType;
    this->color = mColor;
    this->eyes = mEyes;
    this->arms = mArms;
    this->legs = mLegs;
};

//PRIVATE HELPER FUNCTIONS
int Monster::genRandom(int start, int end){
    int range = end - start + 1;
    return (rand() % range) + start;
}

std::string Monster::genName(){
    int size = sizeof(MONSTER_NAMES)/sizeof(MONSTER_NAMES[0]);
    return MONSTER_NAMES[genRandom(0,size-1)];
}

std::string Monster::genType(){
    int size = sizeof(MONSTER_TYPES)/sizeof(MONSTER_TYPES[0]);
    return MONSTER_TYPES[genRandom(0,size-1)];
}

std::string Monster::genColor(){
    int size = sizeof(MONSTER_COLORS)/sizeof(MONSTER_COLORS[0]);
    return MONSTER_COLORS[genRandom(0,size-1)];
}

std::string Monster::toString(){
    std::string output = "";
    
    output += "---------------------------\n";
    output += name + " the Monster\n";
    output += "---------------------------\n";
    output += "Name: " + name + "\n";
    output += "Type: " + type + "\n";
    output += "Color: " + color + "\n";
    output += "Eyes: " + std::to_string(eyes) + "\n";
    output += "Arms: " + std::to_string(arms) + "\n";
    output += "Legs: " + std::to_string(legs) + "\n";
   
    //TODO 3:
    //  Finish updating output string with all of the monster info
    //  (hint: you will need to use std::to_string() for the integers)
    return output;
}

// SETTERS
void Monster::setName(std::string n){ name = n; }
void Monster::setType(std::string t){ type = t; }
void Monster::setColor(std::string c){ color = c; }
void Monster::setEyes(int e){ eyes = e; }
void Monster::setArms(int a){ arms = a; }
void Monster::setLegs(int l){ legs = l; }

// GETTERS
std::string Monster::getName(){ return name; }
std::string Monster::getType(){ return type; }
std::string Monster::getColor(){ return color; }
int Monster::getEyes(){ return eyes; }
int Monster::getArms(){ return arms; }
int Monster::getLegs(){ return legs; }
