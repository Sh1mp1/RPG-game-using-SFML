#pragma once
class MovementComponent
{
private:

	sf::Sprite& sprite;

	bool canAccelerate;

	float maxVelocity;
	float minVelocity;

	sf::Vector2f velocity;

	float acceleration;
	float deceleration;

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, const float maxVelocity, const float minVelocity, const float acceleration , const float deceleration, const bool canAccelerate);
	~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;

	//Functions
	void move(const float& dt, sf::Vector2f dir, sf::Sprite* sprite);
	void update(const float& dt);
};

