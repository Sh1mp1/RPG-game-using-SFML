#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(sf::Vector2f dir, sf::Vector2f pos, sf::Texture& texture, float angle)
	:Entity(pos.x , pos.y, texture), movementSpeed(3000.f)
{
	this->velocity = dir;

	this->initMovementComponent(3000.f ,0.f, 0 ,0.f, false);

	this->sprite.setScale(sf::Vector2f(0.03f, 0.03f));

	this->sprite.setOrigin(sf::Vector2f(this->sprite.getGlobalBounds().width /2, this->sprite.getGlobalBounds().height /2));
	this->sprite.setPosition(pos);

	//int deviation = 10;
	//
	//if (rand() % 2 == 0)
	//{
	//	this->sprite.rotate(angle - 180 + (rand() % deviation));
	//}
	//else
	//{
	//	this->sprite.rotate(angle - 180 - (rand() % deviation));
	//}

	this->sprite.rotate(angle - 180);	

	this->sprite.move(this->velocity * 200.f);
}

Bullet::~Bullet()
{
}

const sf::Vector2f Bullet::getPosition() const
{
	return this->sprite.getPosition();
}

void Bullet::update(const float& dt)
{
	this->move(dt, this->velocity);

	if (this->movementComponent)
	{
		this->movementComponent->update(dt);
	}
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}


