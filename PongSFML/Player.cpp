#include "assert.h"
#include "Player.h"

sf::Sprite Player::createPlayer1()
{
	if (!paddle.loadFromFile("pongPlayer1Paddle.png"))	assert(false);
	sf::Sprite p1pad(paddle);
	p1pad.setPosition(gdata.margin - gdata.borderSize - 10, gdata.height / 2 - 25);
	p1pad.setScale(1, 1);
	paddle.setSmooth(true);
	return p1pad;
}

sf::Sprite Player::getPlayer1()
{
	return createPlayer1();
}

sf::Sprite Player::createPlayer2()
{
	sf::Sprite p2pad(paddle);
	p2pad.setPosition(gdata.width - gdata.margin - 40, gdata.height / 2 - 25);
	p2pad.setScale(1, 1);
	return p2pad;
}

sf::Sprite Player::getPlayer2()
{
	return createPlayer2();
}

void Player::displayPlayers(GameData& gdata, sf::Sprite p1pad, sf::Sprite p2pad)
{
	gdata.window.draw(p1pad);
	gdata.window.draw(p2pad);
}

void Player::playerMovement(sf::Sprite& p1, sf::Sprite& p2)
{
	//Player 1 movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	p1.move(0, -moveDistance / 50.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	p1.move(0, moveDistance / 50.0f);

	//Player 2 movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	p2.move(0, -moveDistance / 50.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	p2.move(0, moveDistance / 50.0f);
}

void Player::player1BallCollision(sf::Sprite& ball, sf::Sprite player, Ball& ball_, int playerNumber)
{
	//Player collision with ball
	if (spriteintersects(ball, player))
	{
		sf::FloatRect p = player.getGlobalBounds();
		sf::FloatRect b = ball.getGlobalBounds();
		ball_.ballSpeed.x = -ball_.ballSpeed.x;
		ball_.ballSpeed.y = (b.top + b.height / 2 - p.top - p.height / 2) / 10;
		float u = p.left + p.width - b.left;		//Used for player 1 collision
		float v = b.left + b.width - p.left;		//Used for player 2 collision

		if (playerNumber == 1)						//If player 1 has collision 
		{
			b.left = p.left + p.width + u;			 
		}
		else
		{
			b.left = p.left - b.width - v;
		}

		ball.setPosition(b.left, b.top);
	}
}

bool Player::spriteintersects(const sf::Sprite & spr1, const sf::Sprite & spr2)
{
	sf::FloatRect r1 = spr1.getGlobalBounds();
	sf::FloatRect r2 = spr2.getGlobalBounds();
	return r1.intersects(r2);
}

Player::~Player()
{}