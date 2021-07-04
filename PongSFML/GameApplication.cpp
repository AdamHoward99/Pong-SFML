#include "GameApplication.h"
#include "Ball.h"
#include "Player.h"
#include "Court.h"
#include "Score.h"
#include "GameObject.h"
#include "GameData.h"

void GameApplication::init(GameApplication& game)
{
	GameObject gameObj;
	GameData gdata;
	gdata.window.create(sf::VideoMode((int)gdata.width, (int)gdata.height), "Pong In SFML");
	gdata.text.setCharacterSize(GameData::PRINT_FONTSIZE);
	gameState = STARTING_STATE;

	game.run(game, gdata);
}

void GameApplication::run(GameApplication& game, GameData& gdata)
{
	GameObject gameObj;

	//Initialise the game
	gameObj.court.createCourt(); 		//Creating the walls for the game

	//Determines the speed of the ball
	gameObj.ball_.SpeedofBall();

	while (gdata.window.isOpen())
	{
		char command = 0;
		bool enter = false;
		sf::Event event;

		gdata.window.setFramerateLimit(60);
		while (gdata.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	gameState = game.QUIT_STATE;
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == GameData::ASCII_ESCAPE)	gameState = game.QUIT_STATE;
				else if (isalpha(event.text.unicode))	command = toupper(event.text.unicode);
				else if (isdigit(event.text.unicode))	command = toupper(event.text.unicode);
				else if (event.text.unicode == 32)	gameState = game.GAME_STATE;
				else if (event.text.unicode == GameData::ASCII_ENTER)	enter = true;
			}
		}
		gdata.window.clear();
		gdata.text.setFont(gdata.font);

		//Switch statement for switching states of the game
		switch (gameState)
		{
		case game.STARTING_STATE:
			//Output the starting stuff
			//Draws the borders and ball to the screen
			gameObj.court.displayCourt(gdata, gameObj.topBorder, gameObj.bottomBorder, gameObj.middleLine);

			//Set the ball in a straight line for the first serve
			gameObj.ball_.ballSpeed.x = 6.1f; gameObj.ball_.ballSpeed.y = 0.f;

			//Initial serve (p1)
			gameObj.Ball.setPosition(gameObj.p1pad.getPosition().x + 30, gameObj.p1pad.getPosition().y + 50);

			//P2 Serve
			if (gameObj.players.player2Serve)
			{
				gameObj.Ball.setPosition(gameObj.p2pad.getPosition().x - 50, gameObj.p2pad.getPosition().y + 50);
				gameObj.ball_.ballSpeed.x = -6.1f; gameObj.ball_.ballSpeed.y = 0.f;
			}

			//gdata.window.draw(ball);
			gdata.window.draw(gameObj.Ball);

			gameObj.score_.displayScore(gdata, gameObj.score);

			//Draw the players to the screen
			gameObj.players.displayPlayers(gdata, gameObj.p1pad, gameObj.p2pad);
			break;

		case game.GAME_STATE:

			//Draws the borders and ball to the screen

			gameObj.court.displayCourt(gdata, gameObj.topBorder, gameObj.bottomBorder, gameObj.middleLine);

			gdata.window.draw(gameObj.Ball);

			//Draw the score to the screen
			gdata.window.draw(gameObj.score);

			//Draw the players to the screen
			gameObj.players.displayPlayers(gdata, gameObj.p1pad, gameObj.p2pad);
			break;

		case game.QUIT_STATE:
			gdata.window.close();
			break;
		}

		gameObj.court.ballCollision(gameObj.Ball, gameObj.topBorder, gameObj.bottomBorder, gameObj.ball_);

		gameObj.players.playerMovement(gameObj.p1pad, gameObj.p2pad);		//Moves both players around the court

		gameObj.court.playerCollision(gameObj.p1pad, gameObj.topBorder, gameObj.bottomBorder);		//Checks collision between player 1 paddle and walls

		gameObj.court.playerCollision(gameObj.p2pad, gameObj.topBorder, gameObj.bottomBorder);		//Checks collision between player 2 paddle and walls

		gameObj.players.player1BallCollision(gameObj.Ball, gameObj.p1pad, gameObj.ball_, 1);		//Checks ball collision for player 1 paddle
		gameObj.players.player1BallCollision(gameObj.Ball, gameObj.p2pad, gameObj.ball_, 2);		//Checks ball collision for player 2 paddle

		gameObj.court.checkforScore(gameObj.Ball, gameObj.score, gameState, game, gameObj.players.player2Serve, gameObj.p2pad, 0, gameObj.players.player1Serve);	//Checks if player 1 has scored
		gameObj.court.checkforScore(gameObj.Ball, gameObj.score, gameState, game, gameObj.players.player1Serve, gameObj.p1pad, 1, gameObj.players.player2Serve);	//Checks if player 2 has scored



		//Moves the ball
		gameObj.ball_.moveBall(gameObj.Ball);
		gdata.window.display();
	}

}