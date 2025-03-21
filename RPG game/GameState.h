#pragma once

#include "State.h"
#include "Player.h"
#include "Entity.h"
#include "Gun.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "EnemyHandler.h"
#include "Sword.h"
#include "DeathScreen.h"

class State;
class Player;
class PlayerGUI;
class Entity;
class Gun;
class TileMap;
class Enemy;
class EnemyHandler;

class GameState:
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;


	//Entities
	Player* player;
	sf::Texture playerTexture;
	PlayerGUI* playerGUI;

	std::vector<Enemy*> enemies;
	EnemyHandler* enemyHandler;
	Enemy* enemy;
	sf::Texture ratEnemyTexture;


	//Weapons
	Sword* sword;
	float attackTimer;
	float attackTimerMax;
	sf::Texture swordTexture;
	Gun* gun;
	sf::Texture gunTexture;
	bool isGunEquipped;
	bool isEPressed;
	std::vector<Entity*> bullets;
	sf::Texture bulletTexture;
	float bulletTimer;
	float bulletTimerMax;


	sf::Shader shader;

	//Pause menu
	PauseMenu* pauseMenu;
	bool isEscapePressed;	

	//Deathscreen
	DeathScreen* endScreen;
	sf::Font endFont;

	//Audio
	std::vector<sf::Sound> shootSounds;
	sf::SoundBuffer shootBuffer;

	sf::Sound deathSound;
	sf::SoundBuffer deathBuffer;
	bool deathSoundPlayed;

	

	std::map <std::string, int> keybinds;

	TileMap* tileMap;
	sf::Texture tileMapTexture;	//Stores the texture sheet/ tilesheet
	std::string tileMapTexturePath;	//Stores the path to the texture file

	float weaponAngle;

	gui::FPS* fps;

	sf::Text debugText;

	sf::Font progressBarFont;
	//gui::ProgressBar* hpBar;
	
	//Initialization functions
	void initDefferedRender();
	void initView();
	void initWindow();
	void initKeybinds();
	void initPlayer();
	void initPlayerGUI();
	void initEnemyHandler();
	void initBullet();
	void initAudio();
	void initWeapons();
	void initPauseMenu();
	void initDeathScreen();
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

