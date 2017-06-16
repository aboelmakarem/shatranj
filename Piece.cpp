
// Piece.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Piece.h"
#include "Move.h"
#include "Board.h"
#include "stdlib.h"

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
			m_iMoveCount = oPiece.m_iMoveCount;
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
	bool Piece::HasMoved() const
	{
		return (m_iMoveCount == 0);
	}
	void Piece::SetSquare(Square* poSquare)
	{
		m_poSquare = poSquare;
		m_poSquare->PutPiece(this);
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
	void Piece::ApplyMove(Move* poMove)
	{
		// the move is assumed to be legal and valid
		m_iMoveCount++;
	}
	unsigned int Piece::GetMoveCount() const
	{
		return m_iMoveCount;
	}
	void Piece::Initialize()
	{
		m_bIsFree = true;
		m_bIsWhite = true;
		m_poSquare = 0;
		m_iMoveCount = 0;
	}
	bool Piece::IsSquareOurs(Square* poSquare) const
	{
		if(poSquare == 0)			return false;
		if(poSquare->IsEmpty())		return false;
		bool bSquareHasWhite = poSquare->GetPiece()->IsWhite();
		if(m_bIsWhite && bSquareHasWhite)			return true;
		if((!m_bIsWhite) && (!bSquareHasWhite))		return true;
		return false;
	}

	King::King()
	{
		Initialize();
	}
	King::King(const King& oKing)
	{
		*this = oKing;
	}
	King::King(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return KingPiece;
	}
	void King::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string King::GetSymbol() const
	{
		if(m_bIsWhite)		return "WKG";
		return "BKG";
	}
	void King::Initialize()
	{
		Piece::Initialize();
	}
	void King::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// the king has up to 8 legal moves plus castling
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		Square* poSquare = 0;
		unsigned int i = 0;
		unsigned int iSize = 8;
		int piRankSteps[8] = {1,-1,0,0,1,1,-1,-1};
		int piFileSteps[8] = {0,0,1,-1,1,-1,1,-1};
		Move* poMove = 0;
		for(i = 0 ; i < iSize ; i++)
		{
			poSquare = poBoard->GetSquare(iMyRank + piRankSteps[i],iMyFile + piFileSteps[i]);
			if(poSquare != 0)
			{
				if(!IsSquareOurs(poSquare))
				{
					// the square is not ours, then we can move to it, create the move
					poMove = new Move((Piece*)this,m_poSquare,poSquare);
					// if the square is not empty, then it is a capture move, mark it as such
					if(!poSquare->IsEmpty())		poMove->MakeCapture();
					lpoMoves.push_back(poMove);
				}
			}	
		}
		// handle castling, we have up to 2 castling moves, this has to be the first move for the king
		// and the king cannot be in check
		if(poBoard->IsWhiteInCheck() && m_bIsWhite)			return;
		if(poBoard->IsBlackInCheck() && (!m_bIsWhite))		return;
		if(m_iMoveCount == 0)
		{
			// look at the squares containing the rooks and see whether their rooks
			// 1. are still on the squares or not
			// 2. have moved previously or not
			// examine near castle
			poSquare = poBoard->GetSquare(iMyRank,8);
			Piece* poCastlePiece = 0;
			Move* poMove = 0;
			if(poSquare != 0)
			{
				if(!poSquare->IsEmpty())
				{
					poCastlePiece = poSquare->GetPiece();
					if(poCastlePiece->GetType() == RookPiece)
					{
						if(!poCastlePiece->HasMoved())
						{
							// now we can castle only if the squares in between the two pieces are all empty
							if(poBoard->GetSquare(iMyRank,6)->IsEmpty())
							{
								if(poBoard->GetSquare(iMyRank,7)->IsEmpty())
								{
									// all conditions satisfied, create the move
									poMove = new Move((Piece*)this,m_poSquare,poBoard->GetSquare(iMyRank,7));
									poMove->MakeCastle();
									lpoMoves.push_back(poMove);
								}
							}
						}
					}
				}
			}
			// examine far castle
			poSquare = poBoard->GetSquare(iMyRank,1);
			if(poSquare != 0)
			{
				if(!poSquare->IsEmpty())
				{
					poCastlePiece = poSquare->GetPiece();
					if(poCastlePiece->GetType() == RookPiece)
					{
						if(!poCastlePiece->HasMoved())
						{
							// now we can castle only if the squares in between the two pieces are all empty
							if(poBoard->GetSquare(iMyRank,4)->IsEmpty())
							{
								if(poBoard->GetSquare(iMyRank,3)->IsEmpty())
								{
									if(poBoard->GetSquare(iMyRank,2)->IsEmpty())
									{
										// all conditions satisfied, create the move
										poMove = new Move((Piece*)this,m_poSquare,poBoard->GetSquare(iMyRank,3));
										poMove->MakeCastle();
										lpoMoves.push_back(poMove);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	Queen::Queen()
	{
		Initialize();
	}
	Queen::Queen(const Queen& oQueen)
	{
		*this = oQueen;
	}
	Queen::Queen(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return QueenPiece;
	}
	void Queen::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string Queen::GetSymbol() const
	{
		if(m_bIsWhite)		return "WQN";
		return "BQN";
	}
	void Queen::Initialize()
	{
		Piece::Initialize();
	}
	void Queen::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// the queen has up to 27 legal moves
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		Square* poSquare = 0;
		// move forward
		int i = 0;
		Move* poMove = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move backward
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move right
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move front right
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move front left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move back right
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move back left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
	}

	Rook::Rook()
	{
		Initialize();
	}
	Rook::Rook(const Rook& oRook)
	{
		*this = oRook;
	}
	Rook::Rook(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return RookPiece;
	}
	void Rook::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string Rook::GetSymbol() const
	{
		if(m_bIsWhite)		return "WRK";
		return "BRK";
	}
	void Rook::Initialize()
	{
		Piece::Initialize();
	}
	void Rook::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// the rook has 14 legal moves
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		Square* poSquare = 0;
		// move forward
		int i = 0;
		Move* poMove = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move backward
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move right
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
	}

	Knight::Knight()
	{
		Initialize();
	}
	Knight::Knight(const Knight& oKnight)
	{
		*this = oKnight;
	}
	Knight::Knight(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return KnightPiece;
	}
	void Knight::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string Knight::GetSymbol() const
	{
		if(m_bIsWhite)		return "WKT";
		return "BKT";
	}
	void Knight::Initialize()
	{
		Piece::Initialize();
	}
	void Knight::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// the knight has 8 legal moves and is not obstructed by other pieces
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		Square* poSquare = 0;
		unsigned int i = 0;
		unsigned int iSize = 8;
		int piRankSteps[8] = {2,2,-2,-2,1,1,-1,-1};
		int piFileSteps[8] = {1,-1,1,-1,2,-2,2,-2};
		Move* poMove = 0;
		for(i = 0 ; i < iSize ; i++)
		{
			poSquare = poBoard->GetSquare(iMyRank + piRankSteps[i],iMyFile + piFileSteps[i]);
			if(poSquare != 0)
			{
				if(!IsSquareOurs(poSquare))
				{
					// the square is not ours, then we can move to it, create the move
					poMove = new Move((Piece*)this,m_poSquare,poSquare);
					// if the square is not empty, then it is a capture move, mark it as such
					if(!poSquare->IsEmpty())		poMove->MakeCapture();
					lpoMoves.push_back(poMove);
				}
			}	
		}
	}

	Bishop::Bishop()
	{
		Initialize();
	}
	Bishop::Bishop(const Bishop& oBishop)
	{
		*this = oBishop;
	}
	Bishop::Bishop(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return BishopPiece;
	}
	void Bishop::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string Bishop::GetSymbol() const
	{
		if(m_bIsWhite)		return "WBP";
		return "BBP";
	}
	void Bishop::Initialize()
	{
		Piece::Initialize();
	}
	void Bishop::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// the bishop has up to 13 legal moves
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		Square* poSquare = 0;
		// move front right
		int i = 0;
		Move* poMove = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move front left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank + i,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move back right
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile + i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
		// move back left
		i = 0;
		while(true)
		{
			poSquare = poBoard->GetSquare(iMyRank - i,iMyFile - i);
			// if the square does not exist, stop
			if(poSquare == 0)			break;
			// if the square contains a piece that is ours, stop
			if(IsSquareOurs(poSquare))	break;
			// now we have a square that exists and either is empty or contains an enemy piece, add
			// a move to it regardless
			poMove = new Move((Piece*)this,m_poSquare,poSquare);
			lpoMoves.push_back(poMove);
			// if it happens to contain an enemy piece, then we are done, mark the move as a capture
			if(!poSquare->IsEmpty())
			{
				poMove->MakeCapture();
				break;	
			};
			i++;
		}
	}

	Pawn::Pawn()
	{
		Initialize();
	}
	Pawn::Pawn(const Pawn& oPawn)
	{
		*this = oPawn;
	}
	Pawn::Pawn(Square* poSquare,const bool& bIsWhite)
	{
		Initialize();
		m_bIsWhite = bIsWhite;
		SetSquare(poSquare);
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
		return PawnPiece;
	}
	void Pawn::GetAllMoves(Board* poBoard,list<Move*> lpoMoves) const
	{

	}
	string Pawn::GetSymbol() const
	{
		if(m_bIsWhite)		return "WPN";
		return "BPN";
	}
	void Pawn::Initialize()
	{
		Piece::Initialize();
	}
	void Pawn::GetAllLegalMoves(Board* poBoard,list<Move*> lpoMoves) const
	{
		// a pawn has at most 4 basic moves in addition to en-passant capturing and promotions
		// also a pawn moves only forward, so the color of the pawn makes a difference
		int iMyRank = m_poSquare->GetRank();
		int iMyFile = m_poSquare->GetFile();
		int iMoveDirection = 1;
		if(!m_bIsWhite)		iMoveDirection = -1;
		Square* poSquare = 0;
		// add the basic move
		poSquare = poBoard->GetSquare(iMyRank + iMoveDirection,iMyFile);
		if(poSquare != 0)
		{
			// we have a square but it has to be empty for the pawn to move to it
			if(poSquare->IsEmpty())		lpoMoves.push_back(new Move((Piece*)this,m_poSquare,poSquare));
		}
		// if this is the first move for the pawn, it can jump 2 squares ahead
		if(m_iMoveCount == 0)
		{
			poSquare = poBoard->GetSquare(iMyRank + 2*iMoveDirection,iMyFile);
			if(poSquare != 0)
			{
				// we have a square but it has to be empty for the pawn to move to it
				// also the square before it needs to be empty
				if(poBoard->GetSquare(iMyRank + iMoveDirection,iMyFile)->IsEmpty())
				{
					if(poSquare->IsEmpty())		lpoMoves.push_back(new Move((Piece*)this,m_poSquare,poSquare));
				}
			}
		}
		// generate the diagonal capturing moves, the target square has to have an enemy piece
		poSquare = poBoard->GetSquare(iMyRank + iMoveDirection,iMyFile + 1);
		Move* poThisMove = 0;
		bool bMoveExists = false;
		if(poSquare != 0)
		{
			if(!poSquare->IsEmpty())
			{
				if(poSquare->GetPiece()->IsWhite() && (!m_bIsWhite))	bMoveExists = true;
				if((!poSquare->GetPiece()->IsWhite()) && m_bIsWhite)	bMoveExists = true;
				if(bMoveExists)
				{
					poThisMove = new Move((Piece*)this,m_poSquare,poSquare);
					poThisMove->MakeCapture();
					lpoMoves.push_back(poThisMove);
				}
			}
		}
		poSquare = poBoard->GetSquare(iMyRank + iMoveDirection,iMyFile - 1);
		bMoveExists = false;
		if(poSquare != 0)
		{
			if(!poSquare->IsEmpty())
			{
				if(poSquare->GetPiece()->IsWhite() && (!m_bIsWhite))	bMoveExists = true;
				if((!poSquare->GetPiece()->IsWhite()) && m_bIsWhite)	bMoveExists = true;
				if(bMoveExists)
				{
					poThisMove = new Move((Piece*)this,m_poSquare,poSquare);
					poThisMove->MakeCapture();
					lpoMoves.push_back(poThisMove);
				}
			}
		}
		// generate the en-passant moves
		Move* poLastMove = poBoard->GetLastMove();
		if(poLastMove != 0)
		{
			Piece* poEnemyPiece = poLastMove->GetPiece();
			if(poEnemyPiece->GetType() == PawnPiece)
			{
				// the last move was made by an enemy pawn, see if it was:
				// 1. the first move done by that pawn
				if(poEnemyPiece->GetMoveCount() == 1)
				{
					// 2. a 2 square move
					if(abs(poLastMove->GetToSquare()->GetRank() - poLastMove->GetFromSquare()->GetRank()) == 2)
					{
						// finally, make sure that the enemy pawn ended right next to this piece
						if(poEnemyPiece->GetSquare()->GetRank() == iMyRank)
						{
							if(abs(poEnemyPiece->GetSquare()->GetFile() - iMyFile) == 1)
							{
								// that's it, we have a possible en-passant move
								poThisMove = new Move((Piece*)this,m_poSquare,poBoard->GetSquare(iMyRank + iMoveDirection,poEnemyPiece->GetSquare()->GetFile()));
								poThisMove->MakeEnPassant();
								lpoMoves.push_back(poThisMove);
							}
						}
					}
				}				
			}
		}
	}
}

