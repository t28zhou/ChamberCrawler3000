#include "Shade.h"

Shade::Shade():PC{125}{
	hp = 125;
	atk = 25;
	def = 25;
	race = "Shade";
}

Shade::~Shade(){}

void Shade::resetStats(){
	atk = 25;
	def = 25;
}

