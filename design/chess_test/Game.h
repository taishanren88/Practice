#pragma once

#include "Piece.h"
#include "Player.h"
#include "Move.h"
#include "Board.h"

enum class GameState {
	BLACKWIN,
	WHITEWIN,
	DRAW
};
class Game
{
public:
	Game()
	:playerOne(1, "Jimmy"), playerTwo(0, "John") {

	}
	GameState play () {
		GameStatus status;
		Player& player = playerOne;
		while (status == GameStatus::CONTINUE) {
			Move move = player.getNextMove();
			if (move.srcPiece->isValidMove(move.src, move.dst))
				move.srcPiece->movePiece(move.dst);

			player = changeTurn();
			
			// Check for is checkmate
			if (board.isCheckMate())
			{
				...
			}
		}
		return GameState::BLACKWIN; // TODO fill in
	}
	void init() {
		board.addPiece(new Pawn(), 0, 0);
		board.addPiece(new King(), 0, 1);
		///
	}

private:
	Player& changeTurn() {
		// TODO: oscillate between activate player
		return playerOne;
	}
	enum class GameStatus {
	CHECKMATE,
	STALEMATE,
	CONTINUE
};
Player playerOne;
Player playerTwo;
Board board;


};