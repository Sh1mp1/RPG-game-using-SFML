#include "stdafx.h"
#include "WeaponComponent.h"

WeaponComponent::WeaponComponent()
{
}

WeaponComponent::WeaponComponent(sf::Texture& texture, sf::Vector2f pos)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos);

}

WeaponComponent::~WeaponComponent()
{
}


void WeaponComponent::update(const sf::Vector2f& playerPos, const float& angle)
{
	this->sprite.setPosition(playerPos);
	this->sprite.rotate(angle);
}

void WeaponComponent::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
