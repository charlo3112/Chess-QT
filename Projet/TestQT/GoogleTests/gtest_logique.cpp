#include "gtest/gtest.h"
#include "../EchiquierLogique.h"
using namespace std;

class EchiquierLogiqueTest : public ::testing::Test{
protected:
	void SetUp() override {
		echiquier = new EchiquierLogique();
	}
	void TearDown() override {
		delete echiquier;
	}
	EchiquierLogique* echiquier;
};

TEST_F(EchiquierLogiqueTest, VecteurPositionKing){
	echiquier->vecteurPositionKing(0, 4);
	vector<Position> positionVoulu = {
		Position(1,5),
		Position(1,3),
		Position(1,4),
		Position(0,5),
		Position(0,3)
	};
	ASSERT_EQ(positionVoulu.size(), echiquier->boardLogique[0][4]->posPiece.size());


	for (int i = 0; i < positionVoulu.size(); ++i){
		bool trouve = false;
		for(int j = 0; j < positionVoulu.size(); ++j){
			
			if(positionVoulu[i].getCol() == echiquier->boardLogique[0][4]->posPiece[j].getCol() &&
				positionVoulu[i].getRow() == echiquier->boardLogique[0][4]->posPiece[j].getRow()){

				trouve = true;
				break;
			}
		}
		EXPECT_TRUE(trouve) << "Il n'a pas toutes la colonne" << positionVoulu[i].getCol() << "et lignes voulu" << positionVoulu[i].getRow();
	}
	

}

TEST_F(EchiquierLogiqueTest, DeplacementStandard) {
	//Verifie si un pion peut se deplacer correctement
	echiquier->boardLogique[2][2] =  make_unique<piece::Pawn>(PieceColor::Black, 2, 2);
	EXPECT_EQ(echiquier->newMoveCheck(echiquier->boardLogique[2][2]->getCol(), echiquier->boardLogique[2][2]->getRow(), 2, 3), true);
	EXPECT_EQ(echiquier->newMoveCheck(echiquier->boardLogique[2][2]->getCol(), echiquier->boardLogique[2][2]->getRow(), 2, 5), false);
}

TEST_F(EchiquierLogiqueTest, EnEchec) {
	//Verifie que la methode retourne bien true si on met le roi en echec avec un pion
	echiquier->boardLogique[2][5] = make_unique<piece::Pawn>(PieceColor::White, 2, 5);
	echiquier->boardLogique[3][5] = make_unique<piece::Pawn>(PieceColor::White, 2, 5);
	EXPECT_EQ(echiquier->isCheck(echiquier->boardLogique[2][5]->getRow(), echiquier->boardLogique[2][5]->getCol(), 1, 5), true);
	EXPECT_EQ(echiquier->isCheck(echiquier->boardLogique[3][5]->getRow(), echiquier->boardLogique[3][5]->getCol(), 2, 5), false);
}

TEST_F(EchiquierLogiqueTest, NombreDeRois) {
	//Verifie que la methode lance bien une runtime error s'il y a trop de rois en jeu
	echiquier->boardLogique[5][5] = make_unique<piece::King>(PieceColor::White, 5, 5);
	echiquier->boardLogique[5][4] = make_unique<piece::King>(PieceColor::White, 5, 4);
	echiquier->boardLogique[5][3] = make_unique<piece::King>(PieceColor::White, 5, 3);
	EXPECT_THROW(echiquier->checkBoard(), runtime_error);
}

TEST_F(EchiquierLogiqueTest, QuiAGagne) {
	//Verifie que notre methode dit bien qui a gagne
	echiquier->boardLogique[0][4] = nullptr;
	EXPECT_EQ(echiquier->whoWon(), 2);
	EXPECT_NE(echiquier->whoWon(), 1);
}

