
// Board.cpp
// June 13th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Board.h"
#include "Piece.h"

using namespace std;

namespace Shatranj
{
	Location::Location()
	{
		Initialize();
	}
	Location::Location(const Location& oLocation)
	{
		*this = oLocation;
	}
	Location::~Location()
	{
		Reset();
	}
	Location& Location::operator=(const Location& oLocation)
	{
		m_eFile = oLocation.m_eFile;
		m_iRank = oLocation.m_iRank;
		return *this;
	}
	void Location::Reset()
	{
		Initialize();
	}
	File Location::GetFile() const
	{
		return m_eFile;
	}
	unsigned int Location::GetRank() const
	{
		return m_iRank;
	}
	void Location::SetFile(const File& eFile)
	{
		m_eFile = eFile;
	}
	void Location::SetRank(const unsigned int& iRank)
	{
		m_iRank = iRank;
	}
	Location Location::GetFront() const
	{
		Location oResult(*this);
		if(m_iRank < 8)			oResult.m_iRank++;
		return oResult;
	}
	Location Location::GetBack() const
	{
		Location oResult(*this);
		if(m_iRank > 0)			oResult.m_iRank--;
		return oResult;
	}
	Location Location::GetLeft() const
	{
		Location oResult(*this);
		if(m_eFile == B)			oResult.m_eFile = A;
		if(m_eFile == C)			oResult.m_eFile = B;
		if(m_eFile == D)			oResult.m_eFile = C;
		if(m_eFile == E)			oResult.m_eFile = D;
		if(m_eFile == F)			oResult.m_eFile = E;
		if(m_eFile == G)			oResult.m_eFile = F;
		if(m_eFile == H)			oResult.m_eFile = G;
		return oResult;
	}
	Location Location::GetRight() const
	{
		Location oResult(*this);
		if(m_eFile == A)			oResult.m_eFile = B;
		if(m_eFile == B)			oResult.m_eFile = C;
		if(m_eFile == C)			oResult.m_eFile = D;
		if(m_eFile == D)			oResult.m_eFile = E;
		if(m_eFile == E)			oResult.m_eFile = F;
		if(m_eFile == F)			oResult.m_eFile = G;
		if(m_eFile == G)			oResult.m_eFile = H;
		return oResult;
	}
	void Location::Initialize()
	{
		m_eFile = NullFile;
		m_iRank = 0;
	}
	
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
		m_oLocation = oSquare.m_oLocation;
		m_poPiece = oSquare.m_poPiece;
		return *this;
	}
	void Square::Reset()
	{
		Initialize();
	}
	File Square::GetFile() const
	{
		return m_oLocation.GetFile();
	}
	unsigned int Square::GetRank() const
	{
		return m_oLocation.GetRank();
	}
	Piece* Square::GetPiece() const
	{
		return m_poPiece;
	}
	void Square::SetFile(const File& eFile)
	{
		m_oLocation.SetFile(eFile);
	}
	void Square::SetRank(const unsigned int& iRank)
	{
		m_oLocation.SetRank(iRank);
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
		File eFile = m_oLocation.GetFile();
		unsigned int iRank = m_oLocation.GetRank();
		bool bIsFileACEG = (eFile == A) || (eFile == C) || (eFile == E) || (eFile == G);
		bool bIsRank1357 = (iRank == 1) || (iRank == 3) || (iRank == 5) || (iRank == 7);
		if(bIsRank1357)		return (!bIsFileACEG);
		else				return (bIsFileACEG);
	}
	bool Square::IsBlack() const
	{
		return (!IsWhite());
	}
	void Square::Initialize()
	{
		m_oLocation.Reset();
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
	}
	Square* Board::GetSquare(const unsigned int& iRank,const File& iFile) const
	{
		return m_vpoSquares[iRank*8 + (unsigned int)iFile];
	}
	void Board::Initialize()
	{
		// clear any existing squares
		ClearBoard();
		// build the board
		BuildBoard();
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
	}
	void Board::BuildBoard()
	{
		// this function assumes that the board has been cleared before making any calls to it
		m_vpoSquares.resize(64);
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int iIndex = 0;
		Square* poSquare = 0;
		for(i = 1 ; i <= 8 ; i++)
		{
			for(j = 1 ; j <= 8 ; j++)
			{
				poSquare = new Square;
				poSquare->SetRank(i);
				poSquare->SetFile((File)j);
				m_vpoSquares[iIndex] = poSquare;
				iIndex++;
			}
		}
	}
}

