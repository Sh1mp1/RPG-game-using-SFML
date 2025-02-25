#pragma once

#include "State.h"
#include "Player.h"
#include "Entity.h"
#include "Gun.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class State;
class Player;
class PlayerGUI;
class Entity;
class Gun;
class TileMap;

class GameState:
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	Player* player;
	sf::Texture playerTexture;
	PlayerGUI* playerGUI;


	sf::Shader shader;

	PauseMenu* pauseMenu;
	bool isEscapePressed;

	Gun* gun;
	sf::Texture gunTexture;
	bool isGunEquipped;
	bool isEPressed;

	std::vector<sf::Sound> shootSounds;
	sf::SoundBuffer shootBuffer;

	std::vector<Entity*> bullets;
	sf::Texture bulletTexture;
	float bulletTimer;
	float bulletTimerMax;

	std::map <std::string, int> keybinds;

	TileMap* tileMap;
	sf::Texture tileMapTexture;	//Stores the texture sheet/ tilesheet
	std::string tileMapTexturePath;	//Stores the path to the texture file

	float weaponAngle;

	gui::FPS* fps;

	sf::Text debugText;

	
	//Initialization functions
	void initDefferedRender();
	void initView();
	void initWindow();
	void initKeybinds();
	void initPlayer();
	void initPlayerGUI();
	void initBullet();
	void initAudio();
	void initGun();
	void initPauseMenu();
	void initTileMap();
	void initFps();
	void initShaders();
	void initText();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions 
	void updateView();	//Sets the center of the camera to the player
	void updatePauseMenu();
	void updateGun(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateBullets(const float& dt);
	void updateWeaponAngle();
	void updateFps(const float& dt);
	void updateDebugText();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

