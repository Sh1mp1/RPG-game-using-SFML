
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture)
	:sprite(sprite), texture(texture)
{
}

AnimationComponent::~AnimationComponent()
{
}

//Functions
void AnimationComponent::update(const float& dt)
{
}
