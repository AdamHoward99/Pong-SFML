#pragma once
#include "GameData.h"
#include "Ball.h"
#include "Court.h"
#include "Player.h"
#include "Score.h"

class GameObject
{
public:
	Ball ball_;
	Court court;
	Player players;
	Score score_;
	GameData gdata;
	~GameObject();

	//Creating the top and bottom borders of the game
	sf::Sprite topBorder = court.getTopBorder();
	sf::Sprite bottomBorder = court.getBottomBorder();

	//Creating the ball
	sf::Sprite Ball = ball_.getBall();

	//Creating Player 1
	sf::Sprite p1pad = players.getPlayer1();

	//Creating Player 2
	sf::Sprite p2pad = players.getPlayer2();

	//Displaying the score
	sf::Text score = score_.getScore();

	//Displaying the middle line
	sf::RectangleShape middleLine = court.getMiddleLine();
};