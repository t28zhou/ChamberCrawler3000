#include "Merchant.h"
#include "PC.h"
#include "Floor.h"
#include <cmath>
#include <string>
using namespace std;

Merchant::Merchant(int x,int y, Floor *fl):NPC{x,y,fl}{
	hp = 30;
	atk = 70;
	def = 5;
	symbol = 'M';
	race = "Merchant";
	angry = false;
}

Merchant::~Merchant(){}

bool Merchant::isAngry()const{
	return angry;
}

void Merchant::makeAngry(){
	angry = true;
}

bool Merchant::beAttacked(PC *p){
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
		p->attachAction(s);
		this->makeAngry();
		active->notifyAllMerchant();
		return true;
	}else{
		s += " " + this->race + " has " + to_string(this->hp) + " HP left.";
		p->attachAction(s);
	}
	return false;
}

