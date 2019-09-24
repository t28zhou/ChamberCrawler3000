#ifndef _DROW_H_
#define _DROW_H_
#include "PC.h"

class Potion;

class Drow: public PC{
public:
	Drow();
	virtual ~Drow();
	virtual void usePotion(int x, int y)override;
	virtual void resetStats()override;
};


#endif

