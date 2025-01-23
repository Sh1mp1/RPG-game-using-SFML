#pragma once
#include "stdafx.h"
#include "Button.h"

class PauseMenu
{
private:

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Font font;



	std::map<std::string, Button*> buttons;

	//Initialization functions
	void initBackground(sf::RenderWindow& window);
	void initButtons();
	void initFont();

public:
	PauseMenu(sf::RenderWindow& window);
	~PauseMenu();

	//FUnctions;
	void update(sf::Vector2f& mousePos, bool& paused, bool& quit);
	void render(sf::RenderTarget& target);
};

