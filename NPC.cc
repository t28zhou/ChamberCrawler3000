#include <string>
#include "NPC.h"
//#include "PC.h"
#include "Shade.h"
#include "Troll.h"
#include "Vampire.h"
#include "Goblin.h"
#include "Drow.h"
#include "Floor.h"
#include "gold.h"
#include <cmath>
#include <cstdlib>
using namespace std;

NPC::NPC(int x,int y, Floor *fl):Character(){
	xPos = x;
	yPos = y;
	curTile = '.';
	active = fl;
	symbol = '&';
}

Gold *NPC::getDG()const{
	return nullptr;
}

char NPC::getCur() {return curTile;}


NPC::~NPC(){}

void NPC::attack(PC *p){
	int miss = rand() % 100;
	if(miss >= 49 && miss <= 99){
		p->beAttacked(this);
	}else{
		string s = " " + race + " miss a deadly shot.";
		p->attachAction(s);
	}
}

bool NPC::beAttacked(PC *p){
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
		return true;
	}else{
		s += " " + this->race + " has " + to_string(this->hp) + " HP left.";
		p->attachAction(s);
	}
	return false;
}



void NPC::move(PC *p){
	int moveX = rand() % 3 - 1;
	int moveY = rand() % 3 - 1;
	while(true){//if both of them are 0, 
		//then this loop make sure the NPC moves in any of the four directions
		if (moveX == 0 && moveY == 0){
			moveX = rand() % 3 - 1;
			moveY = rand() % 3 - 1;
		}else{
			break;
		}
	}
	int newX = this->xPos + moveX;
	int newY = this->yPos + moveY;
	char newCell = active->getCellChar(newX, newY);
	int m =0;
	while(true){
		if(newCell != '.'){
			moveX = rand() % 3 - 1;
			moveY = rand() % 3 - 1;	
			newX = this->xPos + moveX;
			newY = this->yPos + moveY;
			newCell = active->getCellChar(newX, newY);
		}else{
		        active->movePart(xPos,yPos,newX,newY,symbol,curTile);
			this->xPos += moveX;
			this->yPos += moveY;
			curTile = newCell;
			break;
		}
		if(m == 9){
		  newX = this->xPos;
		  newY = this->yPos;
		  break;
		}
		m +=1;
	}
	
}

bool NPC::isAngry()const{
	return true;
}

void NPC::makeAngry(){}


