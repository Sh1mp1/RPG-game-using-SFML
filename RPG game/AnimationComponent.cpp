#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture)
	:sprite(sprite), texture(texture)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, sf::Vector2i startPos, sf::Vector2i endPos, sf::Vector2i size, float animationTimer)
{
	this->animations.emplace(key, new Animation(sprite, this->texture, startPos, endPos, size, animationTimer));

	
}

//Functions
void AnimationComponent::play(const std::string key, const float& dt)
{
	this->animations.at(key)->play(dt);
}
