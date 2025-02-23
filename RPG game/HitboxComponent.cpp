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


	this->nextPosition = this->hitbox.getGlobalBounds();
	this->nextPositionX = this->hitbox.getGlobalBounds();
	this->nextPositionY = this->hitbox.getGlobalBounds();
}

HitboxComponent::~HitboxComponent()
{
}

const sf::RectangleShape& HitboxComponent::getHitbox() const
{
	return this->hitbox;
}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;
	
	return this->nextPosition;
}

const sf::FloatRect& HitboxComponent::getNextPositionX(const float velocity)
{
	this->nextPositionX.left = this->hitbox.getPosition().x + velocity;

	return this->nextPositionX;
}

const sf::FloatRect& HitboxComponent::getNextPositionY(const float velocity)
{
	this->nextPositionY.top = this->hitbox.getPosition().y + velocity;

	return this->nextPositionY;
}

const sf::FloatRect HitboxComponent::getBounds() const
{
	return this->hitbox.getGlobalBounds();;
}


void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position - this->offset);
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& rect)
{
	return this->sprite.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition() + this->offset);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
