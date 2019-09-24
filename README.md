# CS246——Final Project Documentation (Fall 2016)

## 1.0 Introduction
This documentation is for our final group project “ChamberCrawler3000”(CC3k). We are a team of three: Tianyuan Zhou (t28zhou, 20555729), Siqi Zhao (sqzhao, 20453720), and Frank Wang (t266wang, 20611396). We have implemented the rogue-like video game CC3k with the required core functionalities, as well as additional features. We employed the observer pattern for some of the classes and functions. 

## 2.0 Overview
The overall structure for our CC3k is like a chess game. We consider every object in the game (i.e. PC, NPC, gold, potion) as a chess piece placed on the chessboard (floor). 
•	So we have two very basic classes: Part and Floor. 
•	All “chess pieces” are inherited from the Part class, thus we have a Character, a Potion, and a Gold class as the subclasses of Part. 
•	Then we divided the Character into PC (player) and NPC (enemies). 
•	The different races for player and enemies are subclasses inherited from PC and NPC.

When we start a new game, we would either read in a file as the floor plan or use the default empty floor map. When there is no command line argument passed in, the game will randomly spawn Potions, Gold, and NPCs on Floor during then initialization step. The game will delete the entire Floor and everything on it (except PC), when the PC reaches the stairway and then generate a new one.

Whenever the PC proposes an action (i.e. move/use potion/attack), it will notify the Floor and the Floor will react accordingly (return required pointer, or modify display). As for the NPC’s turn, the floor will notify every NPC to attack PC if they can, or move otherwise. 

The GameControl is like a wrapper for all the functionalities. It will simplify the main function, so that the main can call only one game control function at a time to execute the command accordingly. 

## 3.0 Design
### 3.1 Main
Our main function is pretty simple. It will create a new game when start (or restart), and execute command by calling one GameControl function. We realize that there will be lots of repeated command passed in when playing the game (i.e. PC wants to move from the very left all the way down to the very right side of the Floor; or PC wants to kill a Dragon with multiple attacks), so we add in one more command as “p” to repeat previous action. This will simplify the command input. This enhance is implemented in main.

### 3.2 GameControl
Our GameControl class has a PC pointer and a Floor pointer. It will also print all “welcome messages” when a game is initialized. The GameControl will initialize the PC with a specific race that the player chooses, and initialize the Floor whether a floor map is passed in or not. 
•	It also converts all input directions to relative coordinates (i.e. ”no” for north will be converted to (-1,0); “se” for southwest will be (1, -1)), to be passed into PC’s functions. 
•	If the player wants to move/use potion/ attack, it will call PC’s move/use potion/ attack function.
•	If the player wants to freeze all NPCs, the movable flag will be toggled. 
•	It will also check that whether the game is over and print messages accordingly. (“Congratulations” for reaching floor 6, or “Game Over” for being killed)

### 3.3 Floor
Our Floor class is a very important part of the program. It keeps track of everything (Potion, Gold, and NPC) in the game. The initialization of Floor depends on whether a pre-set map is passed in as command argument or not. 
•	If there is a passed-in map, the Floor will assign a pointer to each Potion, Gold or NPC. 
•	The Floor will first identify all five chambers by grabbing all the available cells’ (‘.’) coordinates into a vector (Chamber [0~4]). 
•	If no designed map passed in, the Floor will randomly spawn Potion, Gold, and NPC based on the empty default floor plan. 

The Floor is responsible for the text display. It has a 2-D character board to record and modify. This is also an identifier for everything on the Floor. (I.e. if the floor display for cell (x, y) is “D”, there is a dragon at cell (x, y)). Detail information about observer-like design pattern between Floor and PC will be discussed in the PC part later. As for the NPCs’ turn, the Floor will ask each NPC to attack the PC if PC is within range, or move randomly otherwise.

### 3.4 Part
Part is the superclass for all game objects. It records the x and y coordinates and the symbol of the object. 

