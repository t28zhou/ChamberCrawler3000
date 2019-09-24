#ifndef _DWARF_H_
#define _DWARF_H_
#include "NPC.h"

class Dwarf:public NPC{
public:
	Dwarf(int x, int y, Floor *fl);
	virtual ~Dwarf();
};

#endif

