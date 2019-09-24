#include "God.h"
#include "Floor.h"
#include "NPC.h"
#include <string>
#include "gold.h"
#include <cstdlib>
using namespace std;

God::God():PC{1000}{
	hp = 1000;
	atk = 500;
	def = 100000;
	race = "God";
}

God::~God(){}

void God::resetStats(){
	atk = 500;
	def = 100000;
}

void God::Attack(int x, int y){
        this->clearAction();
	int checkPosX = this->xPos + x;
	int checkPosY = this->yPos + y;
	NPC *temp = active->getNPC(checkPosX, checkPosY);//Finding an enemy, if there is one, findEnemy will return that enemy
	//if no enemy found, return nullptr.
	if(temp != nullptr){//if an enemy is targeted\char killed = temp->getSym();//getting the killed enemy's symbol to determine 
											//what to do with it.
		char killed = temp->getSym();
                if (killed == 'D') {temp->getDG()->setPickable();} // make it getable
		action += " You spit it with the almighty lightning. You killed it with one shot.";
		active->removeNPC(temp->getX(), temp->getY());//this method removes the enemy.
		if(killed != 'M' && killed != 'H' && killed != 'D'){//if it is not a human, merchant or dragon
				gold += rand() % 2 + 1;//generates a random number between 1-2
				//Randomly generate gold.
				}
		else if(killed == 'M'){
			active->dropMGold(checkPosX,checkPosY);
		}else if(killed == 'H'){
			active->dropHGold(checkPosX,checkPosY);
		}
	}else{//if attempt to attack nothing. LOL
		action += "you wiff a fatal hit, You look around, thankfully nobody was watching.";
	}

}
void God::beAttacked(NPC *en){
	action += " You cannot be attacked!";
}



