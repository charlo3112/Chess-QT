#include "TestQT.h"
#include "ui_TestQT.h"
#include "EchiquierLogique.h"

#include <QWidget>
#include <QIcon>
#include <qmessagebox.h>
#include <QVariant>
#include <QMetaType>
#include <qregularexpression.h>
#include <qpushbutton.h>
#include <stdexcept>

vue::TestQT::TestQT(QWidget *parent)
    : QMainWindow(parent),
	whiteKing(":/images/WhiteKing.png"),
	whiteQueen(":/images/WhiteQueen.png"),
	whiteTower(":/images/WhiteTower.png"),
	whiteBishop(":/images/WhiteBishop.png"),
	whiteHorse(":/images/WhiteHorse.png"),
	whitePawn(":/images/WhitePawn.png"),
	blackKing(":/images/BlackKing.png"),
	blackQueen(":/images/BlackQueen.png"),
	blackTower(":/images/BlackTower.png"),
	blackBishop(":/images/BlackBishop.png"),
	blackHorse(":/images/BlackHorse.png"),
	blackPawn(":/images/BlackPawn.png"),
	m_stackedWidget(new QStackedWidget(this)),
	m_mainMenu(new MainMenu(this)),
	m_selectionScreen(new SelectionScreen(this))
{
    setCentralWidget(m_stackedWidget);
	initFullUI();
}

vue::TestQT::~TestQT()
{
}
enum class ChessPieceType {
	Empty, Pawn, Knight, Bishop, Rook, Queen, King
};

void vue::TestQT::initFullUI() {
	QWidget* centralWidget = new QWidget(this);

	initChessBoard(centralWidget);
	m_stackedWidget->addWidget(m_mainMenu); //Ecran du menu
	m_stackedWidget->addWidget(m_selectionScreen); //Ecran de selection de configuration
	m_stackedWidget->addWidget(centralWidget); //Jeu
	m_stackedWidget->setCurrentWidget(m_mainMenu);
	connect(m_mainMenu, &MainMenu::newGameRequested, this, &vue::TestQT::newGameStarted);
	connect (m_mainMenu, &MainMenu::quitRequested, this, &vue::TestQT::close);
	connect(m_selectionScreen, &SelectionScreen::normalGameRequested, this, &vue::TestQT::normalGameStarted);
	connect(m_selectionScreen, &SelectionScreen::changePawnsRequested, this, &vue::TestQT::changePawnsStarted);
	connect(m_selectionScreen, &SelectionScreen::changeBishopsRequested, this, &vue::TestQT::changeBishopsStarted);
}

void vue::TestQT::newGameStarted() {
	m_stackedWidget->setCurrentIndex(1);
}

void vue::TestQT::normalGameStarted() { //Configuration standard
	m_stackedWidget->setCurrentIndex(2);
}
void vue::TestQT::changePawnsStarted() { //Configuration 1 
	initChangePawns();
	m_stackedWidget->setCurrentIndex(2);
}

void vue::TestQT::changeBishopsStarted() { //Configuration 2
	initChangeBishops();
	m_stackedWidget->setCurrentIndex(2);
}

