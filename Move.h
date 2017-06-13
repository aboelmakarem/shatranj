
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

