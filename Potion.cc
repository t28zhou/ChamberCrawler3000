#include "Potion.h"

Potion::Potion(int x, int y, Floor * fl, int type, std::string pname, bool know):Part{x,y,fl},code{type},name{pname},used{know}{}

Potion::~Potion(){}

int Potion::getCode()const{
	return code;
}

std::string Potion::message() const {
	std::string s="";
	s = " You see a " + name + ".";
	return s; 
}

bool Potion::getUsed() const{
	return used;
}

void Potion::setUsed(){
	used = true;
} 

