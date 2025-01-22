#pragma once
#include "stdafx.h"
#include "Button.h"

class PauseMenu
{
private:

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window);
	~PauseMenu();

	//FUnctions;
	void update();
	void render(sf::RenderTarget& target);
};