//Initialisation standard de l'echiquier 
void vue::TestQT::initChessBoard(QWidget* centralWidget) {
    chessGrid = new QGridLayout();
    chessGrid->setSpacing(0);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
			ChessSquare *square = new ChessSquare();
			chessButton[i][j] = square;
			square->setFixedSize(75, 75);
			square->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
			square->chessPiece.col = j;
			square->chessPiece.row = i;
			chessGrid->addWidget(square, i, j);
            if ((i + j) % 2 == 0) {
				square->setStyleSheet("background-color: beige;");
			}
            else {
				square->setStyleSheet("background-color: grey;");
            }
			connect(square, &QPushButton::clicked, this, &TestQT::squareClicked);
		}
	}

	//WHITE
	//Pour les pions
	for (int i = 0; i < 8; ++i) {
		chessButton[6][i]->setIcon(whitePawn);
		chessButton[6][i]->setIconSize(QSize(75, 75));
		chessButton[6][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Pawn));
		chessButton[6][i]->chessPiece.col = i;
		chessButton[6][i]->chessPiece.row = 6;
	}
	//Pour le roi
	QString whiteKingPath = ":/images/WhiteKing.png";
	QIcon whiteKing(whiteKingPath);
	chessButton[7][4]->setIcon(whiteKing);
	chessButton[7][4]->setIconSize(QSize(75, 75));
	chessButton[7][4]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::King));
	chessButton[7][4]->chessPiece.col = 4;
	chessButton[7][4]->chessPiece.row = 7;

	//Pour la tour 
	chessButton[7][0]->setIcon(whiteTower);
	chessButton[7][0]->setIconSize(QSize(75, 75));
	chessButton[7][7]->setIcon(whiteTower);
	chessButton[7][7]->setIconSize(QSize(75, 75));
	chessButton[7][0]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Rook));
	chessButton[7][7]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Rook));
	chessButton[7][0]->chessPiece.col = 0;
	chessButton[7][0]->chessPiece.row = 7;
	chessButton[7][7]->chessPiece.col = 7;
	chessButton[7][7]->chessPiece.row = 7;

	//Pour le cavalier
	chessButton[7][1]->setIcon(whiteHorse);
	chessButton[7][1]->setIconSize(QSize(75, 75));
	chessButton[7][6]->setIcon(whiteHorse);
	chessButton[7][6]->setIconSize(QSize(75, 75));
	chessButton[7][1]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Knight));
	chessButton[7][6]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Knight));
	chessButton[7][1]->chessPiece.col = 1;
	chessButton[7][1]->chessPiece.row = 7;
	chessButton[7][6]->chessPiece.col = 6;
	chessButton[7][6]->chessPiece.row = 7;

	//Pour le fou
	chessButton[7][2]->setIcon(whiteBishop);
	chessButton[7][2]->setIconSize(QSize(75, 75));
	chessButton[7][5]->setIcon(whiteBishop);
	chessButton[7][5]->setIconSize(QSize(75, 75));
	chessButton[7][2]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[7][5]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[7][2]->chessPiece.col = 2;
	chessButton[7][2]->chessPiece.row = 7;
	chessButton[7][5]->chessPiece.col = 5;
	chessButton[7][5]->chessPiece.row = 7;

	//Pour la reine
	chessButton[7][3]->setIcon(whiteQueen);
	chessButton[7][3]->setIconSize(QSize(75, 75));
	chessButton[7][3]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Queen));
	chessButton[7][3]->chessPiece.col = 3;
	chessButton[7][3]->chessPiece.row = 7;

	//BLACK
	//Pour les pions
	for (int i = 0; i < 8; ++i) {
		chessButton[1][i]->setIcon(blackPawn);
		chessButton[1][i]->setIconSize(QSize(75, 75));
		chessButton[1][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Pawn));
		chessButton[1][i]->chessPiece.col = i;
		chessButton[1][i]->chessPiece.row = 1;
	}
	//Pour le roi
	chessButton[0][4]->setIcon(blackKing);
	chessButton[0][4]->setIconSize(QSize(75, 75));
	chessButton[0][4]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::King));
	chessButton[0][4]->chessPiece.col = 4;
	chessButton[0][4]->chessPiece.row = 0;

	//Pour la tour
	chessButton[0][0]->setIcon(blackTower);
	chessButton[0][0]->setIconSize(QSize(75, 75));
	chessButton[0][7]->setIcon(blackTower);
	chessButton[0][7]->setIconSize(QSize(75, 75));
	chessButton[0][0]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Rook));
	chessButton[0][7]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Rook));
	chessButton[0][0]->chessPiece.col = 0;
	chessButton[0][0]->chessPiece.row = 0;
	chessButton[0][7]->chessPiece.col = 7;
	chessButton[0][7]->chessPiece.row = 0;

	//Pour le cavalier
	chessButton[0][1]->setIcon(blackHorse);
	chessButton[0][1]->setIconSize(QSize(75, 75));
	chessButton[0][6]->setIcon(blackHorse);
	chessButton[0][6]->setIconSize(QSize(75, 75));
	chessButton[0][1]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Knight));
	chessButton[0][6]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Knight));
	chessButton[0][1]->chessPiece.col = 1;
	chessButton[0][1]->chessPiece.row = 0;
	chessButton[0][6]->chessPiece.col = 6;
	chessButton[0][6]->chessPiece.row = 0;

	//Pour le fou
	chessButton[0][2]->setIcon(blackBishop);
	chessButton[0][2]->setIconSize(QSize(75, 75));
	chessButton[0][5]->setIcon(blackBishop);
	chessButton[0][5]->setIconSize(QSize(75, 75));
	chessButton[0][2]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[0][5]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[0][2]->chessPiece.col = 2;
	chessButton[0][2]->chessPiece.row = 0;
	chessButton[0][5]->chessPiece.col = 5;
	chessButton[0][5]->chessPiece.row = 0;

	//Pour la reine
	chessButton[0][3]->setIcon(blackQueen);
	chessButton[0][3]->setIconSize(QSize(75, 75));
	chessButton[0][3]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Queen));
	chessButton[0][3]->chessPiece.col = 3;
	chessButton[0][3]->chessPiece.row = 0;


	centralWidget->setFixedSize(600, 600);
	centralWidget->setLayout(chessGrid);
}

