#pragma once
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    sf::Font font;
	sf::Text mousePosText;

	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	std::map<std::string, gui::Button*> buttons;

	std::map <std::string, int> keybinds;

	PauseMenu pauseMenu;
	bool isEscapePressed;

	//Initializer functions
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();
	void initGUI();
	void initPauseMenu();
	void initTileMap();

public:
    EditorState(StateData* state_data);
    ~EditorState();

	//Functions 

	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updatePauseMenu();
	void updateButtons();
	void updateGUI();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};