#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initBackground(sf::RenderWindow& window)
{
	sf::Vector2f windowSize = sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	this->background.setSize(sf::Vector2f(windowSize));
	this->container.setSize(sf::Vector2f(windowSize.x / 4.f, windowSize.y));

	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(sf::Vector2f(0.f, 0.f));

	this->container.setPosition(sf::Vector2f((windowSize.x / 2.f) - (this->container.getGlobalBounds().width / 2.f), 0.f));
}

void PauseMenu::initButtons()
{
	this->buttons.emplace("RESUME", new Button(sf::Vector2f(880, 500.f), &this->font, "RESUME",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 50));

	this->buttons.emplace("EXIT", new Button(sf::Vector2f(920, 800.f), &this->font, "EXIT",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 50));
}

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
	this->initBackground(window);

	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::PAUSEMENU::COULDNT LOAD FONT!" << '\n';
	}

	this->initButtons();
}

PauseMenu::~PauseMenu()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}
}

//Functions

void PauseMenu::update(sf::Vector2f& mousePos, bool& paused, bool& quit)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}

	paused = (!this->buttons.at("RESUME")->isPressed());	//If it is pressed then paused will be set to false

	quit = this->buttons.at("EXIT")->isPressed();		//If it is pressed quit will be set to true
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}



