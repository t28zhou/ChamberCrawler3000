#ifndef _PART_H_
#define _PART_H_

class Floor;

class Part{
protected:
	int xPos;
	int yPos;
	Floor *active;
	char symbol;
public:
	Part(int x, int y, Floor *fl);
	virtual ~Part() = 0;
	int getX()const;
	int getY()const;
	char getSym()const;
};


#endif

