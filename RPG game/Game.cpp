#include "stdafx.h"
#include "Game.h"

float mouseWheelDelta;

//Initialization functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;

	this->gridSize = 64.f;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::GAME::COULDNT LOAD FONT" << '\n';
	}
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("config/window.ini");
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
	this->stateData.font = &this->font;
	this->stateData.mouseWheelDelta = &this->mouseWheelDelta;
}

void Game::initWindow()
{
	if (this->gfxSettings.fullScreen)
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);

	else
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);


	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);	
}



void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

void Game::initKeys()
{

	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key;
		int key_value;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys.emplace(key, key_value);
		}

	}
	ifs.close();
}


//Constructor & Destructor
Game::Game()
{
	this->initVariables();
	this->initFont();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();	
}


Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();

		this->states.pop();
	}
}


void Game::run()
{
	while (this->window->isOpen())
	{
		if (this->window->hasFocus())
			this->updateDt();

		this->update();
		this->render();
	}
}

void Game::endGame()
{
	//Ending app
}

//Functions

void Game::updateDt()
{
	//Updates dt to the time it takes to render 1 frame

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::pollEvents()
{
	this->mouseWheelDelta = 0.f;
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::MouseWheelScrolled: 
			this->mouseWheelDelta = this->event.mouseWheelScroll.delta;
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				//this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	//Application end
	else
	{
		this->endGame();
		this->window->close();
	}
}

void Game::render()
{
	//this->window->clear(sf::Color(129, 235, 255));
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	this->window->display();
}
