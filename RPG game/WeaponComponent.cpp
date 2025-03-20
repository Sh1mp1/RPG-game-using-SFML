#include "stdafx.h"
#include "WeaponComponent.h"

WeaponComponent::WeaponComponent()
{
}

WeaponComponent::WeaponComponent(sf::Texture& texture, sf::Vector2f pos, const int damage, const int range)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos);

	this->damage = damage;
	this->range = range;

}

WeaponComponent::~WeaponComponent()
{
}

const int WeaponComponent::getDamage() const
{
	return this->damage;
}


