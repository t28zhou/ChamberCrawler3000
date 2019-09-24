#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "PC.h"

class Goblin: public PC{
public:
	Goblin();
	virtual ~Goblin();
	virtual void beAttacked(NPC *en)override;
	virtual void Attack(int x, int y)override;
	virtual void resetStats()override;
};


#endif

