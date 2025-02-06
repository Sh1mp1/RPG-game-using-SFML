#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initBackground(sf::RenderWindow& window)
{
	sf::Vector2f windowSize = sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	this->background.setSize(sf::Vector2f(windowSize));
	this->container.setSize(sf::Vector2f(windowSize.x / 4.f, windowSize.y));

	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setFillColor(sf::Color(20, 20, 20, 250));
	this->background.setPosition(sf::Vector2f(0.f, 0.f));

	this->container.setPosition(sf::Vector2f((windowSize.x / 2.f) - (this->container.getGlobalBounds().width / 2.f), 0.f));
}

void PauseMenu::initButtons()
{
	this->buttons.emplace("RESUME", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, 500.f), &this->font, "RESUME",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 50));
	
	this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, 800.f), &this->font, "EXIT",
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 50));
}

void PauseMenu::initFont(sf::Font& font)
{
	this->font = font;
}

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:window(window)
{
	this->initBackground(window);

	this->initFont(font);

	//this->initButtons();
}

PauseMenu::~PauseMenu()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}
}

const bool PauseMenu::isPressed(std::string id) const
{
	return this->buttons.at(id)->isPressed();
}

//Functions

void PauseMenu::addButton(sf::Vector2f pos, std::string text)
{
	this->buttons.emplace(text, new gui::Button(pos, &this->font, text,
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), 50));
}

void PauseMenu::update(sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}

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



