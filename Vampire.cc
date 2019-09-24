#include "Vampire.h"
#include "Floor.h"
#include "NPC.h"
#include "gold.h"
#include "Potion.h"
#include <cmath>
#include <cstdlib>

Vampire::Vampire():PC{-1}{
	hp = 50;
	atk = 25;
	def = 25;
	race = "Vampire";
}
Vampire::~Vampire(){}

void Vampire::Attack(int x, int y){
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
		if(temp->getRace() != "Dwarf"){//Vampire specials
			action += "You leech 5HP.";
			this->hp += 5;
		}else if(temp->getRace() == "Dwarf"){
			action += "You are allergic to Dwarves! STOP ATTACKING THEM!";
			this->hp -= 5;
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

void Vampire::resetStats(){
	atk = 25;
	def = 25;
}

