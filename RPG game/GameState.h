#pragma once

#include "State.h"
#include "Player.h"
#include "Entity.h"

class GameState:
	public State
{
private:
	//Entity player;
	Entity* player;
	sf::Texture playerTexture;

	PauseMenu pauseMenu;

	std::vector<sf::Sound> shootSounds;
	sf::SoundBuffer shootBuffer;

	std::vector<Entity*> bullets;
	sf::Texture bulletTexture;
	float bulletTimer;
	float bulletTimerMax;

	std::map <std::string, int> keybinds;
	
	//Initialization functions
	void initKeybinds();
	void initPlayer();
	void initBullet();
	void initAudio();

public:
	GameState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions 
	

	void updateInput(const float& dt);
	void updateBullets(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

