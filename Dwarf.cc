#include "Dwarf.h"

Dwarf::Dwarf(int x, int y, Floor *fl): NPC{x,y,fl}{
	hp = 100;
	atk = 20;
	def = 30;
	symbol = 'W';
	race = "Dwarf";
}

Dwarf::~Dwarf(){}

