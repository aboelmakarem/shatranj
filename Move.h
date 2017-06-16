
// Move.h
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef MOVE_H_
#define MOVE_H_

namespace Shatranj
{
	class Square;
	class Piece;
	class Move
	{
	public:		
		Move();
		Move(const Move& oMove);
		Move(Piece* poPiece,Square* poFromSquare,Square* poToSquare);
		~Move();
		Move& operator=(const Move& oMove);
		void Reset();
		void SetPiece(Piece* poPiece);
		void SetFromSquare(Square* poSquare);
		void SetToSquare(Square* poSquare);
		void MakeCapture();
		void MakeCastle();
		void MakePromotion();
		void MakeEnPassant();
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

