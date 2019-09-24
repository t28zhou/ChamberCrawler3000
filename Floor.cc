#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Floor.h"
#include "PC.h"
#include "NPC.h"
#include "Potion.h"
#include "gold.h"
#include "Human.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Orcs.h"
#include "Merchant.h"
#include "Dragon.h"
#include "Halfling.h"
#include "Tracker.h"
using namespace std;


#include <ncurses.h>


// constant definition
const int NumCol = 79;
const int NumRow = 25;
const int NumPotion = 10;
const int NumGold = 10;
const int NumNPC = 20;
const int NumChamber =5;

// private flags and display
char FloorDisplay[NumRow][NumCol];             // floor display
bool caught[NumRow][NumCol];                   // flag to catch all valid '.'s
vector < vector<pair<int,int>>> allChamber;    // vector of 5 chambers' coordinates

// ctor
Floor::Floor(PC* player, const string input, int upperFloorLineNum, bool checkFile){//if read from the first floor
	angryMerchant=false;

	RHused = false;
	BAused = false;
	BDused = false;
	PHused = false;
	WAused = false;
	WDused = false;
	thePC = player;
	thePC -> setFloor (this);

	ifstream file {input};
	if(!file){return;}//no input  exists

	// set all flags to false
        for (int i=0;i<NumRow;++i) {
		for (int j=0;j<NumCol;j++){                     
			caught[i][j] = false;}}

	string line;
	// throw previous floors away
	for(int i=0; i<upperFloorLineNum; ++i){getline(file, line);}

	//read the lines beginning from upperFloorLineNum
	for(int i=0; i<NumRow; ++i){
		getline(file, line);
		for(int j=0;j<NumCol; ++j){
			char symbol = line[j];
			FloorDisplay[i][j]=symbol;}}

        // initialize allChamber 
	allChamber.clear();
	for (int k=0; k<NumChamber;++k) {
		vector <pair<int,int>> vp;
		allChamber.emplace_back(vp);
	}	

	// random generate
	if (checkFile == false) {
		attachCham();
		placePCandStairway();
		placePotion();
		placeGold();
		placeNPC();
		return;
	}

	// read in
	for (int i= 0;i<NumRow;++i) {
		for (int j=0;j<NumCol;++j) {
			char symbol = FloorDisplay[i][j];
			// PC 
			if(symbol =='@'){
				thePC->setCoords(i,j);

				// NPC
			}else if(symbol == 'H'){
				allNPC.emplace_back( new Human(i,j,this));
			}else if(symbol == 'W'){
				allNPC.emplace_back( new Dwarf(i,j,this));
			}else if(symbol == 'E'){
				allNPC.emplace_back(new Elf(i,j,this));
			}else if(symbol == 'O'){
				allNPC.emplace_back(new Orcs(i,j,this));
			}else if(symbol == 'M'){
				allNPC.emplace_back(new Merchant(i,j,this));
			}else if(symbol == 'L'){
				allNPC.emplace_back( new Halfling(i,j,this));
			}else if (symbol == 'K') {allNPC.emplace_back(new Tracker(i,j,this));}


				// Potion
			else if(symbol == '0'){//RH
				allPotions.emplace_back(new Potion(i,j,this,0,"RH",RHused));
				FloorDisplay[i][j]= 'P';
			}else if(symbol == '1'){//BA
				allPotions.emplace_back(new Potion(i,j,this,1,"BA",BAused));
				FloorDisplay[i][j]= 'P';
			}else if(symbol == '2'){//BD
				allPotions.emplace_back(new Potion(i,j,this,2,"BD",BDused));
				FloorDisplay[i][j]= 'P';
			}else if(symbol == '3'){//PH
				allPotions.emplace_back(new Potion(i,j,this,3,"PH",PHused));
				FloorDisplay[i][j]= 'P';
			}else if(symbol == '4'){//WA
				allPotions.emplace_back(new Potion(i,j,this,4,"WA",WAused));
				FloorDisplay[i][j]= 'P';
			}else if(symbol == '5'){//WD
				allPotions.emplace_back(new Potion(i,j,this,5,"WD",WDused));
				FloorDisplay[i][j]= 'P';
			}

			// all Gold
			else if(symbol == '6'){//normal gold pile
				allGold.emplace_back(new Gold(i,j,this,2, true));
				FloorDisplay[i][j]= 'G';
			}else if(symbol == '7'){//small hoard
				allGold.emplace_back(new Gold(i,j,this,1, true));
				FloorDisplay[i][j]= 'G';
			}else if(symbol == '8'){//merchant hoard
				allGold.emplace_back(new Gold(i,j,this,4, true));
				FloorDisplay[i][j]= 'G';
			}else if(symbol == '9'){//dragon hoard
				Gold * dragonhoard = new Gold(i,j,this,6 , false);
				allGold.emplace_back(dragonhoard);
				FloorDisplay[i][j]= 'G';
				for(int ii=-1; ii<2; ++ii){
					for(int jj=-1; jj<2;++jj){
						int dragonX = ii+dragonhoard->getX();
						int dragonY = jj+dragonhoard->getY();
						if ((FloorDisplay[dragonX][dragonY] == 'D') && (getNPC(dragonX,dragonY) == nullptr)) {
							allNPC.emplace_back(new Dragon(dragonX,dragonY,this, dragonhoard));
						}
					}
				}
			}

		}
	}
}

