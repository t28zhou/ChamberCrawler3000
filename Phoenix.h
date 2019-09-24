#ifndef _PHOENIX_H_
#define _PHOENIX_H_
#include "PC.h"
#include <string>


//Phoenix attacks twice, and gets to respawn once, and Potions have no negative side effects.
class Phoenix: public PC{
	bool reved;
public:
	Phoenix();
	~Phoenix();
	virtual void Attack(int x, int y);
	virtual void beAttacked(NPC *en);
	virtual void usePotion(int x, int y);
	virtual void resetStats();
};


#endif


