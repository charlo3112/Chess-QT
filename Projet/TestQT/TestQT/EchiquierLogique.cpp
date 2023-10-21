
#pragma once

#include "EchiquierLogique.h"
#include "Piece.h"
#include "Exceptions.h"

#include <typeinfo>

EchiquierLogique::EchiquierLogique() // Initialisation standard du board logique
{
	for (int row = 2; row < 6; row++) {
		for (int col = 0; col < 8; col++) {
			boardLogique[row][col] = nullptr;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		boardLogique[1][i] = make_unique<piece::Pawn>(PieceColor::Black, 1, i);
		boardLogique[6][i] = make_unique<piece::Pawn>(PieceColor::White, 6, i);
	}
	boardLogique[0][0] = make_unique<piece::Rook>(PieceColor::Black, 0, 0);
	boardLogique[0][7] = make_unique<piece::Rook>(PieceColor::Black, 0, 7);
	boardLogique[7][0] = make_unique<piece::Rook>(PieceColor::White, 7, 0);
	boardLogique[7][7] = make_unique<piece::Rook>(PieceColor::White, 7, 7);

	boardLogique[0][1] = make_unique<piece::Knight>(PieceColor::Black, 0, 1);
	boardLogique[0][6] = make_unique<piece::Knight>(PieceColor::Black, 0, 6);
	boardLogique[7][1] = make_unique<piece::Knight>(PieceColor::White, 7, 1);
	boardLogique[7][6] = make_unique<piece::Knight>(PieceColor::White, 7, 6);

	boardLogique[7][3] = make_unique<piece::Queen>(PieceColor::White, 7, 3);
	boardLogique[0][3] = make_unique<piece::Queen>(PieceColor::Black, 0, 3);

	boardLogique[0][4] = make_unique<piece::King>(PieceColor::Black, 0, 4);
	boardLogique[7][4] = make_unique<piece::King>(PieceColor::White, 7, 4);
}

EchiquierLogique::~EchiquierLogique()
{
}


void EchiquierLogique::vecteurPosition(int oldCol, int oldRow) //Choisis la methode approprie pour generer les positions possibles en fonction du type
{
	if (boardLogique[oldRow][oldCol] != nullptr) {
		if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::Rook))
		{
			vecteurPositionRook(oldCol, oldRow);
		}
		else if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::Knight))
		{
			vecteurPositionKnight(oldCol, oldRow);
		}
		else if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::Bishop))
		{
			vecteurPositionBishop(oldCol, oldRow);
		}
		else if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::Queen))
		{
			vecteurPositionQueen(oldCol, oldRow);
		}
		else if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::King))
		{
			vecteurPositionKing(oldCol, oldRow);
		}
		else if (typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::Pawn))
		{
			vecteurPositionPawn(oldCol, oldRow);
		}
		else {

		}
	}
}

