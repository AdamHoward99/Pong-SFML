#pragma once
#include "GameData.h"
#include "GameApplication.h"
#include "Ball.h"

class Court
{
public:
	void createCourt();
	void displayCourt(GameData& gdata, sf::Sprite& topBorder, sf::Sprite& bottomBorder, sf::RectangleShape& middleLine);
	void ballCollision(sf::Sprite& ball, sf::Sprite topBorder, sf::Sprite bottomBorder, Ball& ball_);
	void playerCollision(sf::Sprite& p1pad, sf::Sprite topBorder, sf::Sprite bottomBorder);
	bool spriteintersects(const sf::Sprite & spr1, const sf::Sprite & spr2);
	bool intersects(const sf::Sprite & spr1, const sf::RectangleShape & rect2);
	float clamp(const int x, const int a, const int b);
	void checkforScore(sf::Sprite& Ball, sf::Text& score, int& gameState, GameApplication& game, bool& player2Serve, sf::Sprite p2pad, int borderPosition, bool& playerNotToServe);
	sf::Sprite getTopBorder();
	sf::Sprite getBottomBorder();
	sf::RectangleShape getMiddleLine();
	sf::RectangleShape borders[2];	//left is 0, right is 1
	~Court();
private:
	sf::Texture pongBorder;
	sf::Sprite createTopBorder();
	sf::Sprite createBottomBorder();
	sf::RectangleShape createMiddleLine();
	GameData gdata;
};