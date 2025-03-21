#pragma once

#include "GUI.h"

class DeathScreen
{
private:

	sf::RectangleShape background;	//Rectangle covering the entire screen
	sf::RectangleShape container;	//Container covers some portion of the middle of the screen with the Resume, exit and other buttons

	sf::Font font;

	sf::Text text;
	int alpha;

	sf::VideoMode videoMode;

	std::map<std::string, gui::Button*> buttons;

	//Initialization functions
	void initBackground();
	void initButtons();
	void initFont(sf::Font& font);

public:
	DeathScreen(sf::VideoMode& video_mode, sf::Font& font);
	~DeathScreen();

	//Accessors
	const bool isPressed(std::string id) const;

	//FUnctions;
	void addButton(const sf::Vector2f pos, const std::string text, const unsigned char_size);
	void update(const float& dt, sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

