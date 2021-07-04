#pragma once
#include "SFML/Graphics.hpp"

struct GameData
{
	sf::RenderWindow window;
	sf::Text text;
	sf::Font font;
	const float width = 1024;
	const float height = 768;
	const float borderSize = 12;
	const float margin = 50;
	unsigned int p1Score = 0, p2Score = 0;
	enum
	{
		PRINT_OFFSETX = 100,
		PRINT_OFFSETY = 50,
		PRINT_LINEINC = 50,
		PRINT_FONTSIZE = 30
	};

	enum
	{
		ASCII_ENTER = 13,
		ASCII_ESCAPE = 27,
		ASCII_UP = 24,
		ASCII_DOWN = 25,
		ASCII_S = 83 || 115,
		ASCII_W = 87 || 119
	};
};

struct Vec2f
{
	float x, y;

	Vec2f() : x(0.f), y(0.f)
	{}

	Vec2f(int x, int y) : x(x), y(y) {};

	Vec2f(double x, double y) : x(x), y(y) {};

	Vec2f operator+(const Vec2f& vec)
	{
		Vec2f v;
		v.x = this->x + vec.x;
		v.y = this->y + vec.y;
		return v;
	}

	Vec2f operator*(const Vec2f& vec)
	{
		Vec2f v;
		v.x = this->x * vec.x;
		v.y = this->y * vec.y;
		return v;
	}

	Vec2f operator-(const Vec2f& vec)
	{
		Vec2f v;
		v.x = this->x - vec.x;
		v.y = this->y - vec.y;
		return v;
	}

};