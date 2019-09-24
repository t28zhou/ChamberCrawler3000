#include "Tracker.h"
#include "PC.h"
#include "Floor.h"
#include <cmath>
#include <cstdlib>

Tracker::Tracker(int x, int y, Floor *fl):NPC{x,y,fl}{
	hp = 200;
	atk = 40;
	def = 5;
	race = "Tracker";
	symbol = 'K';
	curTile = '.';
}
char Tracker::getCur(){
	return curTile;
}
Tracker::~Tracker(){}

void Tracker::move(PC *p){
	int pX = p->getX();
	int pY = p->getY();
	char newCell = '.';
	for(int i = -10; i <= 10; ++i){
        for(int j = -10; j <= 10; ++j){
            int e_xrange = xPos + j;
            int e_yrange = yPos + i;
            if(pX == e_xrange && pY == e_yrange){//player is within range
            	if(i == 0 && j < 0){//player is to the North
            		newCell = active->getCellChar(xPos - 1, yPos);
            		if(newCell == '.' || newCell == '+' || newCell == '#'){
            			active->movePart(xPos, yPos, xPos - 1, yPos, symbol, curTile);
				curTile = newCell;
            			xPos = xPos - 1;
   }         			return;
 //           		}
            	}else if(i == 0 && j > 0){//player is to the South
            		newCell = active->getCellChar(xPos + 1, yPos);
            		if(newCell == '.' || newCell == '+' || newCell == '#'){
            			active->movePart(xPos, yPos, xPos + 1, yPos, symbol, curTile);
				curTile = newCell;
            			xPos = xPos + 1;
      }      			return;
    //        		}
            	}else if(i < 0 && j == 0){//player is West
            		newCell = active->getCellChar(xPos, yPos - 1);
                    	if(newCell == '.' || newCell == '+' || newCell == '#'){
                        	active->movePart(xPos, yPos, xPos, yPos - 1, symbol, curTile);
				curTile = newCell;
                        	yPos = yPos - 1;
         }               	return;
       //            	 }
                }else if(i > 0 && j == 0){//player is East
                	newCell = active->getCellChar(xPos, yPos + 1);
                	if(newCell == '.' || newCell == '+' || newCell == '#'){
				active->movePart(xPos, yPos, xPos, yPos + 1, symbol, curTile);
				curTile = newCell;
                		yPos = yPos + 1;
            }    		return;
          //      	}
                }else if(i < 0 && j < 0){//player is NorthWest
                	newCell = active->getCellChar(xPos - 1, yPos - 1);
                	if(newCell == '.' || newCell == '+' || newCell == '#'){
                		active->movePart(xPos, yPos, xPos - 1, yPos - 1, symbol, curTile);
                		curTile = newCell;
				xPos = xPos - 1;
                		yPos = yPos - 1;
               } 		return;
             //   	}
                }else if(i > 0 && j > 0){//player is SouthEast
                	newCell = active->getCellChar(xPos + 1, yPos + 1);
                	if(newCell == '.' || newCell == '+' || newCell == '#'){
                		active->movePart(xPos, yPos, xPos + 1, yPos + 1, symbol, curTile);
                		curTile = newCell;	
				xPos = xPos + 1;
                		yPos = yPos + 1;
                }		return;
                //	}
                }else if(i < 0 && j > 0){//player is SouthWest
                	newCell = active->getCellChar(xPos + 1, yPos - 1);
                	if(newCell == '.' || newCell == '+' || newCell == '#'){
                		active->movePart(xPos, yPos, xPos + 1, yPos - 1, symbol, curTile);
                		curTile = newCell;
				xPos = xPos + 1;
                		yPos = yPos - 1;
                }		return;
                //	}
                }else{//player is NorthEase
                	newCell = active->getCellChar(xPos - 1, yPos + 1);
                	if(newCell == '.' || newCell == '+' || newCell == '#'){
                		active->movePart(xPos, yPos, xPos - 1, yPos + 1, symbol, curTile);
				curTile = newCell;
                		xPos = xPos - 1;
                		yPos = yPos + 1;
                }		return;
                //	}
                }
            }
        }
    }
	int moveX = rand() % 3 - 1; // Either -1, 0, 1 to move in each direction
	int moveY = rand() % 3 - 1;
	int newX = xPos + moveX;
	int newY = yPos + moveY;
	newCell = active->getCellChar(newX,newY);
	int m = 0;
	while(true){
		if(newCell != '.'){
			moveX = rand() % 3 - 1;
			moveY = rand() % 3 - 1;	
			newX = xPos + moveX;
			newY = yPos + moveY;
			newCell = active->getCellChar(newX, newY);
		}else{  
 			active->movePart(xPos,yPos,newX,newY,symbol,curTile);
        		this->xPos += moveX;
        		this->yPos += moveY;
        		curTile = newCell;
			break;
		}
		if(m == 10){
		  break;
		}
		++m;
	}
}

