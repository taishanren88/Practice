#pragma once

#include "Move.h"
#include <string>
class Player {
public:
	Player(int icolor, std::string iname)
	:color(icolor), name(iname) {
	}

	Move getNextMove() {
		return Move();
	}
private:
	int color;
	std::string name;
};