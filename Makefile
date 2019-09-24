CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = main.o gamecontrol.o Phoenix.o Tracker.o Floor.o Part.o character.o NPC.o gold.o Potion.o Human.o Dwarf.o Elf.o Orcs.o Merchant.o Dragon.o Halfling.o PC.o Drow.o Shade.o Troll.o Vampire.o Goblin.o God.o
DEPENDS = ${OBJECTS.o:= .d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -lncurses ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
