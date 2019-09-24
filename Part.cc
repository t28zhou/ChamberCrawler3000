#include "Part.h"
#include "Floor.h"

Part::Part(int x,int y, Floor *fl):xPos{x},yPos{y},active{fl}{}

Part::~Part(){}

int Part::getX()const{
	return xPos;
}

int Part::getY()const{
	return yPos;
}

char Part::getSym()const{
	return symbol;
}

