#pragma once
#include "GameData.h"
#include "Ball.h"

class Player
{
public:
	void displayPlayers(GameData& gdata, sf::Sprite p1pad, sf::Sprite p2pad);
	void playerMovement(sf::Sprite& p1, sf::Sprite& p2);	//movement for p1
	void player1BallCollision(sf::Sprite& ball, sf::Sprite p1, Ball& ball_, int playerNumber);					//ball collision for p1
	bool spriteintersects(const sf::Sprite & spr1, const sf::Sprite & spr2);
	bool player1Serve = false;
	bool player2Serve = false;
	sf::Sprite getPlayer1();
	sf::Sprite getPlayer2();
	~Player();
private:
	sf::Texture paddle;
	sf::Sprite createPlayer1();
	sf::Sprite createPlayer2();
	GameData gdata;
	const int moveDistance = 250;
};