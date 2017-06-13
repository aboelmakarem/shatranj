
// Piece.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Piece.h"

using namespace std;

namespace Shatranj
{
	Piece::Piece()
	{
		Initialize();
	}
	Piece::Piece(const Piece& oPiece)
	{
		*this = oPiece;
	}
	Piece::~Piece()
	{
		Reset();
	}
	Piece& Piece::operator=(const Piece& oPiece)
	{
		if(GetType() == oPiece.GetType())
		{
			m_bIsFree = oPiece.m_bIsFree;
			m_bIsWhite = oPiece.m_bIsWhite;
			m_poSquare = oPiece.m_poSquare;
			m_bHasMoved = oPiece.m_bHasMoved;
		}
		return *this;
	}
	void Piece::Reset()
	{
		Initialize();
	}
	Square* Piece::GetSquare() const
	{
		return m_poSquare;
	}
	bool Piece::IsFree() const
	{
		return m_bIsFree;
	}
	bool Piece::IsWhite() const
	{
		return m_bIsWhite;
	}
	bool Piece::IsBlack() const
	{
		return (!m_bIsWhite);
	}
	void Piece::SetSquare(Square* poSquare)
	{
		m_poSquare = poSquare;
	}
	void Piece::Capture()
	{
		m_bIsFree = true;
	}
	void Piece::SetWhite()
	{
		m_bIsWhite = true;
	}
	void Piece::SetBlack()
	{
		m_bIsWhite = false;
	}
	void Piece::Initialize()
	{
		m_bIsFree = true;
		m_bIsWhite = true;
		m_poSquare = 0;
		m_bHasMoved = false;
	}

	King::King()
	{
		Initialize();
	}
	King::King(const King& oKing)
	{
		*this = oKing;
	}
	King::~King()
	{
		Reset();
	}
	King& King::operator=(const King& oKing)
	{
		Piece::operator=(oKing);
		return *this;
	}
	void King::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType King::GetType() const
	{
		return TheKing;
	}
	void King::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void King::Initialize()
	{
		Piece::Initialize();
	}
	void King::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}

	Queen::Queen()
	{
		Initialize();
	}
	Queen::Queen(const Queen& oQueen)
	{
		*this = oQueen;
	}
	Queen::~Queen()
	{
		Reset();
	}
	Queen& Queen::operator=(const Queen& oQueen)
	{
		Piece::operator=(oQueen);
		return *this;
	}
	void Queen::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Queen::GetType() const
	{
		return TheQueen;
	}
	void Queen::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Queen::Initialize()
	{
		Piece::Initialize();
	}
	void Queen::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}

	Rook::Rook()
	{
		Initialize();
	}
	Rook::Rook(const Rook& oRook)
	{
		*this = oRook;
	}
	Rook::~Rook()
	{
		Reset();
	}
	Rook& Rook::operator=(const Rook& oRook)
	{
		Piece::operator=(oRook);
		return *this;
	}
	void Rook::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Rook::GetType() const
	{

	}
	void Rook::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Rook::Initialize()
	{
		Piece::Initialize();
	}
	void Rook::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}

	Knight::Knight()
	{
		Initialize();
	}
	Knight::Knight(const Knight& oKnight)
	{
		*this = oKnight;
	}
	Knight::~Knight()
	{
		Reset();
	}
	Knight& Knight::operator=(const Knight& oKnight)
	{
		Piece::operator=(oKnight);
		return *this;
	}
	void Knight::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Knight::GetType() const
	{

	}
	void Knight::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Knight::Initialize()
	{
		Piece::Initialize();
	}
	void Knight::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}

	Bishop::Bishop()
	{
		Initialize();
	}
	Bishop::Bishop(const Bishop& oBishop)
	{
		*this = oBishop;
	}
	Bishop::~Bishop()
	{
		Reset();
	}
	Bishop& Bishop::operator=(const Bishop& oBishop)
	{
		Piece::operator=(oBishop);
		return *this;
	}
	void Bishop::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Bishop::GetType() const
	{

	}
	void Bishop::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Bishop::Initialize()
	{
		Piece::Initialize();
	}
	void Bishop::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}

	Pawn::Pawn()
	{
		Initialize();
	}
	Pawn::Pawn(const Pawn& oPawn)
	{
		*this = oPawn;
	}
	Pawn::~Pawn()
	{
		Reset();
	}
	Pawn& Pawn::operator=(const Pawn& oPawn)
	{
		Piece::operator=(oPawn);
		return *this;
	}
	void Pawn::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Pawn::GetType() const
	{

	}
	void Pawn::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Pawn::Initialize()
	{
		Piece::Initialize();
	}
	void Pawn::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
}

