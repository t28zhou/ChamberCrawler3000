#include <string>
#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "gamecontrol.h"
using namespace std;

int main  (int argc, char *argv[]) {
  initscr();
  keypad (stdscr, true);
  
  start_color();

  string filename = "empty_floor.txt"; // default empty plan
  bool argfile = false;
 
  noecho(); 

  if (argc > 1) {
     argfile = true;
     string inputfile(argv[1]);        // convert the char* to string
     filename = inputfile;
  }

  string previousdirection="no";       // store previous action
  string previouscommand="f";          // random assignment, in case any wierd input
  string command;
  string direction;
  bool set = false;
  string trans;
 
 	
  
  srand (time(nullptr));
  GameControl *game = new GameControl ();
  if (game->initGame(argfile, filename)) {// exit the game before start  
     while (1) {
       
        command = game->transf(getch());
        
        if (command == "q") {break;}
       
	if (command == "No"){ 
            printw ( "Well, try again. \n");              // looking for valid input
            continue;
        }
        
        if (command == "p") {                              // repeat last action, too hard to test
            command = previouscommand;
            direction = previousdirection;
            set = true;
        }

        if (command == "r") {
            previouscommand = command;
            delete game;
            game = new GameControl();
            if (!game->initGame(argfile, filename)) break; // exit the game
        } 

	else if (game -> gameOver() == false) {          // check whether GAMEOVER
            if (command == "a") {                          // attack
               previouscommand = command;
               if (!set) { 
                  direction = game->transf(getch());
                  previousdirection = direction;
               }
               game -> attackNPC(direction);
            } else if (command == "f") {                   // freeze or unfreeze the NPCs
               previouscommand = command;
               game -> changeNPCmoveable ();
            } else if (command == "u") {                   // use potion
               previouscommand = command;
               if (!set) {
                  direction =  game->transf(getch());
                  previousdirection = direction;
               }
               game -> PCusePotion(direction);              
            } else {                                       // move
	       previouscommand = command;
               game->movePC(command); 
            }
         }
       set = false;
     }
  }

  delete game;
  init_pair(7, COLOR_BLUE,COLOR_BLACK);
  attron(COLOR_PAIR(7));
  printw( "\nYOU ARE NOW IN THE REAL WORLD, WHERE DEADLINES, EXAMS, AND TRYING TO PASS EXIST. GOOD LUCK. \n");
  refresh();
  getch();  
  endwin(); 
  return 0;
}
