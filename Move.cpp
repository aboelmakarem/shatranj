

// Move.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Move.h"

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

