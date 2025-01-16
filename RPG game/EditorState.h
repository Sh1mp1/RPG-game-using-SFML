#pragma once
#include "State.h"
#include "Button.h"

class EditorState :
    public State
{

    sf::Font font;
	sf::Text mousePosText;

	std::map<std::string, Button*> buttons;

	std::map <std::string, int> keybinds;

	//Initializer functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states);
    ~EditorState();

	//Functions 

	void updateInput(const float& dt);
	void updateButtons();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget* target);

	void render(sf::RenderTarget* target = nullptr);

};