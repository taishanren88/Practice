#pragma once
// For Pawn
#include "Spot.h"
class Piece {
public:
	Piece() {

	}
	virtual bool isValidMove(Spot& src, Spot& dest) const = 0;
	virtual void movePiece(Spot& dest)  = 0;

private:
};

class Pawn : public Piece {
	public:
	Pawn () {

	}
	virtual bool isValidMove(Spot& src, Spot& dest) const{
		return true;
	}
	virtual void movePiece(Spot& dest) {

	}

private:
};

class King : public Piece{
	public:

	virtual bool isValidMove(Spot& src, Spot& dest) const {
		return true;
	}
	virtual void movePiece(Spot& dest) {

	}

private:
};

enum class Direction {
	UP, 
	DOWN
};