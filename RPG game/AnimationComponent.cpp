#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture)
	:sprite(sprite), texture(texture)
{
	this->lastAnimation = nullptr;
	this->priorityAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

const sf::Vector2f AnimationComponent::getSize() const
{
	return sf::Vector2f(this->animations.at("IDLE")->startFrame.getSize());
}

const bool& AnimationComponent::isDone(const std::string key) const
{
	return this->animations.at(key)->isDone();
}

void AnimationComponent::addAnimation(const std::string key, sf::Vector2i startPos, int no_of_frames, sf::Vector2i size, float animationTimer)
{
	this->animations.emplace(key, new Animation(sprite, this->texture, startPos, no_of_frames, size, animationTimer));
}

//Functions
void AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	if (priority)	//If it is a priority animatino then set it as a priority animation
	{
		this->priorityAnimation = this->animations.at(key);
	}

	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations.at(key))
		{
			if (this->lastAnimation != this->animations.at(key))
			{
				if (this->lastAnimation == nullptr)
				{
					this->lastAnimation = this->animations.at(key);
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations.at(key);
				}
			}

			//Set priority animation to null when it is done
			if (this->animations.at(key)->play(dt))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		if (this->lastAnimation != this->animations.at(key))
		{
			if (this->lastAnimation == nullptr)
			{
				this->lastAnimation = this->animations.at(key);
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations.at(key);
			}
		}

		this->animations.at(key)->play(dt);
	}	
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (priority)
	{
		this->priorityAnimation = this->animations.at(key);
	}

	if (this->priorityAnimation)	//Check if a priority animation exists
	{
		if (this->priorityAnimation == this->animations.at(key))	//IF current animation is priority animation
		{
			if (this->lastAnimation != this->animations.at(key))
			{
				if (this->lastAnimation == nullptr)
				{
					this->lastAnimation = this->animations.at(key);
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations.at(key);
				}
			}
			this->animations.at(key)->play(dt, (modifier / modifier_max));
		}
	}
	else	//If no priority animation exists
	{
		if (this->lastAnimation != this->animations.at(key))
		{
			if (this->lastAnimation == nullptr)
			{
				this->lastAnimation = this->animations.at(key);
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations.at(key);
			}
		}
		if (this->animations.at(key)->play(dt, (modifier / modifier_max)))
		{
			this->priorityAnimation = nullptr;
		}
	}

	
}
