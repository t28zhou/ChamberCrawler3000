#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "NPC.h"


class Merchant:public NPC{
	bool angry;
public:
	Merchant(int x, int y, Floor *fl);
	virtual ~Merchant();
	virtual bool isAngry()const override;
	virtual void makeAngry()override;
	virtual bool beAttacked(PC *p)override;
};

#endif

