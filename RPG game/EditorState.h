#pragma once
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

enum EditorModes {Default = 0, COLLISION, SPAWNER};

class EditorState :
    public State
{
private:
	std::map<std::string, sf::Texture> enemyTextures;	//
	sf::Sprite currentEnemy;							//GUI to show what enemy type the enemy spawner will have
	sf::RectangleShape currentEnemyBoundary;

	sf::View view;
	float cameraSpeed;	//The speed at which user can move the camera

	sf::Text mouseText;	//Shows position of mouse, this->collision and this->type. UI to show properties of the tile currently selected

	TileMap* tileMap;	//contains the tile sheet

	sf::IntRect textureRect;	//Stores which texturerect will be used by tileMap;

	sf::RectangleShape selectorRect;	//Shows which grid the mouse is currently pointing to

	sf::RectangleShape currentTextureGUI;	//Shows which texturerect is currently selected next to mousePosText

	gui::TextureSelector* textureSelector;	//GUI to select specific tile from tile sheet

	sf::RectangleShape sidebar;		//Useless, dont know why I made it

	sf::Texture tileMapTexture;		//Stores the texture sheet/tilesheet
	std::string tileMapTexturePath;		//The path of the tile sheet file

	std::map<std::string, gui::Button*> buttons;		//Not used for now

	std::map <std::string, int> keybinds;	//Theyre keybinds duh

	float addTileCooldown;		//An extra cooldown so user doesnt add a tile whenever hitting the hide tilemap button
	float addTileCooldownMax;

	PauseMenu pauseMenu;
	bool isEscapePressed;

	bool collision;		//Stores if the tile to be added will have collision
	short type;		//Stores the type of the tile to be added
	short enemyType;		//Stores the enemy type to be stored in enemy spawner
	std::string typeString;	//Stores the string for the type of the tile currently selected


	std::vector<std::string> modes;
	int currentMode;
	bool showHitbox;
	bool showSpawners;
	sf::Text currentModeText;
	bool isTogglePressed;	//For toggling view modes 

	//Initializer functions
	void initVariables();
	void initView();
	void initKeybinds();
	void initFont();
	void initBackground();
	void initButtons();
	void initGUI();
	void initPauseMenu();
	void initTileMap();
	void initTextureRect();

	void initViewModes();
	void initEnemyTextures();
public:
    EditorState(StateData* state_data);
    ~EditorState();


	const bool isValidPos(const sf::Vector2u mousePosGrid) const;	//Returns true if the position/intRect of the texture is valid and isn't blank

	const bool canAddTile();

	//Functions 
	void updateAddTileCooldown(const float& dt);
	void updateMouseScroll(const float& dt);
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateViewSize();
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