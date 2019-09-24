#include "Drow.h"
#include "Floor.h"
#include "Potion.h"

Drow::Drow():PC{150}{
	hp = 150;
	atk = 25;
	def = 15;
	race = "Drow";
}

Drow::~Drow(){
	
}

void Drow::usePotion(int x, int y){
	this->clearAction();
	int newX = this->xPos + x;
	int newY = this->yPos + y;
	Potion *p = active->getPotion(newX,newY);
	action += "You tried to use the potion";
	if(p != nullptr){
		int pt = p->getCode();
		action += " since you are a Drow, your potion effects are magnified by 1.5.";
		if(pt == 0){
			this->hp += 15;
			if(this->hp > this->maxHP){
				this->hp = this->maxHP;
			}
			action += " your HP is restored by 15 points.";
		}else if(pt == 1){
			this->atk += 7;
			action += " your Attack is boosted by 7 points.";
		}else if(pt == 2){
			this->def += 7;
			action += " your Defense is boosted by 7 points.";
		}else if(pt == 3){
			this->hp -= 15;
			if(this->hp <= 0){
				this->hp = 1;
			}
			action += " your HP is poisoned by 15 points.";
		}else if(pt == 4){
			this->atk -= 7;
			if(this->atk <= 0){
				this->atk = 1;
			}
			action += " your Attack is decreased by 7 points.";
		}else if(pt == 5){
			this->def -= 7;
			if(this->def <= 0){
				this->def = 1;
			}
			action += " your Defense is decreased by 7 points.";
		}
		active->removePotion(newX,newY);
	}else{
		action += " nothing happened.";
	}
	
}

void Drow::resetStats(){
	atk = 25;
	def = 15;
}



