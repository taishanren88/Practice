#pragma once

class Piece;
class Spot {
public:
	Spot(int iX, int iY)
	:x(iX), y(iY), piece(nullptr) {

	}
	Spot() 
	:Spot(-1,-1) {

	}
	int x, y;
	Piece* piece; // if null ,not valid, else valid
	Piece* getPieceAt() {
		return piece;
	}
};