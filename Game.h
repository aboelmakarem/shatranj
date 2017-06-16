
// Game.h
// June 16th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Piece.h"
#include "Move.h"

namespace Shatranj
{
	class Game
	{
	public:		
		Game();
		~Game();
		void Reset();

	private:
		Game(const Game& oGame);
		Game& operator=(const Game& oGame);

	protected:
		void Initialize();

	};
}

#endif

