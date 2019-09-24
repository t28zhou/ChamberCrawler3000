#include "gamecontrol.h"
#include <iostream>
using namespace std;
#include <sstream>

#include <ncurses.h>
#include <string>
#include "Shade.h"
#include "Goblin.h"
#include "Troll.h"
#include "Vampire.h"
#include "Drow.h"
#include "God.h"
#include "Phoenix.h"
#include "PC.h"
#include "Floor.h"

bool merchantIsAngry = false;
bool gRHused = false;
bool gBAused = false;
bool gBDused = false;
bool gPHused = false;
bool gWAused = false;
bool gWDused = false;

GameControl::GameControl () {
  beginrow = 0;
  player = nullptr;
  floor = nullptr;
}

GameControl::~GameControl () {
  if (player != nullptr) delete player;
  if (floor != nullptr) delete floor;
  player = nullptr;
  floor = nullptr;
}

string GameControl::transf (int ch) {
  	keypad(stdscr,true);
	if (ch == KEY_LEFT)  return "we";
	if (ch == KEY_RIGHT) return "ea";
	if (ch == KEY_UP)    return "no";
	if (ch == KEY_DOWN)  return "so";

	if (ch == 's') return "nw";
	if (ch == 'd') return "ne";
	if (ch == 'x') return "sw";
	if (ch == 'c') return "se";


	if (ch == 'q') return "q";
	if (ch == 'a') return "a";
	if (ch == 'u') return "u";
	if (ch == 'r') return "r";
	if (ch == 'p') return "p";
	if (ch == 'f') return "f";
	else return "No";
}


void GameControl::instructions () { 
  // display valid commands
  init_pair(4, COLOR_RED,COLOR_BLACK);
  attron(COLOR_PAIR(4));

  printw( "Here are valid commands: \n");
  printw( "no, so,  ea,   we, ne, nw, se, sw \n");//: moves the player one block in the appropriate cardinal direction. \n");
  printw( "up,down,right,left, d,  s,  c,  x: moves the player one block in the appropriate cardinal direction. \n");
  printw( "u <direction>: uses the potion indicated by the direction. \n");
  printw( "a <direction>: attacks the enemy in the specified direction  \n");
  printw( "f: stops enemies from moving until this key is pressed again. \n");
  printw( "p: repeat previous action. {we add this to simplify the test}. \n");
  printw( "r: restarts the game. All stats, inventory, and gold are reset. \n");
  printw( "q: quits the game. \n\n");
}

void GameControl::gameDisplay() {
  clear();
  instructions();

  attron(COLOR_PAIR(5));
  colorPC();

//  init_pair(6, COLOR_YELLOW,COLOR_BLACK);
  attron(COLOR_PAIR(6));
  printw(player -> displayState().c_str());
  refresh();
}

void GameControl::colorPC () {
  attroff(COLOR_PAIR(5));
  init_pair(7,COLOR_BLUE,COLOR_BLACK);
  std::string original = floor ->displayFloor();
  for (int i=0;i<original.size();++i) {
	if (original[i]=='\n') {printw("\n"); continue;}
	if (original[i]==' ') {printw(" "); continue;}
	stringstream ss;
	string s;
	ss << original[i];
	ss >> s;
	if (original[i]=='P') {
 		attron(COLOR_PAIR(3));
		printw(s.c_str());
		attroff(COLOR_PAIR(3));
	} else if (original[i]=='G') {
                attron(COLOR_PAIR(6));
                printw(s.c_str());
                attroff(COLOR_PAIR(6));
	} else if (original[i]=='@') {
                attron(COLOR_PAIR(2));
                printw(s.c_str());
                attroff(COLOR_PAIR(2));
        } else if (original[i]=='\\') {
                attron(COLOR_PAIR(4));
                printw(s.c_str());
                attroff(COLOR_PAIR(4));
        } else if (original[i]=='K') {
                attron(COLOR_PAIR(7));
                printw(s.c_str());
                attroff(COLOR_PAIR(7));
        } else if (original[i] == 'D' ||original[i] == 'H' ||original[i] == 'M' ||original[i] == 'O'
		 ||original[i] == 'E' ||original[i] == 'L' || original[i] == 'W'){
		attron(COLOR_PAIR(5));
 		printw(s.c_str());
		attroff(COLOR_PAIR(5));
	} else {
        //        attron(COLOR_PAIR(5));
                printw(s.c_str());
          //      attroff(COLOR_PAIR(5));
        }
}
}