#### 3.4.1 Potion
Potion is a subclass of Part; the additional fields are the code and the name of the potion to specify it. One more flag is added to Potion, and will be turned on if the potion has been used. The six different effects are subclasses of Potion. When an unknown potion is used, it will notify the floor and the floor will notify all Potion of its kind. In order to remove the effect of temporary potions, we will reset the PC’s ATK and DEF when move to the new floor.

#### 3.4.2 Gold
Gold is a subclass of Part; the additional fields are the gold value and a gettable flag for Dragon Hoard. Only when the Dragon is killed, the flag will be set as true, and the Gold can be picked up.

#### 3.4.3 Character
Character is a subclass of Part. Additional fields are: HP, ATK, DEF, RACE, a flag to check whether it is alive, and the symbol of current cell. It is the superclass for both PC and NPC.

#### 3.4.3.1 PC
PC is our player class. It adds: MAX HP, gold, and an action string. (The max HP for vampire is set to be -1, so that it is different from others.) The action string contains all events that happened during this turn, and will be printed to the player.
•	Whenever the PC wants to move, it will notify the Floor, and the Floor will modify the display accordingly
•	Whenever the PC wants to use a Potion, it will notify the Floor, and the Floor will return a Potion pointer, and then erase this Potion from the “all Potions” vector. 
•	Whenever the PC wants to grab a Gold, it will notify the Floor, and the Floor will return the Gold value and remove the Gold if it is not a Dragon Hoard. 
•	Whenever the PC wants to attack a NPC, it will notify the Floor, and the Floor will return a NPC pointer. Then the be-attacked function for that NPC will be called.
o	If PC kills the NPC, the Floor will remove the NPC. 
o	If the PC kills a Human, the PC will notify the Floor to drop two piles of Gold;
o	If the PC kills a Merchant, the PC will notify the Floor to drop one pile of Gold, and set the “Merchants are angry” flag on. When the flag is on, the Floor will notify all Merchants to be angry (hostile to PC); 
o	If the PC kills a Dragon, the Dragon will notify its Dragon Hoard to be gettable.
 
All different races are subclasses inherited from PC. They may override the move/ use potion/ attack/ be-attacked functions accordingly. 

#### 3.4.3.2 NPC
NPC is our enemy class. It has less functionalities comparing to PC. It has two choices when it is the NPC’s turn:
•	If the NPC can attack the PC, it will attack, and the be-Attacked function for PC will be called.
•	Otherwise the NPC will move randomly to an available cell.

All different races are subclasses inherited from NPC. They may override the move/ attack/ be-Attacked functions accordingly. 

## 4.0 Resilience to Change
Our design makes it very easy to add new races for PC and NPC. We only need to override one or two functions according to new special abilities. So we added a new PC – God, which will not be attacked and can kill the enemy with one shot; and a new NPC –Tracker, which will tracks you, even into the passages. We can also add more functionality like buying and selling gears by adding the function to PC.
•	If there is any command change in the game, we just need to change our main and/or the GameControl class accordingly.
•	If the probability for spawning different game objects changes, we just need to change the range for random numbers in Floor constructor. (I.e. change rand ()%18 to rand ()%19 when we want to add a little probability to spawn the Tracker.)
•	If new functionality (i.e. buy, sell, etc.) added, we just need to add functions in PC accordingly.
•	We can change the “difficulty” by increase the probability of spawning stronger NPCs at the initialization step.

As for cohesion and coupling, each class is pretty high cohesion within itself. Since we give each different kind of game object a separate class, and let them do thing that relates only to itself. PC, NPC, Potion, and Gold have very low coupling in between, changing in one of them won’t affect others in general. 

One thing that can be improved is the Floor. Since we need the game objects to interact with the each other, we use the Floor as a general observer and a bridge to connect them. We could have made some middle classes to separate them (like Cell), if we had more time.

