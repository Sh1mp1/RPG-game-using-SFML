#include "stdafx.h"
#include "MovementComponent.h"



MovementComponent::MovementComponent(sf::Sprite& sprite, const float maxVelocity, const float minVelocity, const float acceleration, const float deceleration, const bool canAccelerate)
	:sprite(sprite), maxVelocity(maxVelocity), minVelocity(minVelocity), acceleration(acceleration), deceleration(deceleration), canAccelerate(canAccelerate)
{
	this->state = 0;
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const int& MovementComponent::getState() const
{
	return this->state;
}

void MovementComponent::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void MovementComponent::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::resetVelocityY()
{
	this->velocity.y = 0.f;
}


//Functions
void MovementComponent::move(const float& dt, sf::Vector2f dir, sf::Sprite* sprite)
{
	this->velocity.x += dir.x * this->acceleration * dt;
	this->velocity.y += dir.y * this->acceleration * dt;

	if (!this->canAccelerate)
	{
		this->velocity.x = dir.x * this->maxVelocity;
		this->velocity.y = dir.y * this->maxVelocity;
	}


	//Set to max velocity if it exceeds it
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

void MovementComponent::moveConstant(sf::Vector2f dir, sf::Sprite& sprite)
{
	sprite.move(dir);
}

void MovementComponent::updateState()
{
	this->state = STATE::IDLE;

	if (this->velocity.y < 0.f)
	{
		this->state = STATE::MOVING_UP;
	}
	else if (this->velocity.y > 0.f)
	{
		this->state = STATE::MOVING_DOWN;
	}

	if (this->velocity.x < 0.f)
	{
		this->state = STATE::MOVING_LEFT;
	}
	else if (this->velocity.x > 0.f)
	{
		this->state = STATE::MOVING_RIGHT;
	}
	
	if (std::abs(this->velocity.y) > std::abs(this->velocity.x))
	{
		if (this->velocity.y < 0.f)
		{
			this->state = STATE::MOVING_UP;
		}
		else if (this->velocity.y > 0.f)
		{
			this->state = STATE::MOVING_DOWN;
		}
	}

}

void MovementComponent::update(const float& dt)
{
	this->updateState();


	//Deceleration
	if (this->canAccelerate)
	{
		if (this->velocity.x > 0.f )
		{
			this->velocity.x -= this->deceleration  * dt;
			if (this->velocity.x < 0.f)
			{
				this->velocity.x = 0.f;
			}

		}
		else if (this->velocity.x < 0.f)
		{
			this->velocity.x += this->deceleration  * dt;
			if (this->velocity.x > 0.f)
			{
				this->velocity.x = 0.f;
			}
		}
		
		if (this->velocity.y > 0.f )
		{
			this->velocity.y -= this->deceleration  * dt;
			if (this->velocity.y < 0.f)
			{
				this->velocity.y = 0.f;
			}

		}
		else if (this->velocity.y < 0.f)
		{
			this->velocity.y += this->deceleration  * dt;
			if (this->velocity.y > 0.f)
			{
				this->velocity.y = 0.f;
			}

		}
	}

	if (std::abs(this->velocity.x) < this->minVelocity)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < this->minVelocity)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity* dt);


	

}
