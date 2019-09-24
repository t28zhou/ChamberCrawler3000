#ifndef _GOLD_H_
#define _GOLD_H_
#include "Part.h"

class Gold: public Part{
	int value;
	bool pickable;
public:
	Gold(int x, int y, Floor *fl, int value, bool pick);
	~Gold();
	int getValue()const;
	bool getPickable()const;
	void setPickable();
};

#endif

