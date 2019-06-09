#pragma once

#include "Spot.h"
#include "Piece.h"
struct Move {
	Spot src, dst;
	Piece* capturedPiece;
	Piece* srcPiece;
};