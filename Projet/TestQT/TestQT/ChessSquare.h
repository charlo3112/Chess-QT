#pragma once
#include <qpushbutton.h>
#include "Piece.h"

class ChessSquare : public QPushButton
{
    Q_OBJECT
public:
    explicit ChessSquare(QWidget* parent = nullptr);
    UIPiece chessPiece;
};