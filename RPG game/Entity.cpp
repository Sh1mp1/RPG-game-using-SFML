#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->movementSpeed = 200.f;
	this->animationComponent = nullptr;
	this->movementComponent = nullptr;

}

void Entity::initSprite(sf::Texture& texture)
{
	this->sprite = sf::Sprite(texture);
}

void Entity::initMovementComponent(const float maxVelocity, const float minVelocity,  const float acceleration, const float deceleration, const bool canAccelerate)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, minVelocity, acceleration, deceleration, canAccelerate);
}

void Entity::initAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::initHitboxComponent(sf::Vector2f offset, sf::Vector2f size)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset, size);
}

Entity::Entity(const float x, const float y, sf::Texture& texture)
{
	this->initVariables();
	
	this->initSprite(texture);

	this->sprite.setPosition(sf::Vector2f(x, y));
}

Entity::~Entity()
{
	
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect& Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


//Component functions



//Functions
void Entity::move(const float& dt, sf::Vector2f dir)
{
	if (this->movementComponent)
		this->movementComponent->move(dt, dir, &this->sprite);	//Sets velocity from movement component

	if (this->animationComponent)
	{
	}
		
}

void Entity::update(const float& dt)
{
	if (this->movementComponent != nullptr)
	{
		this->movementComponent->update(dt);
	}


	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

