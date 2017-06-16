
// Board.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Board.h"

using namespace std;

namespace Shatranj
{	
	Square::Square()
	{
		Initialize();
	}
	Square::Square(const Square& oSquare)
	{
		*this = oSquare;
	}
	Square::~Square()
	{
		Reset();
	}
	Square& Square::operator=(const Square& oSquare)
	{
		m_iRank = oSquare.m_iRank;
		m_iFile = oSquare.m_iFile;
		m_poPiece = oSquare.m_poPiece;
		return *this;
	}
	void Square::Reset()
	{
		Initialize();
	}
	int Square::GetFile() const
	{
		return m_iFile;
	}
	int Square::GetRank() const
	{
		return m_iRank;
	}
	Piece* Square::GetPiece() const
	{
		return m_poPiece;
	}
	void Square::SetFile(const int& iFile)
	{
		m_iFile = iFile;
	}
	void Square::SetRank(const int& iRank)
	{
		m_iRank = iRank;
	}
	bool Square::CapturePiece(Piece* poNewPiece)
	{
		if(m_poPiece == 0)		return false;
		if(poNewPiece == 0)		return false;
		m_poPiece = poNewPiece;
		return true;
	}
	bool Square::PutPiece(Piece* poPiece)
	{
		if(m_poPiece == 0)
		{
			m_poPiece = poPiece;
			return true;
		}
		return false;
	}
	bool Square::MovePiece()
	{
		if(m_poPiece != 0)
		{
			m_poPiece = 0;
			return true;
		}
		return false;
	}
	bool Square::IsEmpty() const
	{
		return (m_poPiece == 0);
	}
	bool Square::IsWhite() const
	{
		// white squares are the ones with odd ranks and even files or even ranks and odd files
		bool bIsOddFile = (m_iFile%2 != 0);
		bool bIsOddRank = (m_iRank%2 != 0);
		if(bIsOddRank)		return (!bIsOddFile);
		else				return (bIsOddFile);
	}
	bool Square::IsBlack() const
	{
		return (!IsWhite());
	}
	void Square::Initialize()
	{
		m_iRank = 0;
		m_iFile = 0;
		m_poPiece = 0;
	}

	Board::Board()
	{
		Initialize();
	}
	Board::Board(const Board& oBoard)
	{
		*this = oBoard;
	}
	Board::~Board()
	{
		Reset();
	}
	Board& Board::operator=(const Board& oBoard)
	{
		// do nothing, this operator cannot be called
		return *this;
	}
	void Board::Reset()
	{
		// the board owns its squares
		ClearBoard();	
		m_bIsWhiteCheck = false;
		m_bIsBlackCheck = false;
	}
	Square* Board::GetSquare(const int& iRank,const int& iFile) const
	{
		if(iRank < 1)			return 0;
		if(iRank > 8)			return 0;
		if(iFile < 1)			return 0;
		if(iFile > 8)			return 0;
		return m_vpoSquares[iRank*8 + iFile];
	}
	bool Board::IsWhiteInCheck() const
	{
		return m_bIsWhiteCheck;
	}
	bool Board::IsBlackInCheck() const
	{
		return m_bIsBlackCheck;
	}
	void Board::ApplyMove(Move* poMove)
	{
		// the move is guaranteed to be legal, no need to check it, add it unless it does not exist
		if(poMove != 0)			m_lpoMoves.push_back(poMove);
	}
	Move* Board::GetLastMove() const
	{
		if(m_lpoMoves.empty())		return 0;
		return m_lpoMoves.back();
	}
	void Board::Initialize()
	{
		// clear any existing squares
		ClearBoard();
		// build the board
		BuildBoard();
		m_bIsWhiteCheck = false;
		m_bIsBlackCheck = false;
	}
	void Board::ClearBoard()
	{
		unsigned int i = 0;
		unsigned int iSize = (unsigned int)m_vpoSquares.size();
		for(i = 0 ; i < iSize ; i++)
		{
			if(m_vpoSquares[i] != 0)		delete m_vpoSquares[i];
		}
		m_vpoSquares.clear();
		list<Move*>::iterator liMoves;
		for(liMoves = m_lpoMoves.begin() ; liMoves != m_lpoMoves.end() ; liMoves++)
		{
			if((*liMoves) != 0)			delete (*liMoves);
		}
		m_lpoMoves.clear();
	}
	void Board::BuildBoard()
	{
		// this function assumes that the board has been cleared before making any calls to it
		m_vpoSquares.resize(64);
		int i = 0;
		int j = 0;
		unsigned int iIndex = 0;
		Square* poSquare = 0;
		for(i = 1 ; i <= 8 ; i++)
		{
			for(j = 1 ; j <= 8 ; j++)
			{
				poSquare = new Square;
				poSquare->SetRank(i);
				poSquare->SetFile(j);
				m_vpoSquares[iIndex] = poSquare;
				iIndex++;
			}
		}
	}
}

