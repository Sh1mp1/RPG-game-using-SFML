#pragma once
#include "stdafx.h"

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	sf::View view;
	sf::ContextSettings settings;

	std::vector<sf::VideoMode> videoModes;

	sf::Clock dtClock;
	float dt;


	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialize functions
	void initVariables();
	void initWindow();	
	void initStates();
	void initKeys();

public:
	Game();
	~Game();


	//Functions

	void run();
	void endGame();

	void updateDt();
	void pollEvents();

	void update();
	

	void render();
};
