#ifndef _GAMECONTROL_H_
#define _GAMECONTROL_H_
#include <string>

class PC;
class Floor;

class GameControl {
   std::string filename;
   int beginrow;
   bool thereisafile;
   PC *player;
   Floor *floor;
   bool NPCcanMove = true;               //flag for FREEZE
   void instructions();  
   void gameDisplay();
   void colorPC();

  public:
   std :: string transf(int);
   GameControl();
   ~GameControl();
   void movePC(std::string);
   bool initGame (bool,std::string);         // return false if quit before start
   void changeNPCmoveable();
   void attackNPC (std::string);
   bool gameOver();
   void PCusePotion (std::string);
};

#endif
