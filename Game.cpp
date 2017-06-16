
// Game.cpp
// June 16th, 2017
// Ahmed Hussein (amhussein4@gmail.com)

#include "Game.h"

using namespace Shatranj;

namespace Shatranj
{
	Game::Game()
	{
		Initialize();
	}
	Game::Game(const Game& oGame)
	{
		*this = oGame;
	}
	Game::~Game()
	{
		Reset();
	}
	Game& Game::operator=(const Game& oGame)
	{
		return *this;
	}
	void Game::Reset()
	{
		Initialize();
	}
	void Game::Initialize()
	{

	}
}

int main(int argc,char** argv)
{
	Board oBoard;
	oBoard.GenerateInitialState();
	oBoard.Show();
	return 0;
}

