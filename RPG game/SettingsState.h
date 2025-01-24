#pragma once
#include "State.h"
#include "GUI.h"

class SettingsState :
    public State
{
private:

	sf::Sprite background;
	sf::Texture backgroundTexture;

	std::map <std::string, int> keybinds;

	sf::Font font;
	sf::Text mousePosText;

	std::map<std::string, gui::Button*> buttons;

	gui::DropDownList* dropDownList;

	//Functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();
	void initDropDownList();

public:
    SettingsState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states);
    ~SettingsState();

	//Functions 

	void updateInput(const float& dt);
	void updateButtons();
	void updateText();
	void updateGUI();
	void updateDropDownList();
	

	void update(const float& dt);

	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};

