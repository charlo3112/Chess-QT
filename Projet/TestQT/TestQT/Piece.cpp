
#pragma once

#include "Piece.h"

#include <memory>

using namespace std;


piece::Piece::Piece(PieceColor color, int row, int col) :
	color_(color),
	pos_(row, col)
{
}

piece::Piece::~Piece()
{
}

void piece::Piece::addPosition(Position pos) {
	posPiece.push_back(pos);
}

bool piece::Piece::move(int row, int col) {
	if (col == pos_.getCol() && row == pos_.getRow()) {
		return false;
	}
	else {
		return true;
	}
}

piece::Pawn::Pawn(PieceColor color, int row, int col) :
Piece(color, row, col)
{
}

piece::Pawn::~Pawn()
{
}



piece::Rook::Rook(PieceColor color, int row, int col) :
Piece(color, row, col)
{
}

piece::Rook::~Rook()
{
}




piece::Knight::Knight(PieceColor color, int row, int col) :
Piece(color, row, col)
{
}

piece::Knight::~Knight()
{
}




piece::Bishop::Bishop(PieceColor color, int row, int col) :
	Piece(color, row, col)
{
}

piece::Bishop::~Bishop()
{
}




piece::Queen::Queen(PieceColor color, int row, int col) :
	Piece(color, row, col)
{
}

piece::Queen::~Queen()
{
}



piece::King::King(PieceColor color, int row, int col) :
	Piece(color, row, col)
{
}

piece::King::~King()
{
}
