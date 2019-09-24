#ifndef _ELF_H_
#define _ELF_H_
#include "NPC.h"

class PC;

class Elf: public NPC{
public:
	Elf(int x, int y, Floor *fl);
	virtual ~Elf();
	virtual void attack(PC *p)override;
};

#endif

