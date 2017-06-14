
// Board.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef BOARD_H_
#define BOARD_H_

#include "vector"

namespace Shatranj
{
	class Piece;
	enum File
	{
		NullFile = 0,
		A = 1,
		B = 2,
		C = 3,
		D = 4,
		E = 5,
		F = 6,
		G = 7,
		H = 8
	};

	class Location
	{
	public:
		Location();
		Location(const Location& oLocation);
		~Location();
		Location& operator=(const Location& oLocation);
		void Reset();
		File GetFile() const;
		unsigned int GetRank() const;
		void SetFile(const File& eFile);
		void SetRank(const unsigned int& iRank);
		Location GetFront() const;
		Location GetBack() const;
		Location GetLeft() const;
		Location GetRight() const;

	private:

	protected:
		void Initialize();
		File m_eFile;
		unsigned int m_iRank;
	};

	class Square
	{
	public:
		Square();
		Square(const Square& oSquare);
		~Square();
		Square& operator=(const Square& oSquare);
		void Reset();
		File GetFile() const;
		unsigned int GetRank() const;
		Piece* GetPiece() const;
		void SetFile(const File& eFile);
		void SetRank(const unsigned int& iRank);
		bool CapturePiece(Piece* poNewPiece);
		bool PutPiece(Piece* poPiece);
		bool MovePiece();
		bool IsEmpty() const;
		bool IsWhite() const;
		bool IsBlack() const;

	private:

	protected:
		void Initialize();
		Location m_oLocation;
		Piece* m_poPiece;
	};

	class Board
	{
	public:
		Board();
		~Board();
		void Reset();
		Square* GetSquare(const unsigned int& iRank,const File& iFile) const;

	private:
		// do not copy or equate boards
		Board(const Board& oBoard);
		Board& operator=(const Board& oBoard);

	protected:
		void Initialize();
		void ClearBoard();
		void BuildBoard();
		std::vector<Square*> m_vpoSquares;
	};
}

#endif

