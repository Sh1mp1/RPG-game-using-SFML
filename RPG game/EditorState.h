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
	sf::Text mousePosText;

	TileMap* tileMap;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	sf::RectangleShape currentTexture;

	sf::Texture tileMapTexture;

	std::map<std::string, gui::Button*> buttons;

	std::map <std::string, int> keybinds;

	//float mouseWheelDelta;

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
	void initTexturRect();

public:
    EditorState(StateData* state_data);
    ~EditorState();

	//Functions 
	void updateMouseScroll(const float& dt);
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateTextureRect(float mouseScroll);
	void updatePauseMenu();
	void updateButtons();
	void updateGUI();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};