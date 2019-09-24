#include "PC.h"
#include "Dragon.h"
#include <string>
#include <cmath>

using namespace std;
Dragon::Dragon(int x, int y, Floor *fl, Gold *g):NPC{x,y,fl},dragonHoard{g}{
	hp = 150;
	atk = 20;
	def = 20;
	symbol = 'D';
	race = "Dragon";
}

Dragon::~Dragon(){}

Gold *Dragon::getDG()const{
	return dragonHoard;
}

bool Dragon::beAttacked(PC *p){
	double trying = 100.0 / (100 + def);
	int atkPC = p->getAtk();
	double damB = trying * atkPC;
	int damage = ceil(damB);
	this->hp -= damage;
	string s = " PC deals " + to_string(damage) + " damage to ";
	s += this->race + ".";
	if(hp <= 0){
		hp = 0;
		s += " " + this->race + " is now dead!";
		s += " The DragonHoard is now able to be picked up!";
		p->attachAction(s);
		dragonHoard->setPickable();
		return true;
	}else{
		s += " " + this->race + " has " + to_string(this->hp) + " HP left.";
		p->attachAction(s);
	}
	return false;
}

void Dragon::move(PC *p){
	
}

