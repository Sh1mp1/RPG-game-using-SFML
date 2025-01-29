#include "stdafx.h"
#include "Gun.h"

Gun::Gun()
{
}

Gun::Gun(sf::Vector2f pos, sf::Texture& texture)
	:WeaponComponent(texture, pos)
{
	this->sprite.setScale(sf::Vector2f(0.07f, 0.07f));

	this->sprite.setOrigin(sf::Vector2f(-400.f, (this->sprite.getGlobalBounds().height / 2.f) + 200.f));
}

Gun::~Gun()
{
}

void Gun::flip()
{
	if (!this->isFlipped)
	{
		this->sprite.setScale(sf::Vector2f(this->sprite.getScale().x, -1.f * this->sprite.getScale().y));

		this->sprite.setOrigin(sf::Vector2f(-400.f, (this->sprite.getGlobalBounds().height / 2.f) + 150.f));
		this->isFlipped = true;
	}
}

void Gun::update(const float& dt, const sf::Vector2f& player_pos, const float& angle)
{
	this->sprite.setPosition(player_pos);

	this->sprite.setRotation(angle);

	if (!(this->sprite.getRotation() < 270 && this->sprite.getRotation() > 90))
	{
		this->flip();
	}
	else
	{
		if (this->isFlipped)
		{
			this->sprite.setScale(sf::Vector2f(this->sprite.getScale().x, -1.f * this->sprite.getScale().y));
			this->sprite.setOrigin(sf::Vector2f(-400.f, (this->sprite.getGlobalBounds().height / 2.f) - 00.f));
		}
		this->isFlipped = false;	
	}

}

void Gun::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
