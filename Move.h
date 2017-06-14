
// Move.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef MOVE_H_
#define MOVE_H_

#include "Board.h"
#include "Piece.h"

namespace Shatranj
{
	class Move
	{
	public:		
		Move();
		Move(const Move& oMove);
		~Move();
		Move& operator=(const Move& oMove);
		void Reset();
		void SetPiece(Piece* poPiece);
		void SetFromSquare(Square* poSquare);
		void SetToSquare(Square* poSquare);
		Piece* GetPiece() const;
		Square* GetFromSquare() const;
		Square* GetToSquare() const;
		bool IsCapture() const;
		bool IsCastle() const;
		bool IsPromotion() const;
		bool IsEnPassant() const;

	private:

	protected:
		void Initialize();
		Piece* m_poPiece;
		Square* m_poFromSquare;
		Square* m_poToSquare;
		bool m_bIsCapture;
		bool m_bIsCastle;
		bool m_bIsPromotion;
		bool m_bIsEnPassant;
	};
}

#endif

