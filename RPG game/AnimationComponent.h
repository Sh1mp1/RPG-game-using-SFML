#pragma once
#include "stdafx.h"

class AnimationComponent
{
private:
	class Animation
	{

	public:
		//Variables
		sf::Texture& textureSheet;

		sf::IntRect startFrame;
		sf::IntRect currentFrame;
		sf::IntRect endFrame;

		float animationTimer;
		float timer;

		Animation(sf::Texture& textureSheet, sf::Vector2i startPos, sf::Vector2i endPos, sf::Vector2i size, float animationTimer)
			:textureSheet(textureSheet), animationTimer(animationTimer)
		{
			this->startFrame = sf::IntRect(startPos, size);
			this->currentFrame = this->startFrame;
			this->endFrame = sf::IntRect(endPos, size);
		}

		//Functions
		void update(const float& dt)
		{
			this->timer = 10 * dt;

			if (this->timer >= this->animationTimer)
			{
				//reset timer;
				this->timer = 0.f;

				if (this->currentFrame != this->endFrame)
				{
					this->currentFrame.left += this->currentFrame.width;
				}
				else
				{
					//reset to starting frame
					this->currentFrame = this->startFrame;
				}
			}
		}

		void pause();
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& texture;
	


	std::map <std::string, Animation> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture);
	~AnimationComponent();

	//Functions
	void addAnimation(const std::string key);


	void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);

	void update(const float& dt);
};