// dtor
Floor::~Floor(){
	for(auto it = allGold.begin(); it!=allGold.end();++it){
		delete *it;}
	for(auto it = allPotions.begin(); it!=allPotions.end();++it){
		delete *it;}
	for(auto it = allNPC.begin();it!=allNPC.end();++it){
		delete *it;}
}


string Floor::displayFloor(){
	string output="";
	for(int i=0; i<NumRow; ++i){
		for(int j=0;j<NumCol;++j){
			output += FloorDisplay[i][j];
		}
		output +='\n';
	} 
	return output;
}

char Floor::getCellChar(int x, int y){ return FloorDisplay[x][y];}

void Floor::movePart(int oldX, int oldY, int newX, int newY, char symbol, char standingon){
	FloorDisplay[newX][newY] = symbol;
	FloorDisplay[oldX][oldY] = standingon;
}

NPC * Floor::getNPC(int x, int y){
	for(size_t i=0; i<allNPC.size(); ++i){
		if(allNPC[i]!=nullptr && allNPC[i]->getX() ==x &&allNPC[i]->getY() ==y){
			return allNPC[i];
		}
	}
	return nullptr;
}

void Floor::moveNPC(NPC *en){ en->move(thePC);}

bool Floor::PCnearby(NPC *en){
	char ch;
	char enem = en->getSym();
	if (en ->isAngry()){
		if(enem == 'D'){
			Gold *g = en->getDG();
			for(int i =-1; i<2;++i){
				for(int j=-1; j<2;++j){
					ch = getCellChar(g->getX() + i, g->getY() + j);
					if(ch == '@'){
						return true;
					}
				}
			}
		}
		int xNew = en->getX();
		int yNew = en->getY();
		for(int i =-1; i<2;++i){
			for(int j=-1; j<2;++j){
				ch = getCellChar(xNew + i, yNew + j);
				if(ch == '@'){
					return true;
				}
			}
		}
	}
	return false;
}

void Floor::allNPCTakeTurn(bool movable){//movable used to indicate if -f is on
	bool att = false;
	for(size_t i=0; i<allNPC.size(); ++i){
		if(allNPC[i]!=nullptr){
			att = PCnearby(allNPC[i]);
			if(att && allNPC[i]->isAngry()){
				allNPC[i]->attack(thePC);
			}else if(movable){
				moveNPC(allNPC[i]);
			}
			att = false;
		}
	}

}

bool Floor::checkAngry(){
	return angryMerchant;
}

void Floor::notifyAllMerchant(){
	for(size_t i=0; i<allNPC.size();++i){
		if(allNPC[i]!=nullptr && allNPC[i]->getSym()=='M'){
			allNPC[i]->makeAngry();
		}
	}
	angryMerchant = true;
}

void Floor::removeNPC(int x, int y){
	for(size_t i=0; i<allNPC.size(); ++i){
		if(allNPC[i]!=nullptr &&allNPC[i]->getX()==x && allNPC[i]->getY()==y){
			FloorDisplay[x][y]='.';
			char npc;
			npc = allNPC[i] -> getSym();
			if (npc == 'K') {FloorDisplay[x][y]=allNPC[i]->getCur();}
			delete allNPC[i];
			allNPC[i] = nullptr;
			break;
		}
	}
}

Potion * Floor::getPotion(int x, int y){
	for(size_t i=0; i<allPotions.size(); ++i){
		if(allPotions[i]!=nullptr && allPotions[i]->getX() ==x &&allPotions[i]->getY() ==y){
			allPotions[i]->setUsed();
			int thecode = allPotions[i]->getCode();
			notifyPotion(thecode);
			return allPotions[i];
		}
	}
	return nullptr;
}

void Floor::notifyPotion (int k) {
	for(size_t i=0; i<allPotions.size(); ++i){
                if(allPotions[i]!=nullptr && allPotions[i]->getCode() ==k){
                        allPotions[i]->setUsed();
                }
        }
	if (k==0) RHused = true;
        if (k==1) BAused = true;
        if (k==2) BDused = true;
        if (k==3) PHused = true;
        if (k==4) WAused = true;
        if (k==5) WDused = true;
}

