#include "assert.h"
#include "Score.h"

sf::Text Score::initialiseScore()
{
	if (!gdata.font.loadFromFile("../bin/arcadeclassic.ttf"))		assert(false);
	gdata.text.setFont(gdata.font);
	sf::Text score("0    0", gdata.font, 100);
	score.setPosition(gdata.width / 2 - score.getGlobalBounds().width / 2, 10);
	return score;
}

sf::Text Score::getScore()
{
	return initialiseScore();
}

void Score::displayScore(GameData& gdata, sf::Text score)
{
	//Draw the score to the screen
	gdata.window.draw(score);
}

Score::~Score()
{}