// for cmd move in the direction
void GameControl::movePC (string direction) {
  // clear the action string for PC
  player -> clearAction();
  player -> attachAction ("Player moves towards ");

  bool reached = false; // return true if the player reaches the stair
  if (direction == "no") {
    player -> attachAction("North.");
    reached = player-> move(-1, 0);
  } else if(direction == "ne") {
    player -> attachAction("Northeast.");
    reached = player->move(-1, 1);
  } else if (direction == "ea") {
    player -> attachAction("East.");
    reached = player->move(0, 1);
  } else if (direction == "se") {
    player -> attachAction("Southeast.");
    reached = player->move(1 ,1);
  } else if (direction == "so") {
    player -> attachAction("South.");
    reached = player->move(1, 0);
  } else if (direction == "sw") {
    player -> attachAction("Southwest.");
    reached = player->move(1 ,-1);
  } else if (direction == "we") {
    player -> attachAction("West.");
    reached = player->move(0, -1);
  } else if (direction == "nw") {
    player -> attachAction("Northwest.");
    reached = player->move(-1 ,-1);
  } else player ->attachAction("invalid direction.");                 // bad direction

  if (reached) {     // new floor
    if (thereisafile) beginrow +=25;
    delete floor;
    floor = new Floor (player, filename, beginrow, thereisafile);

    player -> resetStats();
    if (merchantIsAngry) floor -> notifyAllMerchant();
    if (gRHused) floor->notifyPotion(0);
    if (gBAused) floor->notifyPotion(1);
    if (gBDused) floor->notifyPotion(2);
    if (gPHused) floor->notifyPotion(3);
    if (gWAused) floor->notifyPotion(4);
    if (gWDused) floor->notifyPotion(5);
  } 
  else
    floor -> allNPCTakeTurn(NPCcanMove);

  if (!gameOver()) gameDisplay();
}





