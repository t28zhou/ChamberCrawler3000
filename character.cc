#include "character.h"
//#include "Floor.h"
#include <string>
using namespace std;

Character::Character():Part{0,0,nullptr}{
	race = "";
}

Character::~Character(){}

bool Character::checkDead()const{
	return !(this->alive);
}

string Character::getRace()const{
	return this->race;
}

int Character::getAtk()const{
	return this->atk;
}

int Character::getDef()const{
	return this->def;
}

int Character::getHp()const{
	return this->hp;
}

//char Character::getCurTile() const {
//	return this->curTile;
//}