bool Floor::checkUsed(int k){
        if (k==0) return RHused;
        if (k==1) return BAused;
        if (k==2) return BDused;
        if (k==3) return PHused;
        if (k==4) return WAused;
        if (k==5) return WDused;
	else return false;
}

void Floor::removePotion(int x, int y){
	for(size_t i=0; i<allPotions.size(); ++i){
		if(allPotions[i]!=nullptr &&allPotions[i]->getX()==x && allPotions[i]->getY()==y){
			FloorDisplay[x][y]='.';
			delete allPotions[i];
			allPotions.erase(allPotions.begin()+i);
			break;
		}
	}
}


int Floor::potionNear(int x, int y){
	int count = 0;
	for(int i =-1; i<2;++i){
		for(int j =-1; j<2;++j){
			if(FloorDisplay[x+i][y+j]=='P') {
				for(size_t k=0; k<allPotions.size(); ++k){
               				if(allPotions[k]!=nullptr &&allPotions[k]->getX()==x+i && allPotions[k]->getY()==y+j) {
						if (allPotions[k]->getUsed()) thePC->attachAction(allPotions[k]->message());
						else count+=1;
					}
				}
				
			}
		}
	}	
	return count;
}

bool Floor::checkGoldGetable(int x, int y){
	for(size_t i=0; i<allGold.size();++i){
		if(allGold[i] != nullptr && allGold[i]->getX() ==x && allGold[i]->getY() ==y){
			return allGold[i]->getPickable();
		}
	}
	return true;
}

int Floor::getGoldValue(int x, int y){
	int value=0;
	for(size_t i=0; i<allGold.size();++i){
		if(allGold[i] != nullptr && allGold[i]->getX() ==x && allGold[i]->getY() ==y){
			value= allGold[i]->getValue();
			delete allGold[i];
			allGold.erase(allGold.begin()+i);
		}
	}
	return value;
}


void Floor::dropHGold(int x,int y){//not show G after killed a Human
	int x2,y2;

	bool havespace = false;
	for (int i= -1; i<2;i++) {
		for (int j =-1; j<2;j++) {
		 	if ((!(i==0&&j==0))&&(FloorDisplay[x+i][y+j] == '.')) {
				havespace = true;
			}
		}
	}

	if (havespace == false) {            // if there is no space for the second gold, drop one of 4 instead
		dropMGold(x,y);
		return;
	}

	while(true){ //Select a cell except (x,y))
		x2=rand()%3-1;
		y2=rand()%3-1;
		if((!(x2 == 0 && y2 ==0))&& (FloorDisplay[x+x2][y+y2] == '.')){break;} 
	}
	int goldX2 = x+x2;
	int goldY2 = y+y2;
	Gold * newlyDropped = new Gold(x,y,this,2,true);
	Gold * newlyDropped2 = new Gold(goldX2,goldY2,this,2,true);
	allGold.emplace_back(newlyDropped);
	allGold.emplace_back(newlyDropped2);
	FloorDisplay[x][y]='G';
	FloorDisplay[goldX2][goldY2]='G';
}

void Floor::dropMGold(int x,int y){
	Gold * newlyDropped =new Gold(x,y, this, 4, true);
	allGold.emplace_back(newlyDropped);
	FloorDisplay[x][y]='G';
}



//--------------RANDOM GENERATE-------------------------------------------------------------------------------------

void Floor::attachCham() {
	int 	k =0; // 0~4 
	for(int i=0; i<NumRow; ++i){
		for(int j=0;j<NumCol; ++j){
		if ((FloorDisplay[i][j]=='.') && (caught[i][j])==false) {   // get a new base point '.''
			explore(i,j,k);  // k is the chamber number
			k +=1;
			}
		}
	}
}

void Floor::explore(int i, int j, int k){
	if (i<0 ||i>=NumRow|| j<0||j>=NumCol) {return;}  //end when explored the whole space
	else {
		caught[i][j] = true;                              // get you
		allChamber[k].emplace_back(make_pair(i,j));       // put myself in
		if ((FloorDisplay[i-1][j]=='.')&&(caught[i-1][j] == false)) explore(i-1,j,k); // up
		if ((FloorDisplay[i][j+1]=='.')&&(caught[i][j+1] == false)) explore(i,j+1,k); // right
		if ((FloorDisplay[i+1][j]=='.')&&(caught[i+1][j] == false)) explore(i+1,j,k); // down
		if ((FloorDisplay[i][j-1]=='.')&&(caught[i][j-1] == false)) explore(i,j-1,k); // left
	}
}