// generate a new game
// return false if the player terminate the game at the very beginning 
bool GameControl::initGame (bool thereisafile,  string filename) {
  merchantIsAngry = false;
  gRHused = false;
  gBAused = false;
  gBDused = false;
  gPHused = false;
  gWAused = false;
  gWDused = false;

  initscr();
  clear();
  
  start_color();

  init_pair(1, COLOR_WHITE,COLOR_BLACK);
  attron(COLOR_PAIR(1));
  printw( "2000 years ago, our ancestors dreamed of going into the \n");
  printw( "Chamber of Secrets to gather what they called, the Gold of Revival. \n");
  printw( "The Gold of Revival can immediately heal any sick or injured personnel without any side effects. \n");
  printw( "They said the Chamber of Secrets is full of monsters never seen by anyone, because no one ever survived to tell the tale. \n");
  printw( "\nI am Archilles, I am the chief of the guards in my holy city, Cannan. \n");
  printw( "Although behind the great walls of Cannan, we are safe, but the Dark army of the West are marching towards us, \n");
  printw( "they sent ahead a deadly virus to soften the battlefield, many of our best soldiers have already got infected. \n");
  printw( "I must march into the Chamber of Secrets to obtain the Gold of Revival to help my city. \n\n");//<<endl;

  printw( "This game is modified with DLC.\n");
  printw( "The DLC contains two powerful races, God and Phonenix, and the deadliest Tracker that will track you down and kill you. \n");
  
  init_pair(2, COLOR_MAGENTA,COLOR_BLACK);
  attron(COLOR_PAIR(2));
  
  printw( "-----------------------------------------------Your journey begins------------------------------------------------- \n");
  printw( "Welcome to the Chamber of Secrets\n");
  printw( "By the magical power of the Chamber, you are to be transformed into one of the following race\n");
  printw( "Please choose your desired transformation\n\n");
  printw( "(s)hade   : HP: 125,  Atk: 25,  Def: 25,     Special Ability: 50\%% more final score.\n");
  printw( "(d)row    : HP: 150,  Atk: 25,  Def: 15,     Special Ability: 50\%% more potion effect.\n");
  printw( "(v)ampire : HP:  50,  Atk: 25,  Def: 25,     Special Ability: 5 HP gained on successful attack.\n");
  printw( "(t)roll   : HP: 120,  Atk: 25,  Def: 15,     Special Ability: 5 HP gained every turn.\n");
  printw( "(g)oblin  : HP: 110,  Atk: 15,  Def: 20,     Special Ability: 5 gold stolen every kill.\n");
  printw( "(o)God    : HP: 1000, Atk: 500, Def: 100000, Special Ability: You cannot be damaged.\n");
  printw( "(x)Phoenix: HP: 120,  Atk: 25,  Def: 30,     Special Ability: Respawn after death one time, attacks twice.\n");
  printw( "OR (q) to exit the game.\n\n");
  refresh();
 
  // get the race for PC
  char race;
  race = getch();

  
  init_pair(3, COLOR_GREEN,COLOR_BLACK);
  attron(COLOR_PAIR(3));

  if (race == 'q') return false;       // quit the game before start

  switch (race) {
   case 'd': {
     printw("You are a drow, an ancient species found at the edge of the world.\n");
     player = new Drow();
     break;
   }
   case 'v': {
     printw("You are a vampire, the chamber is your home, you rule the darkness.\n");
     player = new Vampire();
     break;
   }
   case 't': {
     printw("You are a troll, the funniest of all monsters, and the biggest too.\n");
     player = new Troll();
     break;
   }
   case 'g': {
     printw("You are a goblin, the greediest race of all, perhaps greed can save the city.\n");
     player = new Goblin();
     break;
   }
   case 'o': {
     printw("You are the all powerful God Almighty, Your salvation shall save the city of Cannan.\n");
     player = new God();
     break;
   }
   case 'x': {
     printw("You are the last of your race, you shall bring peace to the land of Cannan.\n");
     player = new Phoenix();
     break;
   }
   default: {
     printw("You are a shade, you have chosen the most honorable race.\n");
     player = new Shade();
     break;
   }
  }
  printw("\n");
  refresh ();
  
  printw ("Press any key to start.\n");
  getch();  // useless;  
  clear();

  // initialize the game
  this -> filename = filename;
  this -> thereisafile = thereisafile;
  floor = new Floor (player, filename, beginrow, thereisafile);
  player -> attachAction ("PC has been spawned successfully. Let's start the journey!");

  instructions();
  refresh();

  // now let's start
  init_pair(5, COLOR_CYAN,COLOR_BLACK);
  attron(COLOR_PAIR(5));
  colorPC();


  init_pair(6, COLOR_YELLOW,COLOR_BLACK);
  attron(COLOR_PAIR(6));
  printw(player -> displayState().c_str());
  refresh();

  return true;
}


// for cmd freeze the NPCs' move
void GameControl::changeNPCmoveable() {
 // clear();
  NPCcanMove = !NPCcanMove;
  player -> clearAction ();
  if (NPCcanMove) player -> attachAction("Now NPCs can move again!");
  else player -> attachAction ("Everybody Freeze!");

  floor -> allNPCTakeTurn(NPCcanMove);

  gameDisplay();
}

