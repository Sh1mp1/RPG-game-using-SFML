#pragma once

#include "State.h"
#include "Player.h"
#include "Entity.h"
#include "Gun.h"
#include "TileMap.h"

class State;
class Player;
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

	Entity* player;
	sf::Texture playerTexture;

	PauseMenu pauseMenu;
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

	
	//Initialization functions
	void initDefferedRender();
	void initView();
	void initWindow();
	void initKeybinds();
	void initPlayer();
	void initBullet();
	void initAudio();
	void initGun();
	void initPauseMenu();
	void initTileMap();

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

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

