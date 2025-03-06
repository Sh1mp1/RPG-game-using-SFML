#pragma once
#include "State.h"
#include "GUI.h"
#include "GraphicsSettings.h"

class State;
class GUI;
class GraphicsSettings;

class SettingsState :
    public State
{
private:

	sf::Sprite background;
	sf::Texture backgroundTexture;

	sf::RectangleShape bg;
	std::map <std::string, int> keybinds;

	sf::Text mousePosText;

	std::map<std::string, gui::Button*> buttons;

	std::map<std::string, gui::ToggleButton*> toggleButtons;

	std::map<std::string, gui::DropDownList*> dropDownLists;
	

	std::map<std::string, sf::Text> optionsText;

	std::vector<sf::VideoMode> videoModes;

	//Functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();
	void initToggleButtons();
	void initVariables();
	void initDropDownList();
	void initWindow();

public:
    SettingsState(StateData* state_data);
    ~SettingsState();

	//Functions 

	void updateInput(const float& dt);
	void updateButtons();
	void updateText();
	void updateGUI();
	void updateDropDownList();
	void updateButtonPos();
	void updateToggleButtons();
	

	void update(const float& dt);

	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};

