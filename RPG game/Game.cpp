#include "stdafx.h"
#include "Game.h"

//Initialization functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
}

void Game::initWindow()
{

	std::ifstream ifs("Config/window.ini");

	std::string title = "GAME";

	this->videoModes = sf::VideoMode::getFullscreenModes();

	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned antialiasing = 0;

	unsigned framerate_limit = 144;
	bool vsync_enabled = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vsync_enabled;
		ifs >> antialiasing;
		ifs >> fullscreen;
	}
	ifs.close();

	this->settings.antialiasingLevel = antialiasing;
	if (fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->settings);

	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->settings);
	//this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vsync_enabled);
	
}



void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
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
	this->initWindow();
	this->initKeys();
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
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Escape)
			{
				//this->window->close();
			}
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
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
	this->window->clear(sf::Color(129, 235, 255));

	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	this->window->display();
}
