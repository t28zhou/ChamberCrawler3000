#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "NPC.h"

class Human:public NPC{
public:
	Human(int x, int y, Floor *fl);
	virtual ~Human();
};

#endif

