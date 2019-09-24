#ifndef _PC_H_
#define _PC_H_
#include "character.h"
#include <string>

class NPC;
class Gold;
class Potion;

class PC: public Character{
protected:
	int maxHP;
	int gold;
	std::string action;
	int floor;
public:
	PC(int max);
	~PC() = 0;
	int getGold()const;
	void attachAction(std::string newAction);
	int getfloorNum()const;
	void setFloor(Floor *newFloor);
	void setCoords(int x, int y);
	virtual void Attack(int x, int y);//I used Floor's findNPC(int,int),
	//findEnemy should return a NPC pointer, it basically loops through the adjacent blocks
	//to find if PC is indeed attacking a NPC.
	//Also I used removeNPC(int,int), this removes the enemy and change the tile back to '.'
	virtual void beAttacked(NPC *en);
	virtual bool move(int x, int y);//I used getCell(int,int) this function should return the character at that location
	//Also used checkGold(int,int) to see if the gold is getable. this func returns a bool
	//Also used getGold(int,int), which should get the value of the gold at location
	//Also used movePiece(oldx,oldy,newx,newy,symbol,standingon) moves the piece
	//Also used potionNear(int,int), this function should check if theres a potion near the xpos and ypos, should return bool
	virtual void usePotion(int x, int y);
	virtual void resetStats() = 0;
	void clearAction();
	std::string displayState();
};


#endif

