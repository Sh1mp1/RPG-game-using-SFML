#pragma once

#include "State.h"
#include "Player.h"
#include "Entity.h"
#include "Gun.h"

class GameState:
	public State
{
private:
	//Entity player;
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

	float weaponAngle;

	
	//Initialization functions
	void initKeybinds();
	void initPlayer();
	void initBullet();
	void initAudio();
	void initGun();

public:
	GameState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions 
	
	void updateGun(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateBullets(const float& dt);
	void updateWeaponAngle();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

