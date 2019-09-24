#include "Goblin.h"
#include "Floor.h"
#include "NPC.h"
#include "gold.h"
#include "Potion.h"
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;


Goblin::Goblin():PC{110}{
	hp = 110;
	atk = 15;
	def = 20;
	race = "Goblin";
}
Goblin::~Goblin(){

}

void Goblin::beAttacked(NPC *en){
	double trying = 100.0 / (100 + def);
	int atkNPC = en->getAtk();
	double damB = trying * atkNPC;
	int damage = ceil(damB);
	if(en->getRace() == "Orcs"){//This part is Goblin specific
		//Orcs does 50% more damage to Goblins
		action += " Orcs does 50% more damage to you. RUNNNNNN!";//we will use integers since decimal HP doesnt make sense
		damage *= 1.5;
	}
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

void Goblin::Attack(int x, int y){
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
				//Damn 'em Goblins, they get extra 5 gold
				gold += 5;
			}
		}else{
			action += "YOU MISSED!";
		}
	}else{//if attempt to attack nothing. LOL
		action += "You wiff a potentially fatal hit, you look around, thankfully nobody was watching.";
	}
}

void Goblin::resetStats(){
	atk = 15;
	def = 20;
}

