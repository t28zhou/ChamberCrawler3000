#include "Phoenix.h"
#include "Potion.h"
#include "Floor.h"
#include "NPC.h"
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

using namespace std;

Phoenix::Phoenix():PC{120}{
	hp = 120;
	atk = 25;
	def = 30;
	reved = false;
	race = "Phoenix";
}

Phoenix::~Phoenix(){}

void Phoenix::resetStats(){
	atk = 25;
	def = 30;
}
void Phoenix::beAttacked(NPC *en){
	double trying = 100.0 / (100 + def);
	int atkNPC = en->getAtk();
	double damB = trying * atkNPC;
	int damage = ceil(damB);
	this->hp -= damage;
	action += " You are attacked by " + en->getRace() + " hurt by " + to_string(damage) + ".";
	if(hp <= 0){
		hp = 0;
		if(!reved){//revived if not revived before
			reved = true;
			race = "Rebirthed Phoenix";
			hp = maxHP;
			action += " Phoenix rebirth!";
		}else{
			alive = false;
			action += " You are now dead.";
		}
	}else{
		action += " You survived the hit, with " + to_string(hp) + " remaining.";
	}
}

void Phoenix::Attack(int x, int y){
	this->clearAction();
	int checkPosX = this->xPos + x;
	int checkPosY = this->yPos + y;
	int missBy = 50;
	NPC *temp = active->getNPC(checkPosX, checkPosY);//Finding an enemy, if there is one, findEnemy will return that enemy
	//if no enemy found, return nullptr.
	if(temp != nullptr){//if an enemy is targeted
		for(int i = 1; i <= 2; ++i){
			if(i == 2){
				action += " Phoenix's second attack!";
			}
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
						if(this->getRace() == "Goblin"){//Damn 'em Goblins, they get extra 5 gold
							gold += 5;
						}
					}else if(killed == 'M'){
						active->dropMGold(checkPosX, checkPosY);
					}else if(killed == 'H'){
						active->dropHGold(checkPosX, checkPosY);
					}
					break;
				}
			}else{
				action += "YOU MISSED!";
			}
			missBy = 50;
		}
	}else{//if attempt to attack nothing. LOL
		action += "You wiff a potentially fatal hit, you look around, thankfully nobody was watching.";
	}
}

void Phoenix::usePotion(int x, int y){
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
			this->hp += 10;
			if(this->hp <= 0){
				this->hp = 1;
			}
			action += ", your HP is poisoned by 10 points, but you are a phoenix.";
		}else if(pt == 4){
			this->atk += 5;
			if(this->atk <= 0){
				this->atk = 1;
			}
			action += ", your Attack is decreased by 5 points, but you are a phoenix.";
		}else if(pt == 5){
			this->def += 5;
			if(this->def <= 0){
				this->def = 1;
			}
			action += ", your Defense is decreased by 5 points, but you are a phoenix";
		}
		active->removePotion(newX,newY);
	}else{
		action += ", nothing happened.";
	}
	
}

