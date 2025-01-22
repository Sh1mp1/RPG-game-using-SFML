#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{

	sf::Vector2f windowSize = sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	this->background.setSize(sf::Vector2f(windowSize));
	this->container.setSize(sf::Vector2f(windowSize.x / 4.f, windowSize.y));

	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->background.setPosition(sf::Vector2f(0.f, 0.f));
	
	this->container.setPosition(sf::Vector2f((windowSize.x / 2.f) - (this->container.getGlobalBounds().width / 2.f), 0.f));



}

PauseMenu::~PauseMenu()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}
}

//Functions

void PauseMenu::update()
{
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



