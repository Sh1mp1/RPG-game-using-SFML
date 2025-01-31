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

	sf::IntRect textureRect;	//Stores which texturerect will be used by tileMap;

	sf::RectangleShape selectorRect;	//Shows which grid the mouse is currently pointing to

	sf::RectangleShape currentTextureGUI;	//Shows which texturerect is currently selected next to mousePosText

	gui::TextureSelector* textureSelector;

	sf::Texture tileMapTexture;	//Stores the texture sheet/ tilesheet

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


	const bool isValidPos(const sf::Vector2u mousePosGrid) const;	//Returns true if the position/intRect of the texture is valid and isn't blank
	//Functions 
	void updateMouseScroll(const float& dt);
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateTextureRect();
	void updatePauseMenu();
	void updateButtons();
	void updateGUI();
	void updateCurrentTextureGUI();
	void updateText();

	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = nullptr);

};