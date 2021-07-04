#pragma once
#include "GameData.h"

class GameApplication
{
public:
	enum states
	{
		STARTING_STATE,
		GAME_STATE,
		QUIT_STATE
	};
	void init(GameApplication& game);
	void run(GameApplication& game, GameData& gdata);
private:
	int gameState;
};