//On change certaines pieces pour la configuration speciale 1
void vue::TestQT::initChangePawns() {
	//WHITE
	for (int i = 0; i < 8; ++i) {
		chessButton[6][i]->setIcon(QIcon());
		chessButton[6][i]->setIconSize(QSize(75, 75));
		chessButton[6][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
		chessButton[6][i]->chessPiece.col = i;
		chessButton[6][i]->chessPiece.row = 6;
	}
	for (int i = 0; i < 8; ++i) {
		chessButton[4][i]->setIcon(whitePawn);
		chessButton[4][i]->setIconSize(QSize(75, 75));
		chessButton[4][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Pawn));
		chessButton[4][i]->chessPiece.col = i;
		chessButton[4][i]->chessPiece.row = 4;
	}
	//BLACK
	for (int i = 0; i < 8; ++i) {
		chessButton[1][i]->setIcon(QIcon());
		chessButton[1][i]->setIconSize(QSize(75, 75));
		chessButton[1][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
		chessButton[1][i]->chessPiece.col = i;
		chessButton[1][i]->chessPiece.row = 1;
	}
	for (int i = 0; i < 8; ++i) {
		chessButton[3][i]->setIcon(blackPawn);
		chessButton[3][i]->setIconSize(QSize(75, 75));
		chessButton[3][i]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Pawn));
		chessButton[3][i]->chessPiece.col = i;
		chessButton[3][i]->chessPiece.row = 3;
	}
	for (int row = 1; row < 3; row++) {
		for (int col = 0; col < 8; col++) {
			echiquier.boardLogique[row][col] = nullptr;
		}
	}
	for (int row = 5; row < 7; row++) {
		for (int col = 0; col < 8; col++) {
			echiquier.boardLogique[row][col] = nullptr;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		echiquier.boardLogique[3][i] = make_unique<piece::Pawn>(PieceColor::Black, 3, i);
		echiquier.boardLogique[4][i] = make_unique<piece::Pawn>(PieceColor::White, 4, i);
	}
}

