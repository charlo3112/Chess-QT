
#pragma once

#include <vector>
#include <memory>

using namespace std;

enum class PieceColor
{
	White,
	Black
};

class Position {
	public:
		Position(int row, int col) : row_(row), col_(col){}
		~Position() {};

		int getCol() const { return col_; }
		int getRow() const { return row_; }

		void setCol(int col) { col_ = col; }
		void setRow(int row) { row_ = row; }

	private:
		int col_, row_;
};
class UIPiece {
public:
	int col, row;
};
namespace piece {

	class Piece
	{
	public:
		Piece() = default;
		Piece(PieceColor color, int row, int col);
		virtual ~Piece();

		virtual bool move(int row, int col);
		virtual void addPosition(Position pos);
		virtual PieceColor getColor() const { return color_; }

		void setCol(int col) { pos_.setCol(col); }
		void setRow(int row) { pos_.setRow(row); }

		int getCol() const { return pos_.getCol(); }
		int getRow() const { return pos_.getRow(); }

		std::vector<Position> posPiece;

		Position pos_;
		PieceColor color_;


	};

	class Pawn : public Piece
	{
	public:
		Pawn() = default;
		Pawn(PieceColor color, int row, int col);
		~Pawn();
	};

	class Rook : public Piece
	{
	public:
		Rook() = default;
		Rook(PieceColor color, int row, int col);
		~Rook();
	};

	class Knight : public Piece
	{
	public:
		Knight() = default;
		Knight(PieceColor color, int row, int col);
		~Knight();
	};

	class Bishop : public Piece
	{
	public:
		Bishop() = default;
		Bishop(PieceColor color, int row, int col);
		~Bishop();
	};

	class Queen : public Piece
	{
	public:
		Queen() = default;
		Queen(PieceColor color, int row, int col);
		~Queen();
	};

	class King : public Piece
	{
	public:
		King() = default;
		King(PieceColor color, int row, int col);
		~King();
	};
}