// for cmd attack in the direction
void GameControl::attackNPC (string direction) {
 // clear();
  if (direction == "no") player-> Attack (-1, 0);
  else if (direction == "ne") player-> Attack (-1, 1);
  else if (direction == "ea") player-> Attack (0, 1);
  else if (direction == "se") player-> Attack (1 ,1);
  else if (direction == "so") player-> Attack (1, 0);
  else if (direction == "sw") player-> Attack (1 ,-1);
  else if (direction == "we") player-> Attack (0, -1);
  else if (direction == "nw") player-> Attack (-1 ,-1);
  else {
    printw("Please choose a valid direction to attack. \n");
    refresh();
    return;         // pretend that nothing happened
  }

  if (floor -> checkAngry()) {
     if (merchantIsAngry == false) {
        player -> attachAction (" Merchants Are Angry Now. WATCH OUT!!");
     merchantIsAngry = true;}
  } // set up the flag for the first time that a merchat is killed

  floor -> allNPCTakeTurn(NPCcanMove);

  if (!gameOver()) gameDisplay();
}





// check whether the player is dead and print the final score if GAMEOVER
bool GameControl::gameOver () {
  if (player -> checkDead()) {
      clear();
      attron(COLOR_PAIR(4));
      printw("GAMEOVER!!!\n"); 
      printw("Your city is destoryed by the Dark army. \n");
      printw("Let's have a final look at the the game. \n");    
      colorPC();
      attron(COLOR_PAIR(6));
      printw(player -> displayState().c_str());
      attron(COLOR_PAIR(4));
      printw( "\nDo you want to (r)epaly or (q)uit? \n");
      refresh(); 
     return true;
  } else if (player->getfloorNum() > 5) {
      clear();
      attron(COLOR_PAIR(3));
      printw("CONGRATULATIONS!!!\n");
      printw("You have been transformed back to Archilles, you have saved your city.\n");
      printw("\nYour final score is: ");
      int score = player -> getGold();
      int shadscore = score*1.5;
      attron(COLOR_PAIR(2));
      if (player ->getRace() == "Shade") printw(to_string(shadscore).c_str());
      else printw(to_string(score).c_str());
      attroff(COLOR_PAIR(2));
      attron(COLOR_PAIR(5));
      printw("\n\nDo you want to (r)estart a new game or (q)uit? \n");
      refresh();
      return true;
  }
  return false;
}

// for cmd use potion in the direction
void GameControl::PCusePotion (string direction) {
 // clear();
  if (direction == "no") player-> usePotion (-1, 0);
  else if (direction == "ne") player-> usePotion (-1, 1);
  else if (direction == "ea") player-> usePotion (0, 1);
  else if (direction == "se") player-> usePotion (1 ,1);
  else if (direction == "so") player-> usePotion (1, 0);
  else if (direction == "sw") player-> usePotion (1 ,-1);
  else if (direction == "we") player-> usePotion (0, -1);
  else if (direction == "nw") player-> usePotion (-1 ,-1);
  else {
    printw("Please choose a valid direction to use the potion. \n");
	refresh();
    return;         // pretend that nothing happened
  }

  if (floor -> checkUsed(0)) {
     if (gRHused == false) {
        player -> attachAction (" Now you can identify RH.");
     gRHused = true;}
  }
  
  if (floor -> checkUsed(1)) {
     if (gBAused == false) {
        player -> attachAction (" Now you can identify BA.");
     gBAused = true;}
  }

  if (floor -> checkUsed(2)) {
     if (gBDused == false) {
        player -> attachAction (" Now you can identify BD.");
     gBDused = true;}
  }

  if (floor -> checkUsed(3)) {
     if (gPHused == false) {
        player -> attachAction (" Now you can identify PH.");
     gPHused = true;}
  }

  if (floor -> checkUsed(4)) {
     if (gWAused == false) {
        player -> attachAction (" Now you can identify WA.");
     gWAused = true;}
  }

  if (floor -> checkUsed(5)) {
     if (gWDused == false) {
        player -> attachAction (" Now you can identify WD.");
     gWDused = true;}
  }

  floor -> allNPCTakeTurn(NPCcanMove);
  gameDisplay();
}