pair<int,int> Floor::getmelocation (int k) {
    int j = rand() % allChamber[k].size();
    pair<int,int> location = allChamber[k][j];
    allChamber[k].erase(allChamber[k].begin()+j);
    return location;
}

void Floor::iamthere (int i,int j,int k) {
    for (auto it=allChamber[k].begin(); it!=allChamber[k].end(); ){
        if ((it->first == i) && (it->second ==j))
             allChamber[k].erase(it);
	else ++it;                               // new lession learnd!!!
	}
}

// place PC then Stairway and make sure that they will not be in the same chamber
void Floor::placePCandStairway () {
	int pcCham = rand() %5;
	int stairCham = rand() %5;
	while (stairCham == pcCham) {stairCham = rand() %5;} // cannot be in the same Chamber
        
	// PC
	pair<int,int> pcloc = getmelocation(pcCham);
        int pcX = pcloc.first;
	int pcY = pcloc.second;
	thePC->setCoords(pcX,pcY);
        FloorDisplay[pcX][pcY]='@';

	// Stair
	pair<int,int> stairloc = getmelocation(stairCham);
        int stairX = stairloc.first;
        int stairY = stairloc.second;
        FloorDisplay[stairX][stairY]='\\';
}

void Floor::placePotion(){
	for(int i=0;i<NumPotion;++i){
		int num = rand()%5;
		int code = rand()%6;
		pair<int,int> ploc = getmelocation(num);
		int x = ploc.first;
		int y = ploc.second;
		FloorDisplay[x][y]='P';
		if(code==0){//RH
			Potion * newPotionPtr = new Potion(x,y,this,0,"RH",RHused);
			allPotions.emplace_back(newPotionPtr);
		}else if(code ==1){//BA
			Potion * newPotionPtr = new Potion(x,y,this,1,"BA",BAused);
			allPotions.emplace_back(newPotionPtr);
		}else if(code ==2){//BD
			Potion * newPotionPtr = new Potion(x,y,this,2,"BD",BDused);
			allPotions.emplace_back(newPotionPtr);
		}else if(code ==3){//PH
			Potion * newPotionPtr = new Potion(x,y,this,3,"PH",PHused);
			allPotions.emplace_back(newPotionPtr);
		}else if(code ==4){//WA
			Potion * newPotionPtr = new Potion(x,y,this,4,"WA",WAused);
			allPotions.emplace_back(newPotionPtr);
		}else if(code ==5){//WD
			Potion * newPotionPtr = new Potion(x,y,this,5,"WD",WDused);
			allPotions.emplace_back(newPotionPtr);
		}
	}
}

void Floor::placeGold(){
	for(int i=0;i<NumGold;++i){
		int num = rand()%5;
		int code = rand()%8;
		pair<int,int> goldloc = getmelocation(num);
		int x = goldloc.first;
		int y = goldloc.second;
		FloorDisplay[x][y]='G';
		if(code<=1){// small hoard
			allGold.emplace_back(new Gold(x,y,this,1,true));
		}else if(code <=6){//noraml hoard
			allGold.emplace_back(new Gold(x,y,this,2,true));
		}else{//dragon hoard
			allGold.emplace_back(new Gold(x,y,this,6, false));
			int dragonX,dragonY;
			while (1) {
                                dragonX = x+(rand()%3)-1;
                                dragonY = y+(rand()%3)-1;
                                if (FloorDisplay[dragonX][dragonY]=='.') break;
                        }
			iamthere(dragonX,dragonY,num);
			FloorDisplay[dragonX][dragonY]='D';
			allNPC.emplace_back( new Dragon(dragonX, dragonY, this, allGold.back()));
		}
	}
}

void Floor::placeNPC(){
	for(int i=0;i<NumNPC;++i){
		int num = rand()%5;
		int code = rand()%19;
		pair <int,int> npcloc = getmelocation(num);
		int x = npcloc.first;
		int y = npcloc.second;
		if(code<4){
			FloorDisplay[x][y]='H';
			allNPC.emplace_back( new Human(x,y,this));
		}else if(code<7){
			FloorDisplay[x][y]='W';
			allNPC.emplace_back(new Dwarf(x,y,this));
		}else if(code<12){
			FloorDisplay[x][y]='L';
			allNPC.emplace_back(new Halfling(x,y,this));
		}else if(code<14){
			FloorDisplay[x][y]='E';
			allNPC.emplace_back(new Elf(x,y,this));
		}else if(code<16){
			FloorDisplay[x][y]='O';
			allNPC.emplace_back(new Orcs(x,y,this));
		}else if (code<18){
			FloorDisplay[x][y]='M';
			allNPC.emplace_back(new Merchant(x,y,this));
		} else {FloorDisplay[x][y]='K';
			allNPC.emplace_back(new Tracker(x,y,this));}
	}
}

