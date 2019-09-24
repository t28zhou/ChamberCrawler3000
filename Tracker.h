#ifndef _TRACKER_H_
#define _TRACKER_H_
#include "NPC.h"


class PC;

class Tracker:public NPC{
	char curTile;
public:
	Tracker(int x, int y, Floor *fl);
	virtual char getCur() override;
	virtual ~Tracker();
	virtual void move(PC *p)override;
};

#endif
