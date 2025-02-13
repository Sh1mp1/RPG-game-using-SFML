#pragma once
#include "GUI.h"

class GUI;

class PauseMenu
{
private:

	sf::RectangleShape background;	//Rectangle covering the entire screen
	sf::RectangleShape container;	//Container covers some portion of the middle of the screen with the Resume, exit and other buttons

	sf::Font font;

	sf::RenderWindow& window;

	std::map<std::string, gui::Button*> buttons;

	//Initialization functions
	void initBackground(sf::RenderWindow& window);
	void initButtons();
	void initFont(sf::Font& font);

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	//Accessors
	const bool isPressed(std::string id) const;

	//FUnctions;
	void addButton(sf::Vector2f pos, std::string text);
	void update(sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

