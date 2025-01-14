#include "stdafx.h"
#include "MovementComponent.h"



MovementComponent::MovementComponent(sf::Sprite& sprite, const float maxVelocity, const float minVelocity, const float acceleration, const float deceleration, const bool canAccelerate)
	:sprite(sprite), maxVelocity(maxVelocity), minVelocity(minVelocity), acceleration(acceleration), deceleration(deceleration), canAccelerate(canAccelerate)
{

}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions
void MovementComponent::move(const float& dt, sf::Vector2f dir, sf::Sprite* sprite)
{
	this->velocity.x += dir.x * this->acceleration;
	this->velocity.y += dir.y * this->acceleration;	

	if (!this->canAccelerate)
	{
		this->velocity.x = dir.x * this->maxVelocity;
		this->velocity.y = dir.y * this->maxVelocity;
	}

	//Set to max velocity
	if (this->canAccelerate)
	{
		if (std::abs(this->velocity.y) > this->maxVelocity)
		{
			if (this->velocity.y < 0)
			{
				this->velocity.y = -this->maxVelocity;
			}
			else
			{
				this->velocity.y = this->maxVelocity;
			}
		}
		if (std::abs(this->velocity.x) > this->maxVelocity)
		{
			if (this->velocity.x < 0)
			{
				this->velocity.x = -this->maxVelocity;
			}
			else
			{
				this->velocity.x = this->maxVelocity;
			}
		}
	}
}

void MovementComponent::update(const float& dt)
{
	
	//Deceleration
	if (this->canAccelerate)
	{
		if (this->velocity.x > 0)
		{
			this->velocity.x -= this->deceleration;
		}
		else
		{
			this->velocity.x += this->deceleration;
		}

		if (this->velocity.y > 0)
		{
			this->velocity.y -= this->deceleration;
		}
		else
		{
			this->velocity.y += this->deceleration;
		}
	}


	if (std::abs(this->velocity.x) <= this->minVelocity)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) <= this->minVelocity)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity * dt);
}
