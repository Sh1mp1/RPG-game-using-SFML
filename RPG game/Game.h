#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"

class Game
{
private:

	sf::Event event;
	float mouseWheelDelta;

	GraphicsSettings gfxSettings;

	StateData stateData;

	sf::RenderWindow* window;
	sf::View view;

	sf::Font font;

	sf::Clock dtClock;
	float dt;

	float gridSize;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialize functions
	void initVariables();
	void initFont();
	void initGraphicsSettings();
	void initStateData();
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
