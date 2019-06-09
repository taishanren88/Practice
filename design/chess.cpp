#include <iostream>
#include <list>
#include <unordered_set>

using namespace std;

/* 
http://swcodes.blogSpot.com/2012/09/chess-game-design.html
http://k2code.blogSpot.com/2014/03/design-chess-game-using-oo-principles.html
https://codereview.stackexchange.com/questions/71790/design-a-chess-game-using-object-oriented-principles
*/

// Determine checkmate status..., won , not won, ... etc., move validity
class InterfaceGameRules {

};


class Piece;

class Spot{
public:
 int x, y;// could be redundatn if we use-2D-array . If we decide to use a set of Spots we need this
 Piece* piece; // used to determine what's here
 bool getPiece(Piece* getPiece) const {
 	return true;
 }
};

struct Move {
	// Determine where we are moving from
	pair<int,int> getFrom()const  {
		return make_pair(0,0);
	}

	// Determine where we are moving to
	pair <int, int> getTo ()const  {
		return make_pair(0,0);
	}

	// Get the piece we are moving to
	Piece* getPiece();
	// Get the piece we are potentially capturing
	Piece* getCapturedPiece();
};
class Player;

enum class MoveStatus {
	CHECKMATE,
	STALEMATE,
	CHECK,
	CONTINUE,
};

enum class GameStatus {
	WHITEWIN,
	BLACKWIN,
	DRAW
};

class Board;
class Player;
class Game : public InterfaceGameRules {
public:
	bool isOver () const {
		return false;
	}
	void init() {

	}
	bool play() {
		 while (true) /* Check if status is staelmate or checkmate/...etc*/
		 {
		 	// auto player = playerOne; // get the right player
			// Move move = player->getNextMove();
			// move.getPiece()->movePiece(Spot a, Spot b);
			// if (move.getCapturedPiece()->isCaptured())
			// 	board->removePiece(move.getCapturedPiece())
			// changeTurn();
		}
		

		return true;
	}
	Board* getBoard() {
		return board;
	}

private:
	Board* board;
	Player* playerOne;
	Player* playerTwo;
	list<Move*> getMoveHistory() const;
	void changeTurn();
};

Game* getGame()
{
	static Game* game = nullptr;
	if (!game)
		game = new Game();
	return game;
}


class Player {

public:
	Player (int color) { 
	}

	Move getNextMove() const {
		Move m;
		return m;
	}

};

// 
class Board {
public:
	virtual void init();
	virtual void createSpot(Spot a) = 0;
	void addPiece(Spot at, Piece* newPiece);
	void removePiece(Spot at, Piece* piece);
	Piece* getPieceAt(Spot& a)
	{
		return nullptr;
	}

private:
	list<Piece*> getWhitePieces();
	list<Piece*> getBlackPieces();
	//unordered_set<Spot> Spots; // comment to get it compile
};

// virtual class, handles promotion, en-passant, castling , setting captured state
class Piece {
public:
	Piece(int x, int y);
	// Handl
	virtual void movePiece(Spot& a, Spot& b)  {
		movePiece(a, b);
		Piece* capturedPiece;
		if (b.getPiece(capturedPiece))
		{
			auto piece = getGame()->getBoard()->getPieceAt(a);
			piece->setCaptured();
		}
	}
	virtual list<Move> getPossibleMoves() const = 0;
	virtual bool isValidMove(Spot a, Spot b) const {
		// Checks if there are obstacles in the way wehter it can jump over them, etc...
		return true;
	}

	bool isCaptured() const; // is valid ,is dead/etc...
	void setCaptured();
};


class Pawn : public Piece {


	virtual void movePiece(Spot& a, Spot& b) {
		// Handle en-passant, promotion
		Piece::movePiece(a, b);
	}

	virtual list<Move> getPossibleMoves() const = 0;
	virtual bool isValidMove(Spot a, Spot b) const = 0;
};


int main() {

}