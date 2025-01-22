#include "stdafx.h"
#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const unsigned int characterSize)
{


	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(pos);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	
	return false;
}

const sf::FloatRect& Button::getBounds() const
{
	return this->text.getGlobalBounds();
}

void Button::update(sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->text.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->text.setFillColor(this->idleColor);
		
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->text.setFillColor(this->activeColor);
		break;

	default:
		this->text.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->text);
}
