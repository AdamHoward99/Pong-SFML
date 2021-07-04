#pragma once
#include "GameData.h"

class Score
{
public:
	void displayScore(GameData& gdata, sf::Text score);
	sf::Text getScore();
	~Score();
private:
	sf::Text initialiseScore();
	GameData gdata;
};