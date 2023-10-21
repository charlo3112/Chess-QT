
#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <qstackedwidget.h>
#include <qstring.h>

#include "mainmenu.h"
#include "SelectionScreen.h"
#include "EchiquierLogique.h"
#include "Piece.h"
#include "ChessSquare.h"

namespace vue {
    class TestQT : public QMainWindow
    {
        Q_OBJECT

    public:
        TestQT(QWidget* parent = nullptr);
        ~TestQT();



    private slots:
        void squareClicked();

    private:
        QStackedWidget* m_stackedWidget;
        MainMenu* m_mainMenu;
        SelectionScreen* m_selectionScreen;
        QGridLayout* chessGrid;
        ChessSquare* chessButton[8][8];
        ChessSquare* selectedPiece = nullptr;
        int selectedPieceRow = -1;
        int selectedPieceColumn = -1;

        QIcon whiteKing;
        QIcon whiteQueen;
        QIcon whiteTower;
        QIcon whiteBishop;
        QIcon whiteHorse;
        QIcon whitePawn;
        QIcon blackKing;
        QIcon blackQueen;
        QIcon blackTower;
        QIcon blackBishop;
        QIcon blackHorse;
        QIcon blackPawn;

        void newGameStarted();
        void normalGameStarted();
        void changePawnsStarted();
        void changeBishopsStarted();
        void initFullUI();
        void initChessBoard(QWidget* centralWidget);
        void initChangePawns();
        void initChangeBishops();
        void colorPossibleMoves();
        void colorMethod(int col, int row);
        void colorClicked(int col, int row);
        void resetColors();
        void showPopup(const QString& title, const QString& message);
        void moveUiPiece(ChessSquare* clicked);

        EchiquierLogique echiquier;

    };
}
