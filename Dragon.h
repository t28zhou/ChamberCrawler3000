#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "NPC.h"
#include "gold.h"

class Gold;
class PC;

class Dragon:public NPC{
	Gold *dragonHoard;
public:
	Dragon(int x, int y, Floor *fl, Gold *g);
	virtual ~Dragon();
	virtual bool beAttacked(PC *p)override;
	virtual void move(PC *p)override;
	virtual Gold * getDG()const override;
};

#endif

