#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"



class Entity
{
private:											
													
	void initVariables();
protected:			
	sf::Sprite sprite;		

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	//Initialization functions
	void initSprite(sf::Texture& texture);
	void initMovementComponent(const float maxVelocity, const float minVelocity, const float acceleration, const float deceleration, const bool canAccelerate);
	void initAnimationComponent(sf::Texture& texture_sheet);
	void initHitboxComponent(sf::Vector2f offset, sf::Vector2f size);
													
public:												
	Entity(const float x , const float y , sf::Texture& texture);										
	~Entity();		

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect& getBounds() const;
				
	//Component functions
	const sf::RectangleShape& getHitbox() const;

	//Functions
	void move(const float& dt, sf::Vector2f dir);	
	void setPosition(sf::Vector2f pos);
													
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target);	
};													

