#include <string>
#include "PC.h"
#include "Floor.h"
#include "NPC.h"
#include "Potion.h"
#include "gold.h"
#include <cmath>
#include <cstdlib>

using namespace std;

PC::PC(int max):Character{},maxHP{max}{
	xPos = 0;
	yPos = 0;
	gold = 0;
	floor = 1;
	symbol = '@';
	action = "";
	curTile = '.';
	alive = true;
}
PC::~PC(){}
int PC::getGold()const{
	return this->gold;
}

int PC::getfloorNum()const{
	return floor;
}

void PC::attachAction(string newAction){
	this->action += newAction;
}

void PC::setFloor(Floor *newFloor){
	active = newFloor;
}

void PC::setCoords(int x, int y){
	this->xPos = x;
	this->yPos = y;
}

void PC::beAttacked(NPC *en){
	double trying = 100.0 / (100 + def);
	int atkNPC = en->getAtk();
	double damB = trying * atkNPC;
	int damage = ceil(damB);
	this->hp -= damage;
	action += " You are attacked by " + en->getRace() + " hurt by " + to_string(damage) + ".";
	if(hp <= 0){
		hp = 0;
		alive = false;
		action += " You are now dead.";
	}else{
		action += " You survived the hit, with " + to_string(hp) + " remaining.";
	}
}

void PC::clearAction(){
	action = "";
}

void PC::Attack(int x, int y){
	this->clearAction();
	int checkPosX = this->xPos + x;
	int checkPosY = this->yPos + y;
	int missBy = 50;
	NPC *temp = active->getNPC(checkPosX, checkPosY);//Finding an enemy, if there is one, findEnemy will return that enemy
	//if no enemy found, return nullptr.
	if(temp != nullptr){//if an enemy is targeted
		if(temp->getRace() == "Halfling"){
			missBy = rand() % 100;
		}
		if(missBy <= 99 && missBy >= 49){
			if(temp->beAttacked(this)){ //if the damage is not fatal, so its just true/false
										//the damage is subtracted from the enemy's HP in this method. 
										//beAttacked() is a no-throw method
				char killed = temp->getSym();//getting the killed enemy's symbol to determine 
												//what to do with it.
				active->removeNPC(temp->getX(), temp->getY());//this method removes the enemy.
				if(killed != 'M' && killed != 'H' && killed != 'D'){//if it is not a human, merchant or dragon
					gold += rand() % 2 + 1;//generates a random number between 1-2
					//Randomly generate gold.
				}else if(killed == 'M'){
					active->dropMGold(checkPosX, checkPosY);
				}else if(killed == 'H'){
					active->dropHGold(checkPosX, checkPosY);
				}
				
			}
		}else{
			action += "YOU MISSED!";
		}
	}else{//if attempt to attack nothing. LOL
		action += "You wiff a potentially fatal hit, you look around, thankfully nobody was watching.";
	}
}

void PC::usePotion(int x, int y){
	this->clearAction();
	int newX = this->xPos + x;
	int newY = this->yPos + y;
	Potion *p = active->getPotion(newX,newY);
	action += "You tried to use the potion";
	if(p != nullptr){
		int pt = p->getCode();
		if(pt == 0){
			this->hp += 10;
			if(this->hp > this->maxHP){
				this->hp = this->maxHP;
			}
			action += ", your HP is restored by 10 points.";
		}else if(pt == 1){
			this->atk += 5;
			action += ", your Attack is boosted by 5 points.";
		}else if(pt == 2){
			this->def += 5;
			action += ", your Defense is boosted by 5 points.";
		}else if(pt == 3){
			this->hp -= 10;
			if(this->hp <= 0){
				this->hp = 1;
			}
			action += ", your HP is poisoned by 10 points.";
		}else if(pt == 4){
			this->atk -= 5;
			if(this->atk <= 0){
				this->atk = 1;
			}
			action += ", your Attack is decreased by 5 points.";
		}else if(pt == 5){
			this->def -= 5;
			if(this->def <= 0){
				this->def = 1;
			}
			action += ", your Defense is decreased by 5 points.";
		}
		active->removePotion(newX,newY);
	}else{
		action += ", nothing happened.";
	}
	
}

bool PC::move(int x, int y){
	int newX = this->xPos + x;
	int newY = this->yPos + y;
	char newCell = active->getCellChar(newX, newY);//this gets the next moved tile. Since the fields are private
	if(newCell == '.' || newCell == '#' || newCell == '+' || newCell == '\\' || newCell == 'G'){
		if(newCell == '\\'){
			floor += 1;
			action += " You are now on a new floor. Floor number: " + to_string(floor) + ".";
			curTile = '.'; //since stairs are always spawned in rooms.
			return true;
		}else if(newCell == 'G'){
			bool getIt = active->checkGoldGetable(newX, newY);//this should check the Gold's surroundings to 
													//see if there is a dragon
			if(getIt){//Normal Gold
				int worth = active->getGoldValue(newX, newY);
				//Gold *gotIt = active->getGold(newX, newY);
				action += " You got " + to_string(worth) + " gold!";
				gold += worth;
				active->movePart(xPos, yPos, newX, newY, symbol, curTile);
				this->xPos = newX;
				this->yPos = newY;
				curTile = '.';
			}else{//Dragon Hoard
				active->movePart(xPos, yPos, newX, newY, symbol, curTile);
				this->xPos = newX;
				this->yPos = newY;
				curTile = newCell;
				action += " You tried to grab the gold, but it seems like there's a dragon nearby.";

			}
		}else{//Everything Else
			active->movePart(xPos, yPos, newX, newY, symbol, curTile);
			this->xPos = newX;
			this->yPos = newY;
			curTile = newCell;
		}
		int potionN = active->potionNear(xPos, yPos);//the finding potion around 1 block radius is done inside Board class
		if(potionN>0){
			if (potionN ==1) {action += " You see an unknown potion nearby.";}
			else {action += " You see " + to_string(potionN) + " unknown potions nearby.";}
		}
	}else{
		action += " But there's a magical force stopping it from doing so.";
	}
	return false;
}

string PC::displayState(){
	string retThis = "Race: " + race;
	retThis += " | Gold: " + to_string(gold) + "                                               " 
	+ "Floor : " + to_string(floor) +'\n';
	retThis += "HP: " + to_string(hp) + '\n';
	retThis += "Att: " + to_string(atk) + '\n';
	retThis += "Def: " + to_string(def) + '\n';
	retThis += "What happened: " + action + '\n';
	return retThis;
}




