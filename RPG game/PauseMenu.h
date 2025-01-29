#pragma once
#include "GUI.h"

class PauseMenu
{
private:

	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Font font;

	sf::RenderWindow& window;

	std::map<std::string, gui::Button*> buttons;

	//Initialization functions
	void initBackground(sf::RenderWindow& window);
	void initButtons();
	void initFont();

public:
	PauseMenu(sf::RenderWindow& window);
	~PauseMenu();

	//Accessors
	const bool isPressed(std::string id) const;

	//FUnctions;
	void addButton(sf::Vector2f pos, std::string text);
	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

