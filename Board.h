
// Board.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef BOARD_H_
#define BOARD_H_

#include "vector"
#include "list"
#include "Move.h"
#include "Piece.h"

namespace Shatranj
{
	class Square
	{
	public:
		Square();
		Square(const Square& oSquare);
		~Square();
		Square& operator=(const Square& oSquare);
		void Reset();
		int GetFile() const;
		int GetRank() const;
		Piece* GetPiece() const;
		void SetFile(const int& iFile);
		void SetRank(const int& iRank);
		bool CapturePiece(Piece* poNewPiece);
		bool PutPiece(Piece* poPiece);
		bool MovePiece();
		bool IsEmpty() const;
		bool IsWhite() const;
		bool IsBlack() const;

	private:

	protected:
		void Initialize();
		int m_iRank;
		int m_iFile;
		Piece* m_poPiece;
	};

	class Board
	{
	public:
		Board();
		~Board();
		void Reset();
		Square* GetSquare(const int& iRank,const int& iFile) const;
		bool IsWhiteInCheck() const;
		bool IsBlackInCheck() const;
		void ApplyMove(Move* poMove);
		Move* GetLastMove() const;

	private:
		// do not copy or equate boards
		Board(const Board& oBoard);
		Board& operator=(const Board& oBoard);

	protected:
		void Initialize();
		void ClearBoard();
		void BuildBoard();
		std::vector<Square*> m_vpoSquares;
		bool m_bIsWhiteCheck;
		bool m_bIsBlackCheck;
		std::list<Move*> m_lpoMoves;
	};
}

#endif

