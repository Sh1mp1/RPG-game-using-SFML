#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initBackground()
{
	this->background.setSize(sf::Vector2f(this->videoMode.width, this->videoMode.height));
	this->container.setSize(sf::Vector2f(this->videoMode.width / 4.f, this->videoMode.height));

	this->background.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setFillColor(sf::Color(20, 20, 20, 250));
	this->background.setPosition(sf::Vector2f(0.f, 0.f));

	this->container.setPosition(sf::Vector2f((this->videoMode.width / 2.f) - (this->container.getGlobalBounds().width / 2.f), 0.f));
}

void PauseMenu::initButtons()
{
	//this->buttons.emplace("RESUME", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, this->window.getSize().y * 0.46f), &this->font, "RESUME",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), this->window.getSize().x * 0.026f));
	//
	//this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, this->window.getSize().y * 0.74f), &this->font, "EXIT",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), this->window.getSize().x * 0.026f));
}

void PauseMenu::initFont(sf::Font& font)
{
	this->font = font;
}

PauseMenu::PauseMenu(sf::VideoMode& video_mode, sf::Font& font)
	:videoMode(video_mode)
{
	this->initBackground();

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

void PauseMenu::addButton(const sf::Vector2f pos, const std::string text, const unsigned char_size)
{
	this->buttons.emplace(text, new gui::Button(pos, &this->font, text,
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), char_size));
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