void EchiquierLogique::vecteurPositionRook(int oldCol, int oldRow) { //Vecteur pour rook
	//For rows
	for (int i = oldRow; i < 8; i++) {
		if (i != oldRow) {
			if (boardLogique[i][oldCol] != nullptr) {
				if (boardLogique[i][oldCol]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
			}
		}
	}
	for (int i = oldRow; i >= 0; i--) {
		if (i != oldRow) {
			if (boardLogique[i][oldCol] != nullptr) {
				if (boardLogique[i][oldCol]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
			}
		}
	}
	//For columns
	for (int i = oldCol; i < 8; i++) {
		if (i != oldCol) {
			if (boardLogique[oldRow][i] != nullptr) {
				if (boardLogique[oldRow][i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
			}
		}
	}
	for (int i = oldCol; i >= 0; i--) {
		if (i != oldCol) {
			if (boardLogique[oldRow][i] != nullptr) {
				if (boardLogique[oldRow][i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
			}
		}
	}
}

void EchiquierLogique::vecteurPositionKnight(int oldCol, int oldRow) { //Vecteur pour Knight

	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 2, oldCol + 1));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 2, oldCol + 1));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 2, oldCol - 1));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 2, oldCol - 1));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 2));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 2));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 2));
	boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 2));

	for (int i = boardLogique[oldRow][oldCol]->posPiece.size() - 1; i >= 0; i--) {
		if (boardLogique[oldRow][oldCol]->posPiece[i].getCol() > 7 ||
			boardLogique[oldRow][oldCol]->posPiece[i].getCol() < 0 ||
			boardLogique[oldRow][oldCol]->posPiece[i].getRow() > 7 ||
			boardLogique[oldRow][oldCol]->posPiece[i].getRow() < 0) {

			boardLogique[oldRow][oldCol]->posPiece.erase(boardLogique[oldRow][oldCol]->posPiece.begin() + i);
		}
	}
	for (int i = boardLogique[oldRow][oldCol]->posPiece.size() - 1; i >= 0; i--) {
		int col = boardLogique[oldRow][oldCol]->posPiece[i].getCol();
		int row = boardLogique[oldRow][oldCol]->posPiece[i].getRow();
		if (boardLogique[row][col] != nullptr) {
			if (boardLogique[row][col]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
				boardLogique[oldRow][oldCol]->posPiece.erase(boardLogique[oldRow][oldCol]->posPiece.begin() + i);
			}

		}
	}
}

void EchiquierLogique::vecteurPositionBishop(int oldCol, int oldRow) { //Vecteur pour Bishop
	for (int i = 1; i < 8; i++) {
		if (oldCol + i < 8 && oldRow + i < 8) {
			if (boardLogique[oldRow + i][oldCol + i] != nullptr) {
				if (boardLogique[oldRow + i][oldCol + i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol + i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol + i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol - i >= 0 && oldRow - i >= 0) {
			if (boardLogique[oldRow - i][oldCol - i] != nullptr) {
				if (boardLogique[oldRow - i][oldCol - i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol - i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol - i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol + i < 8 && oldRow - i >= 0) {
			if (boardLogique[oldRow - i][oldCol + i] != nullptr) {
				if (boardLogique[oldRow - i][oldCol + i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol + i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol + i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol - i >= 0 && oldRow + i < 8) {
			if (boardLogique[oldRow + i][oldCol - i] != nullptr) {
				if (boardLogique[oldRow + i][oldCol - i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol - i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol - i));
		}
	}

}

void EchiquierLogique::vecteurPositionQueen(int oldCol, int oldRow) { //Vecteur pour Queen

	//For rows
	for (int i = oldRow; i < 8; i++) {
		if (i != oldRow) {
			if (boardLogique[i][oldCol] != nullptr) {
				if (boardLogique[i][oldCol]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
			}
		}
	}
	for (int i = oldRow; i >= 0; i--) {
		if (i != oldRow) {
			if (boardLogique[i][oldCol] != nullptr) {
				if (boardLogique[i][oldCol]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(i, oldCol));
			}
		}
	}
	//For columns
	for (int i = oldCol; i < 8; i++) {
		if (i != oldCol) {
			if (boardLogique[oldRow][i] != nullptr) {
				if (boardLogique[oldRow][i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
			}
		}
	}
	for (int i = oldCol; i >= 0; i--) {
		if (i != oldCol) {
			if (boardLogique[oldRow][i] != nullptr) {
				if (boardLogique[oldRow][i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
				break;
			}
			else {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, i));
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		if (oldCol + i < 8 && oldRow + i < 8) {
			if (boardLogique[oldRow + i][oldCol + i] != nullptr) {
				if (boardLogique[oldRow + i][oldCol + i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol + i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol + i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol - i >= 0 && oldRow - i >= 0) {
			if (boardLogique[oldRow - i][oldCol - i] != nullptr) {
				if (boardLogique[oldRow - i][oldCol - i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol - i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol - i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol + i < 8 && oldRow - i >= 0) {
			if (boardLogique[oldRow - i][oldCol + i] != nullptr) {
				if (boardLogique[oldRow - i][oldCol + i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol + i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - i, oldCol + i));
		}
	}
	for (int i = 1; i < 8; i++) {
		if (oldCol - i >= 0 && oldRow + i < 8) {
			if (boardLogique[oldRow + i][oldCol - i] != nullptr) {
				if (boardLogique[oldRow + i][oldCol - i]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
					break;
				}
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol - i));
				break;
			}
			boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + i, oldCol - i));
		}
	}
}


void EchiquierLogique::vecteurPositionKing(int oldCol, int oldRow) { ////Vecteur pour King
	if (oldRow + 1 > 7 && oldCol + 1 > 7) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
	}
	else if (oldRow - 1 < 0 && oldCol - 1 < 0) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
	}
	else if (oldRow - 1 < 0 && oldCol + 1 > 7) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));

	}
	else if (oldRow + 1 > 7 && oldCol - 1 < 0) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));

	}
	else if (oldRow + 1 > 7) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));

	}
	else if (oldRow - 1 < 0) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));

	}
	else if (oldCol + 1 > 7) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));
	}
	else if (oldCol - 1 < 0) {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));

	}
	else {
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol + 1));
		boardLogique[oldRow][oldCol]->addPosition(Position(oldRow, oldCol - 1));
	}
	for (int i = boardLogique[oldRow][oldCol]->posPiece.size() - 1; i >= 0; i--) {
		int col = boardLogique[oldRow][oldCol]->posPiece[i].getCol();
		int row = boardLogique[oldRow][oldCol]->posPiece[i].getRow();
		if (boardLogique[row][col] != nullptr) {
			if (boardLogique[row][col]->getColor() == boardLogique[oldRow][oldCol]->getColor()) {
				boardLogique[oldRow][oldCol]->posPiece.erase(boardLogique[oldRow][oldCol]->posPiece.begin() + i);
			}

		}
	}

}

