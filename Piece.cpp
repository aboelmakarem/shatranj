
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
		m_bIsRight = oRook.m_bIsRight;
		return *this;
	}
	void Rook::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Rook::GetType() const
	{
		if(m_bIsRight)		return RightRook;
		return LeftRook;
	}
	void Rook::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Rook::SetRight()
	{
		m_bIsRight = true;
	}
	void Rook::SetLeft()
	{
		m_bIsRight = false;
	}
	void Rook::Initialize()
	{
		Piece::Initialize();
		m_bIsRight = false;
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
		m_bIsRight = oKnight.m_bIsRight;
		return *this;
	}
	void Knight::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Knight::GetType() const
	{
		if(m_bIsRight)		return RightKnight;
		return LeftKnight;
	}
	void Knight::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Knight::SetRight()
	{
		m_bIsRight = true;
	}
	void Knight::SetLeft()
	{
		m_bIsRight = false;
	}
	void Knight::Initialize()
	{
		Piece::Initialize();
		m_bIsRight = false;
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
		m_bIsRight = oBishop.m_bIsRight;
		return *this;
	}
	void Bishop::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Bishop::GetType() const
	{
		if(m_bIsRight)		return RightBishop;
		return LeftBishop;
	}
	void Bishop::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Bishop::SetRight()
	{
		m_bIsRight = true;
	}
	void Bishop::SetLeft()
	{
		m_bIsRight = false;
	}
	void Bishop::Initialize()
	{
		Piece::Initialize();
		m_bIsRight = false;
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
		m_iPawnID = oPawn.m_iPawnID;
		return *this;
	}
	void Pawn::Reset()
	{
		Piece::Reset();
		Initialize();
	}
	PieceType Pawn::GetType() const
	{
		if(m_iPawnID == 1)			return Pawn1;
		if(m_iPawnID == 2)			return Pawn2;
		if(m_iPawnID == 3)			return Pawn3;
		if(m_iPawnID == 4)			return Pawn4;
		if(m_iPawnID == 5)			return Pawn5;
		if(m_iPawnID == 6)			return Pawn6;
		if(m_iPawnID == 7)			return Pawn7;
		if(m_iPawnID == 8)			return Pawn8;
		return NullPieceType;
	}
	void Pawn::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	void Pawn::SetID(const unsigned int& iID)
	{
		m_iPawnID = iID;
	}
	void Pawn::Initialize()
	{
		Piece::Initialize();
		m_iPawnID = 0;
	}
	void Pawn::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
}

