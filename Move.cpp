

// Move.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Move.h"
#include "Board.h"
#include "Piece.h"

namespace Shatranj
{
	Move::Move()
	{
		Initialize();
	}
	Move::Move(const Move& oMove)
	{
		*this = oMove;
	}
	Move::Move(Piece* poPiece,Square* poFromSquare,Square* poToSquare)
	{
		Initialize();
		m_poPiece = poPiece;
		m_poFromSquare = poFromSquare;
		m_poToSquare = poToSquare;
	}
	Move::~Move()
	{
		Reset();
	}
	Move& Move::operator=(const Move& oMove)
	{
		m_poPiece = oMove.m_poPiece;
		m_poFromSquare = oMove.m_poFromSquare;
		m_poToSquare = oMove.m_poToSquare;
		m_bIsCapture = oMove.m_bIsCapture;
		m_bIsCastle = oMove.m_bIsCastle;
		m_bIsPromotion = oMove.m_bIsPromotion;
		m_bIsEnPassant = oMove.m_bIsEnPassant;
		return *this;
	}
	void Move::Reset()
	{
		Initialize();
	}
	void Move::SetPiece(Piece* poPiece)
	{
		m_poPiece = poPiece;
	}
	void Move::SetFromSquare(Square* poSquare)
	{
		m_poFromSquare = poSquare;
	}
	void Move::SetToSquare(Square* poSquare)
	{
		m_poToSquare = poSquare;
	}
	void Move::MakeCapture()
	{
		m_bIsCapture = true;
		m_bIsCastle = false;
		m_bIsPromotion = false;
	}
	void Move::MakeCastle()
	{
		m_bIsCapture = false;
		m_bIsCastle = true;
		m_bIsPromotion = true;
		m_bIsEnPassant = false;
	}
	void Move::MakePromotion()
	{
		m_bIsCapture = false;
		m_bIsCastle = false;
		m_bIsPromotion = true;
		m_bIsEnPassant = false;
	}
	void Move::MakeEnPassant()
	{
		m_bIsCapture = true;
		m_bIsCastle = false;
		m_bIsPromotion = false;
		m_bIsEnPassant = true;
	}
	Piece* Move::GetPiece() const
	{
		return m_poPiece;
	}
	Square* Move::GetFromSquare() const
	{
		return m_poFromSquare;
	}
	Square* Move::GetToSquare() const
	{
		return m_poToSquare;
	}
	bool Move::IsCapture() const
	{
		return m_bIsCapture;
	}
	bool Move::IsCastle() const
	{
		return m_bIsCastle;
	}
	bool Move::IsPromotion() const
	{
		return m_bIsPromotion;
	}
	bool Move::IsEnPassant() const
	{
		return m_bIsEnPassant;
	}
	void Move::Initialize()
	{
		m_poPiece = 0;
		m_poFromSquare = 0;
		m_poToSquare = 0;
		m_bIsCapture = false;
		m_bIsCastle = false;
		m_bIsPromotion = false;
		m_bIsEnPassant = false;	
	}
}

