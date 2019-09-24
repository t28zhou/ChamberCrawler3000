#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>
#include <string>

class Gold;
class NPC;
class Potion;
class PC;

class Floor {
    std::vector<Potion*> allPotions;
    std::vector<Gold*> allGold;
    std::vector<NPC*> allNPC;
    PC * thePC;
    bool angryMerchant; 
    bool RHused;
    bool BAused;
    bool BDused;
    bool PHused;
    bool WAused;
    bool WDused; 
    // grab everything in one chamber
    void attachCham();
    void explore(int,int,int);
    // random generate
    void placePCandStairway();
    void placePotion();
    void placeGold();
    void placeNPC();
    std::pair<int,int> getmelocation (int); // give me a coordinate inside chamber k
    void iamthere(int,int,int);             // the dragon is there, (i,j) is not availible in chamber k anymore
    // NPC's turn
    void moveNPC(NPC *);
    bool PCnearby(NPC *);
  
  public: 
    Floor(PC *,std::string,int, bool);
    ~Floor();
    
    // Floor related
    std::string displayFloor();
    char getCellChar(int, int);
    void movePart(int,int,int,int,char,char);
    // Potion related
    int potionNear(int,int);                //check the surrounding 8 cells. if there is a potion return ture, oth, false.
    Potion * getPotion(int , int );
    void removePotion(int , int );
    bool checkUsed(int);
    void notifyPotion(int);
    // Gold related
    bool checkGoldGetable(int , int );       //check if we can pick Gold in Cell (x,y)
    int getGoldValue(int , int );            //get the value of the gold in the Cell (x,y), then remove this Gold
    void dropHGold(int ,int );               //drops 2 piles of gold worth 2 each, in the adjacent squares. when a human is killed.
    void dropMGold(int ,int );               //drops 1 pile of gold worth 4 in the adjacent squares. When a merchant is killed
    // NPC related
    NPC * getNPC(int, int);
    void allNPCTakeTurn(bool);               // All NPC has a chance to attack or move
    bool checkAngry();                       // check if the merchants are angry
    void notifyAllMerchant();                // tell everyone to be angry
    void removeNPC(int, int);                //slay the Enemy in the current cell
};


#endif
