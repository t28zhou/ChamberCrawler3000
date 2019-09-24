#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include <vector>
#include "Part.h"

class Character: public Part{
protected:
	int hp;
	int atk;
	int def;
	bool alive;
	std::string race;
	char curTile;
public:
	Character();
	virtual ~Character() = 0;
	virtual bool checkDead() const;
	virtual std::string getRace() const;
	virtual int getAtk() const;
	virtual int getDef() const;
	virtual int getHp() const;
// 	char getCurTile () const;
};

#endif

