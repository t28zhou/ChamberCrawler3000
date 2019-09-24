#include "gold.h"

Gold::Gold(int x, int y, Floor *fl, int value, bool pick):Part{x,y,fl},value{value},pickable{pick}{
	symbol = 'G';
}

Gold::~Gold(){}

int Gold::getValue()const{
	return value;
}

bool Gold::getPickable()const{
	return pickable;
}

void Gold::setPickable(){
	pickable = true;
}

