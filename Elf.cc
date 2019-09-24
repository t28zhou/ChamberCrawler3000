#include "Elf.h"
#include "PC.h"
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

Elf::Elf(int x,int y, Floor *fl):NPC{x,y,fl}{
	hp = 140;
	atk = 30;
	def = 10;
	symbol = 'E';
	race = "Elf";
}

Elf::~Elf(){}

void Elf::attack(PC *p){
	int miss = rand() % 100;
	string s;
	if(miss >= 49 && miss <= 99){
		p->beAttacked(this);
	}else{
		s = " " + race + " miss a deadly shot.";
	}
	miss = rand() % 100;
	if(p->getRace() != "Drow"){
		if(miss >= 49 && miss <= 99){
			p->beAttacked(this);
		}else{
			s = " " + race + " miss a second deadly shot.";
			p->attachAction(s);
		}
	}else{
		p->attachAction(s);
	}
	
}

