#ifndef _NPC_H_
#define _NPC_H_
#include "character.h"


class PC;
class Gold;

class NPC:public Character{
public:
	NPC(int x, int y, Floor *fl);
	virtual ~NPC() = 0;
	virtual void attack(PC *p);
	virtual bool beAttacked(PC *p);
	virtual void move(PC *p);
	virtual bool isAngry()const;
	virtual void makeAngry();
	virtual Gold * getDG()const;
	virtual char getCur();
};

#endif