//On change certaines pieces pour la configuration speciale 2
void vue::TestQT::initChangeBishops() {
	chessButton[7][2]->setIcon(QIcon());
	chessButton[7][2]->setIconSize(QSize(75, 75));
	chessButton[7][5]->setIcon(QIcon());
	chessButton[7][5]->setIconSize(QSize(75, 75));
	chessButton[7][2]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
	chessButton[7][5]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
	chessButton[7][2]->chessPiece.col = 2;
	chessButton[7][2]->chessPiece.row = 7;
	chessButton[7][5]->chessPiece.col = 5;
	chessButton[7][5]->chessPiece.row = 7;

	chessButton[4][3]->setIcon(whiteBishop);
	chessButton[4][3]->setIconSize(QSize(75, 75));
	chessButton[4][4]->setIcon(whiteBishop);
	chessButton[4][4]->setIconSize(QSize(75, 75));
	chessButton[4][3]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[4][4]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[4][3]->chessPiece.col = 3;
	chessButton[4][3]->chessPiece.row = 4;
	chessButton[4][4]->chessPiece.col = 4;
	chessButton[4][4]->chessPiece.row = 4;

	chessButton[3][3]->setIcon(blackBishop);
	chessButton[3][3]->setIconSize(QSize(75, 75));
	chessButton[3][4]->setIcon(blackBishop);
	chessButton[3][4]->setIconSize(QSize(75, 75));
	chessButton[3][3]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[3][4]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Bishop));
	chessButton[3][3]->chessPiece.col = 3;
	chessButton[3][3]->chessPiece.row = 3;
	chessButton[3][4]->chessPiece.col = 4;
	chessButton[3][4]->chessPiece.row = 3;

	chessButton[0][2]->setIcon(QIcon());
	chessButton[0][2]->setIconSize(QSize(75, 75));
	chessButton[0][5]->setIcon(QIcon());
	chessButton[0][5]->setIconSize(QSize(75, 75));
	chessButton[0][2]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
	chessButton[0][5]->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
	chessButton[0][2]->chessPiece.col = 2;
	chessButton[0][2]->chessPiece.row = 0;
	chessButton[0][5]->chessPiece.col = 5;
	chessButton[0][5]->chessPiece.row = 0;

	echiquier.boardLogique[0][2] = nullptr;
	echiquier.boardLogique[0][5] = nullptr;
	echiquier.boardLogique[7][2] = nullptr;
	echiquier.boardLogique[7][5] = nullptr;

	echiquier.boardLogique[3][3] = make_unique<piece::Bishop>(PieceColor::Black, 3, 3);
	echiquier.boardLogique[3][4] = make_unique<piece::Bishop>(PieceColor::Black, 3, 4);
	echiquier.boardLogique[4][3] = make_unique<piece::Bishop>(PieceColor::White, 4, 3);
	echiquier.boardLogique[4][4] = make_unique<piece::Bishop>(PieceColor::White, 4, 4);
}

