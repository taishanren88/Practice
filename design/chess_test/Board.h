#pragma once
#include <list>
#include <vector>
class Board {
public:
	void placePieceAt(Piece* piece, Spot a) {

	}

	void addPiece(Piece* piece, int x, int y) {

	}
	Piece* getPieceAt(int x, int y){
		return nullptr;
	}
	bool isCheckMate() {
		return false;
	}
private:
	// white/black piece groups
	std::list<Piece*> blackPieces;
	std::list<Piece*> whitePieces;
	// list of spots
	std::vector<std::vector<Spot>> spots;

};