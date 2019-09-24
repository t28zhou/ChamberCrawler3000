
#ifndef _SHADE_H_
#define _SHADE_H_
#include "PC.h"

class Shade: public PC{
public:
	Shade();
	virtual ~Shade();
	virtual void resetStats()override;
};


#endif

