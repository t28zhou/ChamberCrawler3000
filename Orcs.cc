#include "Orcs.h"

Orcs::Orcs(int x, int y, Floor *fl):NPC{x,y,fl}{
	hp = 180;
	atk = 30;
	def = 25;
	race = "Orcs";
	symbol = 'O';
}

Orcs::~Orcs(){}

