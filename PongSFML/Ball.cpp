#include "assert.h"
#include "Ball.h"

void Ball::moveBall(sf::Sprite& Ball)
{
	Ball.move(ballSpeed.x, ballSpeed.y);
}

sf::Sprite Ball::createBall()
{
	if (!pongBall.loadFromFile("pongBall.png"))	assert(false);
	sf::Sprite Ball(pongBall);
	Ball.setScale(1.5, 1.5);
	pongBall.setSmooth(true);
	return Ball;
}

sf::Sprite Ball::getBall()
{
	return createBall();
}

void Ball::SpeedofBall()
{
	ballSpeed.x = 6.1f; ballSpeed.y = 6.f;
}

Ball::~Ball()
{}