## 5.0 Answers to Questions
### Question 2.1: 
We define an abstract class with HP, HP max, Attack, Defense, and Be-Attacked methods. Each of the races is concrete class of the abstract class, the concrete classes would inherit the fields of the HP, HP max, ATK, and DEF, and initialize them to proper values within their constructors. Each concrete class would have a special method of their own special abilities (override). When you add addition races, you just have to implement the constructor of the class to initialize each to proper/desired values, and you have to implement the special ability method if there is one.

### Question 2.2a:
We could generate the enemies based on which character you choose, i.e. if you choose Vampire, then more dwarves will have a higher chance of being generated in higher levels. The number of enemies per chamber is limited depending on the space within that room. Generating enemies is different from generating characters, since the generation of each type of enemy is based on a probably, and the player is based on the choice of the user.

### Question 2.2b: 
Yes, an abstract class will be implemented for the enemies, and each derived class will contain the special abilities, and will initialize each type of enemy's attributes to proper values.

### Question 2.3: 
We could implement the Decorator, since each potion is temporary and is a one-time effect. Decorator Pattern allows us to add additional functionality to the existing one at runtime. The advantage of Decorator Pattern is that it is real-time so during gameplay the player's attributes will be updated based on which potion is consumed. The disadvantage is that you can’t keep track which decorator has already been applied, so it might be hard to reverse the effects of a potion, if temporary, on the next floor.

Whereas, the Strategy Pattern allows us to change the implementation used at runtime. The advantage of using it is, unlike the Decorator Pattern, PC realizes the function it uses to update its stat. The disadvantage is, since the effects of the potion are pretty simple, there is no need to separate the implementation for consuming different types of potions.

### Question 2.3.2: 
Potion and Gold should be derived from the same abstract class, since a treasure is randomly spawned same as the potions, except its effects are permanent, and each gold will have special attributes, i.e. the dragon hoard. For the special ability it will be a separate field/method in each of the derived classes.

## 6.0 Extra Credit Features
### 6.1 new PC – God
We created a new class for PC – God. This is a very strong player race, since it cannot be attacked and can kill the enemy with one shot. This is also very useful for testing. It has been recognized that the game can be too hard to play sometimes. (I.e. too many enemies in a small chamber and blocks your way out.) This new PC ensures you to reach the 6th floor (win), so that everything can be easily tested.

### 6.2 new NPC – Tracker
We created a new class for NPC – Tracker. This is a very dangerous enemy, so we give it a low probability for it to be spawned (1/19). The Tracker has a high HP, high ATK, and low DEF. It can track you down if you are in 10-block radius. It can follow the PC into the PASSAGES. They may even block the passage and kill the PC easily.
## 7.0 Final Questions
### 7.1 Developing Software in Teams
This project teaches me a lot about developing software in teams. It is very important to start early and divide the work to individual team members. The design is important, since related classes have to be done by a single person. 

We separate our responsibilities after several meetings, and it works fine. A little problem is that when a team member cannot figure out the bug in his/her code, others have to learn everything about his/her code then provide advice.

Good thing about working in team is that you can discuss your ideas and questions with others. Working together is much more efficient than doing everything alone. We can also come up with creative ideas when talking to each other.

### 7.2 If We Can Start Over…
If we can start over, we may want to improve our design, and add in more design patterns. Also we changed everything to vectors at the end, after we finish the project. This could have been done at the very beginning. (Starting by using vectors) We also tried to convert everything into smart pointers. But we don’t have enough time to solve the memory leak problem.
### 8.0 Conclusion
Overall, we think our group project -- CC3k is successful. We implemented required core functionalities and added bonus features. The code is clear to read and understand. Though there were some difficulties during the project, working in a team increases our efficiency and creativity. We have learned and practiced a lot from this project, especially the use of vector and smart pointers. We are pretty satisfied with the project, and aiming for higher standard in the future.