//Tout le deroulement lorsqu'on appuie sur un bouton
void vue::TestQT::squareClicked() {
	QWidget* centralWidget = new QWidget(this);
	ChessSquare* clicked = qobject_cast<ChessSquare*>(sender());

	if (!selectedPiece) {
		if (clicked->property("pieceType").value<ChessPieceType>() != ChessPieceType::Empty) { //Verifie qu'elle n'est pas vide 
			selectedPiece = clicked; //Piece devient celle qu'on appuie
			vue::TestQT::colorClicked(clicked->chessPiece.col, clicked->chessPiece.row);
			echiquier.vecteurPosition(selectedPiece->chessPiece.col, 
				selectedPiece->chessPiece.row);//Affiche la piece selectionnee
			vue::TestQT::colorPossibleMoves();//Affiche les mouvements possibles en fonction du vecteur
		}
		
	}
	else if (selectedPiece) {
		if (clicked != selectedPiece) { //Lorsquon appuie sur une deuxieme case 
			bool isChecked = false;
			if (echiquier.newMoveCheck(selectedPiece->chessPiece.col, 
			selectedPiece->chessPiece.row, clicked->chessPiece.col, 
			clicked->chessPiece.row)) { //Verifie que le mouvement est valide

				echiquier.movePiece(selectedPiece->chessPiece.col, 
				selectedPiece->chessPiece.row, clicked->chessPiece.col,
				clicked->chessPiece.row); //Deplace la piece dans la logique

				if (echiquier.isCheck(selectedPiece->chessPiece.row, selectedPiece->chessPiece.col, clicked->chessPiece.row, clicked->chessPiece.col)) {
					isChecked = true; //Verifie qu'on n'est pas en echec
				}
				vue::TestQT::moveUiPiece(clicked); //Bouge la piece dans le UI 
				vue::TestQT::resetColors(); //Remet toutes les couleurs aux normales 
				if (isChecked) {
					vue::TestQT::showPopup("Check", "Check!"); //Execute si on est en echec
				}
				selectedPiece = nullptr;
				if (echiquier.whoWon() == 1) { //Si les noirs gagnent
					vue::TestQT::showPopup("Game over", "Black Wins!");
					m_stackedWidget->setCurrentIndex(0);
					vue::TestQT* newWindow = new vue::TestQT;
					this->close();
					newWindow->show();
				}
				else if (echiquier.whoWon() == 2) { //Si les blancs ont gagnent
					vue::TestQT::showPopup("Game over", "White Wins!");
					m_stackedWidget->setCurrentIndex(0);
					vue::TestQT* newWindow = new vue::TestQT;
					this->close();
					newWindow->show();
				}
				else { //Si le jeux n'est pas fini, on doit changer de tour
					vue::TestQT::showPopup("Next turn", "Other teams turn");
				}
			}

			else {
				vue::TestQT::showPopup("Invalid Move", "Invalid Move, Try again!"); //Lance si le mouvement est invalide
				selectedPiece = nullptr; //Piece est deselectionnee
				vue::TestQT::resetColors();

			}

		}
		else {
			selectedPiece = nullptr;
			vue::TestQT::resetColors();
		}
	}
}
void vue::TestQT::colorPossibleMoves() { //Permet de colorier les cases valides
	for (int i = 0; i < echiquier.boardLogique[selectedPiece->chessPiece.row][selectedPiece->chessPiece.col]->posPiece.size(); i++) {
		vue::TestQT::colorMethod(echiquier.boardLogique[selectedPiece->chessPiece.row][selectedPiece->chessPiece.col]->posPiece[i].getCol(),
			echiquier.boardLogique[selectedPiece->chessPiece.row][selectedPiece->chessPiece.col]->posPiece[i].getRow());
	}
}
void vue::TestQT::colorMethod(int col, int row) { //Utilisee pour colorier les cases valides
	chessButton[row][col]->setStyleSheet("background-color: rgb(0, 255, 0);");
}
void vue::TestQT::colorClicked(int col, int row) { //Utilisee pour colorier la case selectionnee
	chessButton[row][col]->setStyleSheet("background-color: rgb(255, 0, 0);");
}

void vue::TestQT::resetColors() { //Remet toutes les couleurs aux normales du debut
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 == 0) {
				chessButton[i][j]->setStyleSheet("background-color: beige;");
			}
			else {
				chessButton[i][j]->setStyleSheet("background-color: grey;");
			}
		}
	}
}

void vue::TestQT::moveUiPiece(ChessSquare* clicked) { //Deplacement de la piece dans le UI 
	clicked->setProperty("pieceType", (selectedPiece->property("pieceType")));
	clicked->setIcon(selectedPiece->icon());
	clicked->setIconSize(QSize(75, 75));

	selectedPiece->setProperty("pieceType", QVariant::fromValue(ChessPieceType::Empty));
	selectedPiece->setIcon(QIcon());
	//selectedPiece = nullptr;
}

void vue::TestQT::showPopup(const QString& title, const QString& message) {
	QMessageBox::information(nullptr, title, message);
}

