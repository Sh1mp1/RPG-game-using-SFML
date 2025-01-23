#pragma once
#include "State.h"
#include "Button.h"

class SettingsState :
    public State
{
private:

	sf::Sprite background;
	sf::Texture backgroundTexture;

	std::map <std::string, int> keybinds;

	sf::Font font;
	sf::Text mousePosText;

	std::map<std::string, Button*> buttons;

	//Functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();

public:
    SettingsState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states);
    ~SettingsState();

	//Functions 

	void updateInput(const float& dt);
	void updateButtons();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};

