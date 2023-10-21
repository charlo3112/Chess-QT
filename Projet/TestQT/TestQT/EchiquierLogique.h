#pragma once

#include "Piece.h"

#include <memory>
//#include <QSignalMapper>
//#include <QPushButton>
//#include <QObject>

using namespace std;


class EchiquierLogique
{
public:
	EchiquierLogique();
	~EchiquierLogique();

	void vecteurPosition(int oldCol, int oldRow);

	unique_ptr<piece::Piece> boardLogique[8][8];
	void checkBoard();

	bool isCheck(int oldRow, int oldCol, int nextRow, int nextCol);
	bool moveRoi(int oldRow, int oldCol);
	void vecteurPositionRook(int oldCol, int oldRow);
	void vecteurPositionKnight(int oldCol, int oldRow);
	void vecteurPositionBishop(int oldCol, int oldRow);
	void vecteurPositionQueen(int oldCol, int oldRow);
	void vecteurPositionKing(int oldCol, int oldRow);
	void vecteurPositionPawn(int oldCol, int oldRow);

	bool newMoveCheck(int oldCol, int oldRow, int newCol, int newRow);
	
	void movePiece(int oldCol, int oldRow, int newCol, int newRow);

	int whoWon();
};
