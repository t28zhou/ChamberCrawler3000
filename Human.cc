#include "Human.h"

Human::Human(int x,int y, Floor *fl):NPC{x,y,fl}{
	hp = 140;
	atk = 20;
	def = 20;
	symbol = 'H';
	race = "Human";
}

Human::~Human(){}

