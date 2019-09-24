#include "Halfling.h"

Halfling::Halfling(int x, int y, Floor *fl):NPC{x,y,fl}{
	hp = 100;
	atk = 15;
	def = 20;
	symbol = 'L';
	race = "Halfling";
}

Halfling::~Halfling(){}

