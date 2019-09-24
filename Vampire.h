#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_
#include "PC.h"

class Vampire: public PC{
public:
	Vampire();
	virtual ~Vampire();
	virtual void Attack(int x, int y)override;
	virtual void resetStats()override;
};


#endif

