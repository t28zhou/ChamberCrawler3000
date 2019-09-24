#ifndef _POTION_H_
#define _POTION_H_
#include <string>
#include "Part.h"

class Potion: public Part{
	int code;
	std::string name;
	bool used;
public:
	Potion(int x, int y, Floor *fl, int type, std::string, bool);
	~Potion();
	int getCode()const;
	std::string message() const;
	bool getUsed() const;
	void setUsed();
};

#endif

