#include <string>
#include "Monster.h"

void Monster::setName(std:: string n){ 
    name = n; 
}
std::string Monster::getName() const{ 
    return name; 
}


void Monster::setType(std:: string t){
    type = t;
}
std::string Monster::getType() const{
    return type;
}


void Monster::setColor(std:: string c){
    color = c;
}
std::string Monster::getColor() const{
    return color;
}


void Monster::setEyes(int e){
    eyes = e;
}
int Monster::getEyes() const{
    return eyes;
}


void Monster::setArms(int a){
    arms = a;
}
int Monster::getArms() const{
    return arms;
}


void Monster::setLegs(int l){
    legs = l;
}
int Monster::getLegs() const{
    return legs;
}