void EchiquierLogique::vecteurPositionPawn(int oldCol, int oldRow) { //Vecteur pour pawn
	if (boardLogique[oldRow][oldCol]->getColor() == PieceColor::White) {
		if (oldRow == 6) {
			if (boardLogique[oldRow - 1][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
			}

			if (boardLogique[oldRow - 2][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 2, oldCol));
			}

			if (boardLogique[oldRow - 1][oldCol - 1] != nullptr && boardLogique[oldRow - 1][oldCol - 1]->getColor() == PieceColor::Black) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
			}

			if (boardLogique[oldRow - 1][oldCol + 1] != nullptr && boardLogique[oldRow - 1][oldCol + 1]->getColor() == PieceColor::Black) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));
			}
		}
		else if (oldRow == 0) {

		}
		else {
			if (boardLogique[oldRow - 1][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol));
			}

			if (boardLogique[oldRow - 1][oldCol - 1] != nullptr && boardLogique[oldRow - 1][oldCol - 1]->getColor() == PieceColor::Black) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol - 1));
			}

			if (boardLogique[oldRow - 1][oldCol + 1] != nullptr && boardLogique[oldRow - 1][oldCol + 1]->getColor() == PieceColor::Black) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow - 1, oldCol + 1));
			}
		}
	}
	else if (boardLogique[oldRow][oldCol]->getColor() == PieceColor::Black) {
		if (oldRow == 1) {
			if (boardLogique[oldRow + 1][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));

			}
			if (boardLogique[oldRow + 2][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 2, oldCol));
			}

			if (boardLogique[oldRow + 1][oldCol + 1] != nullptr && boardLogique[oldRow + 1][oldCol + 1]->getColor() == PieceColor::White) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
			}
			if (boardLogique[oldRow + 1][oldCol - 1] != nullptr && boardLogique[oldRow + 1][oldCol - 1]->getColor() == PieceColor::White) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));
			}
		}
		else if (oldRow == 7) {

		}
		else {
			if (boardLogique[oldRow + 1][oldCol] == nullptr) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol));
			}
			if (boardLogique[oldRow + 1][oldCol + 1] != nullptr && boardLogique[oldRow + 1][oldCol + 1]->getColor() == PieceColor::White) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol + 1));
			}
			if (boardLogique[oldRow + 1][oldCol - 1] != nullptr && boardLogique[oldRow + 1][oldCol - 1]->getColor() == PieceColor::White) {
				boardLogique[oldRow][oldCol]->addPosition(Position(oldRow + 1, oldCol - 1));
			}
		}
	}
}

