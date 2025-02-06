#include "stdafx.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size)
	:sprite(sprite), offset(offset)
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
	this->hitbox.setSize(size);

	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

const sf::RectangleShape& HitboxComponent::getHitbox() const
{
	return this->hitbox;
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& rect)
{
	return this->sprite.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update(const float& dt)
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
