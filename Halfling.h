#ifndef _HALFLING_H_
#define _HALFLING_H_
#include "NPC.h"

//Do the 50% miss thing.

class Halfling:public NPC{
public:
	Halfling(int x, int y, Floor *fl);
	virtual ~Halfling();
};

#endif