bool EchiquierLogique::newMoveCheck(int oldCol, int oldRow, int newCol, int newRow) { // Verifie si la nouvelle position est dans le vecteur de positions possibles
	boardLogique[oldRow][oldCol];
	for (int i = 0; i < boardLogique[oldRow][oldCol]->posPiece.size(); i++) {
		if (boardLogique[oldRow][oldCol]->posPiece[i].getCol() == newCol && boardLogique[oldRow][oldCol]->posPiece[i].getRow() == newRow  /* && isPathClear(oldCol, oldRow, newCol, newRow)*/) {
			return true;
		}
	}
	return false;
}

void EchiquierLogique::movePiece(int oldCol, int oldRow, int newCol, int newRow) { // Bouger la piece dans le board logique

	auto& pieceToMove = boardLogique[oldRow][oldCol];

	pieceToMove->posPiece.clear();

	pieceToMove->pos_.setCol(newCol);
	pieceToMove->pos_.setRow(newRow);

	boardLogique[newRow][newCol] = move(pieceToMove);
	pieceToMove = nullptr;

}

void EchiquierLogique::checkBoard() { //Compte le nombre de rois
	int compteur = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (boardLogique[i][j] != nullptr) {
				if (typeid(*boardLogique[i][j]) == typeid(piece::King)) {
					++compteur;
				}
			}
		}
	}
	if (compteur > 2) {
		throw PieceException("Il y a plus de 2 rois sur l'echiquier");
	}
}

bool EchiquierLogique::isCheck(int oldRow, int oldCol, int nextRow, int nextCol) { //Verifie s'il y a un echec

	vecteurPosition(nextCol, nextRow);

	for (int i = 0; i < boardLogique[nextRow][nextCol]->posPiece.size(); i++){
		int col = boardLogique[nextRow][nextCol]->posPiece[i].getCol();
		int row = boardLogique[nextRow][nextCol]->posPiece[i].getRow();
		if (boardLogique[row][col] != nullptr) {
			if (typeid(*boardLogique[row][col]) == typeid(piece::King) &&
				boardLogique[nextRow][nextCol]->getColor() != boardLogique[row][col]->getColor()) {
				boardLogique[nextRow][nextCol]->posPiece.clear();
				return true;
			}
		}
	}
	boardLogique[nextRow][nextCol]->posPiece.clear();
	return false;
}
bool EchiquierLogique::moveRoi (int oldRow, int oldCol){
	if(boardLogique[oldRow][oldCol] != nullptr){
		if(typeid(*boardLogique[oldRow][oldCol]) == typeid(piece::King)){
			return true;
		}
	}
	return false;
}


int EchiquierLogique::whoWon(){ //Verifie qui a gagne
	bool blackKing = false;
	bool whiteKing = false;
	for (int row= 0; row < 8; row++){
		for (int col = 0; col < 8; col++){
			if (boardLogique[row][col] != nullptr) {
				if (typeid(*boardLogique[row][col]) == typeid(piece::King)) {
					if(boardLogique[row][col]->getColor() == PieceColor::White){
						whiteKing = true;
					}
					if (boardLogique[row][col]->getColor() == PieceColor::Black) {
						blackKing = true;
					}
				}
			}
		}
	}
	if (!whiteKing){
		return 1;
	}
	if (!blackKing){
		return 2;
	}
	else {
		return 0;
	}
		
}