#pragma once

#include "State.h"
#include "GUI.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"

class State;
class GUI;
class GameState;
class EditorState;
class SettingsState;


class MainMenuState:
	public State
{
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;

	sf::RectangleShape backgroundFade;

	std::map <std::string, int> keybinds;

	sf::Font font;
	sf::Text mousePosText;

	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();


public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions 

	void updateInput(const float& dt);
	void updateButtons();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);
};
