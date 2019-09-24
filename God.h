#ifndef _GOD_H_
#define _GOD_H_
#include "PC.h"


class God: public PC{
public:
	God();
	~God();
	virtual void Attack(int x, int y)override;
	virtual void beAttacked(NPC *en)override;
	virtual void resetStats()override;
};

#endif

