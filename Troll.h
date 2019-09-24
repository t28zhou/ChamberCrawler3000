#ifndef _TROLL_H_
#define _TROLL_H_
#include "PC.h"

class Troll: public PC{
public:
	Troll();
	virtual ~Troll();
	virtual void Attack(int x, int y)override;
	virtual void usePotion(int x, int y)override;
	virtual bool move(int x, int y)override;
	virtual void resetStats()override;
};


#endif

