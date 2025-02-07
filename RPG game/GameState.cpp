#include "stdafx.h"
#include "GameState.h"

void GameState::initDefferedRender()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));


	
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));


	sf::FloatRect bounds = this->player->getBounds();
	float posX = bounds.left + (bounds.width / 2.f);
	float posY = bounds.top + (bounds.height / 2.f);

	this->view.setCenter(sf::Vector2f(posX, posY));
}

void GameState::initWindow()
{
	if (this->gfxSettings.fullScreen)
		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);

	else
		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);


	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);
}

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

void GameState::initGun()
{
	if (!this->gunTexture.loadFromFile("Textures/smg.png"))
	{
		std::cout << "ERROR::GAMESTATE::COULDNT LOAD GUN TEXTURE" << '\n';
	}

	sf::Vector2f pos = sf::Vector2f(this->player->getBounds().left + (this->player->getBounds().width / 2), this->player->getBounds().top + (this->player->getBounds().height / 2.f));
	this->gun = new Gun(pos, this->gunTexture);
}

void GameState::initPauseMenu()
{
	this->pauseMenu.addButton(sf::Vector2f(this->window->getSize().x / 2.f, 500.f), "RESUME");
	this->pauseMenu.addButton(sf::Vector2f(this->window->getSize().x / 2.f, 800.f), "EXIT");
}

void GameState::initTileMap()
{
	this->tileMapTexturePath = "Textures/tilesheet.png";
	
	if (!this->tileMapTexture.loadFromFile(this->tileMapTexturePath))
	{
		std::cout << "ERROR::GAMESTATE::COULDNT LOAD TEXTURE FROM PATH: " << this->tileMapTexturePath << '\n';
	}

	this->tileMap = new TileMap(this->stateData->gridSize, static_cast<unsigned>(this->stateData->window->getSize().x / this->stateData->gridSize),
		static_cast<unsigned>(this->stateData->window->getSize().y / this->stateData->gridSize),
		this->tileMapTexture, this->tileMapTexturePath);


	this->tileMap->loadFromFile("testtilemap");

}

GameState::GameState(StateData* state_data)
	:State(state_data), isEscapePressed(false), isGunEquipped(false), isEPressed(false), pauseMenu(*this->window, *state_data->font)
{
	/*
	Fix later :- Change the video resolution immediately or change it only in gameState
	*/
	
	//this->window->create(sf::VideoMode(this->window->getSize().x, this->window->getSize().y), "TEST", sf::Style::Titlebar | sf::Style::Close);
	
	//this->initWindow();
	this->initDefferedRender();
	this->initKeybinds();
	this->initAudio();
	this->initPlayer();
	this->initView();
	this->initBullet();
	this->initGun();
	this->initPauseMenu();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;

	for (int i = 0; i < this->bullets.size(); ++i)
	{
		delete this->bullets[i];
	}
	delete this->tileMap;
}



void GameState::updateView()
{
	sf::FloatRect bounds = this->player->getBounds();
	float posX = bounds.left + (bounds.width / 2.f);
	float posY = bounds.top + (bounds.height / 2.f);

	this->view.setCenter(sf::Vector2f(posX, posY));
}

void GameState::updatePauseMenu()
{
	if (this->paused)
	{
		if (this->pauseMenu.isPressed("EXIT"))
		{
			this->endState();
		}


		if (this->pauseMenu.isPressed("RESUME"))
		{
			this->unPauseState();
		}
	}
}

void GameState::updateGun(const float& dt)
{

	sf::Vector2f pos = sf::Vector2f(this->player->getBounds().left + (this->player->getBounds().width / 2), this->player->getBounds().top + (this->player->getBounds().height / 2.f));
	this->gun->update(dt, pos, this->weaponAngle * (180.f / 3.14f));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("close"))))
	{
		if (!this->isEscapePressed)
		{
			this->isEscapePressed = true;

			if (!this->paused)
			{
				this->pauseState();
			}
			else
			{
				this->unPauseState();
			}
		}
	}
	else
	{
		this->isEscapePressed = false;
	}	
}

void GameState::updatePlayerInput(const float& dt)
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("equip_gun"))))
	{
		if (!this->isEPressed)
		{
			this->isGunEquipped = !this->isGunEquipped;
			this->isEPressed = true;
		}
	}
	else
	{
		this->isEPressed = false;
	}
																																   
																												 		   
																														 		   
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))																	 		   
	{		
		if (this->bulletTimer >= this->bulletTimerMax && this->isGunEquipped)																	 		   
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

void GameState::updateWeaponAngle()
{
	sf::Vector2f pos = sf::Vector2f(this->player->getBounds().left + (this->player->getBounds().width / 2), this->player->getBounds().top + (this->player->getBounds().height / 2.f));
	sf::Vector2f distance = this->mousePosView - pos;

	this->weaponAngle= atan2(distance.y, distance.x);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	if (!this->paused)	//Unpaused update;
	{
		this->updateWeaponAngle();
		this->updatePlayerInput(dt);
		this->updateBullets(dt);
		this->player->update(dt);
		this->updateGun(dt);
		this->tileMap->update(this->player, dt);
		this->updateView();
	}
	else	//Paused update;
	{
		
		this->pauseMenu.update(this->mousePosWindow);
		this->updatePauseMenu();
		this->bulletTimer = -0.1f;
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->setView(this->view);
	
	this->tileMap->render(*target);
	this->player->render(*target);
	if (this->isGunEquipped)
		this->gun->render(*target);
	
	for (auto i : this->bullets)
	{
		if (i)
			i->render(*target);
	}
	if (!this->paused)
	{
	}
	
	else
	{
		target->setView(this->window->getDefaultView());
		this->pauseMenu.render(*target);
	}


	//if (!target)
	//{
	//	target = this->window;
	//}
	//
	//this->renderTexture.clear();
	//this->renderTexture.setView(this->view);
	//
	//this->tileMap->render(this->renderTexture);
	//this->player->render(this->renderTexture);
	//if (this->isGunEquipped)
	//	this->gun->render(this->renderTexture);
	//
	//for (auto i : this->bullets)
	//{
	//	this->renderTexture.setView(this->window->getDefaultView());
	//	if (i)
	//		i->render(this->renderTexture);
	//}
	//if (!this->paused)
	//{
	//}
	//
	//else
	//{
	//	target->setView(this->window->getDefaultView());
	//	this->pauseMenu.render(this->renderTexture);
	//}
	//
	//
	////FINAL RENDER
	//this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	//target->draw(this->renderSprite);
}
