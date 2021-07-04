#include "assert.h"
#include "Court.h"
#include <sstream>

sf::RectangleShape Court::createMiddleLine()
{
	sf::RectangleShape middleLine;
	middleLine.setOutlineColor(sf::Color(254, 190, 254, 200));
	middleLine.setOutlineThickness(5);
	middleLine.setPosition(gdata.width / 2, 0.f);
	middleLine.setSize(sf::Vector2f(0, gdata.height));
	return middleLine;
}

sf::RectangleShape Court::getMiddleLine()
{
	return createMiddleLine();
}

sf::Sprite Court::createTopBorder()
{
	//Creating the top border of the game
	if (!pongBorder.loadFromFile("pongBorder.png"))	assert(false);
	sf::Sprite topBorder(pongBorder);
	pongBorder.setSmooth(true);
	topBorder.setScale(gdata.width - 2 * gdata.borderSize, 2);
	topBorder.setPosition(gdata.borderSize - 20, 0);
	return topBorder;
}

sf::Sprite Court::createBottomBorder()
{
	//Creating the bottom border of the game
	sf::Sprite bottomBorder(pongBorder);
	pongBorder.setSmooth(true);
	bottomBorder.setScale(gdata.width - 2 * gdata.borderSize, 2);
	bottomBorder.setPosition(gdata.borderSize - 20, gdata.height - gdata.borderSize - 4);
	return bottomBorder;
}

sf::Sprite Court::getTopBorder()
{
	return createTopBorder();
}

sf::Sprite Court::getBottomBorder()
{
	return createBottomBorder();
}

void Court::createCourt()
{
	//Left border
	borders[0].setPosition(0, 0);
	borders[0].setSize(sf::Vector2f(gdata.borderSize, gdata.height));

	borders[0].setFillColor(sf::Color(0, 0, 0));
	borders[0].setOutlineColor(sf::Color::Black);
	borders[0].setOutlineThickness(3);

	//Right border 
	borders[1].setPosition(gdata.width - gdata.borderSize, 0);
	borders[1].setSize(sf::Vector2f(gdata.borderSize, gdata.height));

	borders[1].setFillColor(sf::Color(0, 0, 0));
	borders[1].setOutlineColor(sf::Color::Black);
	borders[1].setOutlineThickness(3);
}

void Court::displayCourt(GameData& gdata, sf::Sprite& topBorder, sf::Sprite& bottomBorder, sf::RectangleShape& middleLine)
{
	gdata.window.draw(borders[0]);
	gdata.window.draw(borders[1]);
	gdata.window.draw(topBorder);
	gdata.window.draw(bottomBorder);
	gdata.window.draw(middleLine);
}

void Court::ballCollision(sf::Sprite& ball, sf::Sprite topBorder, sf::Sprite bottomBorder, Ball& ball_)
{

	//Collision between the ball and top border
	if (spriteintersects(ball, topBorder))
	{
		sf::FloatRect t = topBorder.getGlobalBounds();
		sf::FloatRect b = ball.getGlobalBounds();
		ball_.ballSpeed.y = -ball_.ballSpeed.y;
		float u = t.top + t.height - b.top;
		ball.move(0, 2.0f * u);
	}

	//Collision between the ball and bottom border
	if (spriteintersects(ball, bottomBorder))
	{
		sf::FloatRect bot = bottomBorder.getGlobalBounds();
		sf::FloatRect b = ball.getGlobalBounds();
		ball_.ballSpeed.y = -ball_.ballSpeed.y;
		float u = bot.top - b.height - b.top;
		ball.move(0, 2.0f * u);
	}
}

void Court::playerCollision(sf::Sprite& paddle, sf::Sprite topBorder, sf::Sprite bottomBorder)
{
	//Player collision with walls
	if (spriteintersects(paddle, topBorder) || spriteintersects(paddle, bottomBorder))
	{
		sf::FloatRect t = topBorder.getGlobalBounds();
		sf::FloatRect b = bottomBorder.getGlobalBounds();
		sf::Vector2f p = paddle.getPosition();
		p.y = clamp((int)p.y, (int)t.top + (int)t.height + 5, ((int)b.top - 100) - (int)paddle.getScale().y - 5);
		paddle.setPosition(p);
	}
}

void Court::checkforScore(sf::Sprite& Ball, sf::Text& score, int& gameState, GameApplication& game, bool& playerServe, sf::Sprite paddle, int borderPosition, bool& playerNotToServe)
{

	//Checking for scoring
	if (intersects(Ball, borders[borderPosition]))
	{
		if (borderPosition == 1)		//When the left border wall is hit
		{
			++gdata.p1Score;
		}
		else
		{
			++gdata.p2Score;
		}

		std::stringstream str;
		str << gdata.p1Score << "    " << gdata.p2Score;
		score.setString(str.str());
		score.setPosition(gdata.width / 2 - score.getGlobalBounds().width / 2, 10);
		sf::FloatRect p = paddle.getGlobalBounds();
		sf::FloatRect b = Ball.getGlobalBounds();
		Ball.setPosition(p.left - b.width - 5, gdata.height / 2);
		gameState = game.STARTING_STATE;
		playerServe = true;
		playerNotToServe = false;
	}
}

//Checks for collisions during the game
bool Court::intersects(const sf::Sprite & spr1, const sf::RectangleShape & rect2)
{
	sf::FloatRect r1 = spr1.getGlobalBounds();
	sf::FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

bool Court::spriteintersects(const sf::Sprite & spr1, const sf::Sprite & spr2)
{
	sf::FloatRect r1 = spr1.getGlobalBounds();
	sf::FloatRect r2 = spr2.getGlobalBounds();
	return r1.intersects(r2);
}

//Checks for collision for player 1 during game
float Court::clamp(const int x, const int a, const int b)
{
	return (float)std::min(std::max(a, x), b);
}

Court::~Court()
{}