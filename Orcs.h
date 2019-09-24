#ifndef _ORCS_H_
#define _ORCS_H_
#include "NPC.h"

class Orcs:public NPC{
public:
	Orcs(int x, int y, Floor *fl);
	virtual ~Orcs();
};

#endif

