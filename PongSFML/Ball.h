#pragma once

#include "GameData.h"

class Ball
{
public:
	void SpeedofBall();
	Vec2f ballSpeed;
	void moveBall(sf::Sprite& Ball);
	sf::Sprite getBall();
	~Ball();
private:
	sf::Texture pongBall;
	sf::Sprite createBall();
};