#include "stdafx.h"
#include "DeathScreen.h"

void DeathScreen::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->videoMode.width), static_cast<float>(this->videoMode.height)));
	this->container.setSize(sf::Vector2f(static_cast<float>(this->videoMode.width) / 4.f, static_cast<float>(this->videoMode.height) / 2.f));

	this->background.setFillColor(sf::Color(15, 15, 15, 150));
	this->container.setFillColor(sf::Color(20, 20, 20, 50));
	this->background.setPosition(sf::Vector2f(0.f, 0.f));

	this->container.setPosition(sf::Vector2f((static_cast<float>(this->videoMode.width) / 2.f) - (this->container.getGlobalBounds().width / 2.f), 0.f));
}

void DeathScreen::initButtons()
{
	//this->buttons.emplace("RESUME", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, this->window.getSize().y * 0.46f), &this->font, "RESUME",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), this->window.getSize().x * 0.026f));
	//
	//this->buttons.emplace("EXIT", new gui::Button(sf::Vector2f(this->window.getSize().x / 2.f, this->window.getSize().y * 0.74f), &this->font, "EXIT",
	//	sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), this->window.getSize().x * 0.026f));
}

void DeathScreen::initFont(sf::Font& font)
{
	this->font = font;
	this->text.setFont(this->font);

	this->text.setString("YOU DIED");
	this->text.setFillColor(sf::Color(255, 0, 0, 0));
	this->alpha = 0;

}

DeathScreen::DeathScreen(sf::VideoMode& video_mode, sf::Font& font)
	:videoMode(video_mode)
{
	this->initBackground();

	this->initFont(font);

	//this->initButtons();
	this->container.setPosition(sf::Vector2f((video_mode.width / 2.f) - (this->container.getGlobalBounds().width / 2.f),
		(video_mode.height / 2.f) - (this->container.getGlobalBounds().height / 2.f)));

	this->text.setCharacterSize(50);
	this->text.setPosition(sf::Vector2f((video_mode.width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		(video_mode.height / 2.f) - (this->text.getGlobalBounds().height / 2.f)));


}

DeathScreen::~DeathScreen()
{
	for (auto& i : this->buttons)
	{
		delete i.second;
	}
}

const bool DeathScreen::isPressed(std::string id) const
{
	return this->buttons.at(id)->isPressed();
}

//Functions

void DeathScreen::addButton(const sf::Vector2f pos, const std::string text, const unsigned char_size)
{
	this->buttons.emplace(text, new gui::Button(pos, &this->font, text,
		sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(80, 80, 80), char_size));
}

void DeathScreen::update(const float& dt, sf::Vector2i& mousePosWindow)
{
	if (dt * 400.f >= 2.f)
	{
		this->alpha += dt * 400.f;
	}
	else
	{
		this->alpha += 2.f;
	}

	if (this->alpha > 255)
	{
		this->alpha = 255;
	}

	this->text.setFillColor(sf::Color(255, 0, 0, this->alpha));
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}

}

void DeathScreen::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	//target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->text);
}