
// Piece.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef PIECE_H_
#define PIECE_H_

#include "list"

namespace Shatranj
{
	class Square;
	class Board;
	class Move;
	enum PieceType
	{
		NullPieceType = 0,
		KingPiece = 1,
		QueenPiece = 2,
		RookPiece = 3,
		KnightPiece = 4,
		BishopPiece = 5,
		PawnPiece = 6
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
		bool HasMoved() const;
		virtual PieceType GetType() const = 0;
		void SetSquare(Square* poSquare);
		void Capture();
		void SetWhite();
		void SetBlack();
		void ApplyMove(Move* poMove);
		virtual void GetAllMoves(Board* poBoard,std::list<Move*> lpoMoves) const = 0;
		unsigned int GetMoveCount() const;
		
	private:

	protected:
		void Initialize();
		virtual void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const = 0;
		bool IsSquareOurs(Square* poSquare) const;
		bool m_bIsFree;
		bool m_bIsWhite;
		unsigned int m_iMoveCount;
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
		
	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
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

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
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
		
	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
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

	private:

	protected:
		void Initialize();
		void GetAllLegalMoves(Board* poBoard,std::list<Move*> lpoMoves) const;
	};
}

#endif

