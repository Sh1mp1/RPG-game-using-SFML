#pragma once

class AnimationComponent
{
private:
	class Animation
	{

	public:
		//Variables
		sf::Texture& textureSheet;
		sf::Sprite& sprite;

		sf::IntRect startFrame;
		sf::IntRect currentFrame;
		sf::IntRect endFrame;

		float animationTimer;
		float timer;


		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, sf::Vector2i startPos, int no_of_frames , sf::Vector2i size, float animationTimer)
			:textureSheet(textureSheet), animationTimer(animationTimer), sprite(sprite), startFrame(startPos, size)
		{
			this->timer = 0.f;
			this->startFrame = sf::IntRect(startPos, size);
			this->currentFrame = this->startFrame;

			this->endFrame = sf::IntRect((startPos.x + (size.x * (no_of_frames - 1))), startPos.y, size.x, size.y);

			this->sprite.setTextureRect(this->currentFrame);
		}

		//Functions
		void play(const float& dt)
		{
			this->timer += 100 * dt;

			if (this->timer >= this->animationTimer)
			{
				//reset timer;
				this->timer = 0.f;

				if (this->currentFrame.left < this->endFrame.left)
				{
					this->currentFrame.left += this->currentFrame.width;
				}
				else
				{
					//reset to starting frame
					this->currentFrame = this->startFrame;
				}
				this->sprite.setTextureRect(this->currentFrame);
			} 
		}

		void reset()
		{
			this->currentFrame = this->startFrame;
			this->timer = 0.f;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& texture;
	Animation* lastAnimation;
	


	std::map <std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture);
	~AnimationComponent();

	//Functions
	void addAnimation(const std::string key, sf::Vector2i startPos, int no_of_frames, sf::Vector2i size, float animationTimer);


	void play(const std::string key, const float& dt);
};

