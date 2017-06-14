
// Piece.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef PIECE_H_
#define PIECE_H_

#include "Board.h"
#include "list"

namespace Shatranj
{
	class Move;
	enum PieceType
	{
		NullPieceType = 0,
		TheKing = 1,
		TheQueen = 2,
		RightRook = 3,
		LeftRook = 4,
		RightKnight = 5,
		LeftKnight = 6,
		RightBishop = 7,
		LeftBishop = 8,
		Pawn1 = 9,
		Pawn2 = 10,
		Pawn3 = 11,
		Pawn4 = 12,
		Pawn5 = 13,
		Pawn6 = 14,
		Pawn7 = 15,
		Pawn8 = 16
	};

	class Piece
	{
	public:
		Piece();
		Piece(const Piece& oPiece);
		~Piece();
		Piece& operator=(const Piece& oPiece);
		void Reset();
		Square* GetSquare() const;
		bool IsFree() const;
		bool IsWhite() const;
		bool IsBlack() const;
		virtual PieceType GetType() const = 0;
		void SetSquare(Square* poSquare);
		void Capture();
		void SetWhite();
		void SetBlack();
		virtual void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const = 0;

	private:

	protected:
		void Initialize();
		virtual void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const = 0;
		bool m_bIsFree;
		bool m_bIsWhite;
		bool m_bHasMoved;
		Square* m_poSquare;
	};

	class King : public Piece
	{
	public:
		King();
		King(const King& oKing);
		~King();
		King& operator=(const King& oKing);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
	};

	class Queen : public Piece
	{
	public:
		Queen();
		Queen(const Queen& oQueen);
		~Queen();
		Queen& operator=(const Queen& oQueen);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
	};

	class Rook : public Piece
	{
	public:
		Rook();
		Rook(const Rook& oRook);
		~Rook();
		Rook& operator=(const Rook& oRook);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		void SetRight();
		void SetLeft();
		
	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		bool m_bIsRight;
	};

	class Knight : public Piece
	{
	public:
		Knight();
		Knight(const Knight& oKnight);
		~Knight();
		Knight& operator=(const Knight& oKnight);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		void SetRight();
		void SetLeft();

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		bool m_bIsRight;
	};

	class Bishop : public Piece
	{
	public:
		Bishop();
		Bishop(const Bishop& oBishop);
		~Bishop();
		Bishop& operator=(const Bishop& oBishop);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		void SetRight();
		void SetLeft();
		
	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		bool m_bIsRight;
	};

	class Pawn : public Piece
	{
	public:
		Pawn();
		Pawn(const Pawn& oPawn);
		~Pawn();
		Pawn& operator=(const Pawn& oPawn);
		void Reset();
		PieceType GetType() const;
		void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		void SetID(const unsigned int& iID);

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
		unsigned int m_iPawnID;
	};
}

#endif

