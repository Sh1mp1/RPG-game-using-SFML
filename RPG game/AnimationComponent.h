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

		bool done;

		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, sf::Vector2i startPos, int no_of_frames , sf::Vector2i size, float animationTimer)
			:textureSheet(textureSheet), animationTimer(animationTimer), sprite(sprite), startFrame(startPos, size), done(false)
		{
			this->timer = 0.f;
			this->startFrame = sf::IntRect(startPos, size);
			this->currentFrame = this->startFrame;

			this->endFrame = sf::IntRect((startPos.x + (size.x * (no_of_frames - 1))), startPos.y, size.x, size.y);

			this->sprite.setTextureRect(this->currentFrame);
		}

		//Accessor

		const bool& isDone() const
		{
			return this->done;
		}

		//Functions
		const bool& play(const float& dt)
		{
			this->timer += 100 * dt;
			this->done = false;

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
					this->reset();
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentFrame);


			} 
			return done;
		}

		const bool& play(const float& dt, const float& modifier)
		{
			this->timer += modifier * 100 * dt;
			this->done = false;

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
					this->reset();
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentFrame);
			}
			return this->done;
		}

		void reset()
		{
			this->currentFrame.left = this->startFrame.left;
			this->timer = 0;			
		}
	};


	//Animation component members
	sf::Sprite& sprite;
	sf::Texture& texture;

	Animation* lastAnimation;
	Animation* priorityAnimation;


	std::map <std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture);
	~AnimationComponent();

	//Accessors
	const sf::Vector2f getSize() const;
	const bool& isDone(const std::string key) const;

	//Functions
	void addAnimation(const std::string key, sf::Vector2i startPos, int no_of_frames, sf::Vector2i size, float animationTimer);


	void play(const std::string key, const float& dt, const bool priority);
	void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority);
};

