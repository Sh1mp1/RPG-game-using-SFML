#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key;
		std::string key_value;
		while (ifs >> key >> key_value)
		{
			this->keybinds.emplace(key, this->supportedKeys->at(key_value));
		}

	}
	ifs.close();
}

void GameState::initPlayer()
{
	this->playerTexture.loadFromFile("Textures/player.png");

	this->textures.emplace("player", &this->playerTexture);


	this->player = new Player(10.f, 10.f, *this->textures.at("player"));
}

void GameState::initBullet()
{
	if (!this->bulletTexture.loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::GAMESTATE::COULDNT LOAD BULLET TEXTURE";
	}
	this->bulletTimerMax = 0.07f;
	this->bulletTimer = -0.5f;
}

void GameState::initAudio()
{
	if (!this->shootBuffer.loadFromFile("Audio/shoot.mp3"))
	{
		std::cout << "ERROR::GAMESTATE::INITAUDIO::COULDNT LOAD AUDIO";
	}

	for (int i = 0; i < 15; ++i)
	{
		this->shootSounds.push_back(sf::Sound(this->shootBuffer));
		
	}
}

GameState::GameState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initAudio();
	this->initPlayer();
	this->initBullet();
}

GameState::~GameState()
{
	delete this->player;

	for (int i = 0; i < this->bullets.size(); ++i)
	{
		delete this->bullets[i];
	}
}




void GameState::updateInput(const float& dt)
{
	
	//Update player movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("move_left"))))
	{
		this->player->move(dt, sf::Vector2f(-1.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("move_right"))))
	{
		this->player->move(dt, sf::Vector2f(1.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("move_up"))))
	{
		this->player->move(dt, sf::Vector2f(0.f, -1.f));
	}																															   
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("move_down"))))											   
	{																															   
		this->player->move(dt, sf::Vector2f(0.f, 1.f));																			   
	}																															   
																																   
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))										 		   
	{																													 		   
		this->quit = true;																								 		   
	}																													 		   
																														 		   
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))																	 		   
	{		
		if (this->bulletTimer >= this->bulletTimerMax)																	 		   
		{
			sf::Vector2f pos = sf::Vector2f(this->player->getPosition().x + (this->player->getBounds().width / 2.f),
				this->player->getPosition().y + (this->player->getBounds().height / 2.f));
			float dx = this->mousePosView.x - pos.x;
			float dy = this->mousePosView.y - pos.y;
			float angle = atan2(dy, dx);																				 		   
			float x = cos(angle);																						 		   
			float y = sin(angle);								 		   
			this->bullets.push_back(new Bullet(sf::Vector2f(x, y), pos, this->bulletTexture, angle * (180 / 3.14)));	 		   
			this->bulletTimer = 0.f;	




			for (int i = 0; i < this->shootSounds.size(); ++i)
			{
				if (this->shootSounds[i].getStatus() != sf::SoundSource::Playing)
				{
					this->shootSounds[i].play();
					break;
				}
			}
		}																												 		   
	}

	if (this->bulletTimer <= this->bulletTimerMax)
	{
		this->bulletTimer += 1 * dt;
	}
}

void GameState::updateBullets(const float& dt)
{
	for (int i = 0; i < this->bullets.size(); ++i)
	{
		this->bullets[i]->update(dt);

		//Delete bullets when out of screen
		if (this->bullets[i]->getPosition().x < -200 || this->bullets[i]->getPosition().x > 2500)
		{
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			--i;
			continue;
		}
		if (this->bullets[i]->getPosition().y < -200 || this->bullets[i]->getPosition().y > 2000)
		{
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			--i;
			continue;
		}
	}

}

void GameState::update(const float& dt)
{

	this->updateInput(dt);

	this->updateMousePositions();

	this->updateBullets(dt);

	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->player->render(*target);

	for (auto i : this->bullets)
	{
		if (i)
			i->render(*target);
	}

}
