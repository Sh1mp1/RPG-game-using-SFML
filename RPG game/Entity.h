#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class MmovementComponent;
class AnimationComponent;
class HitboxComponent;
class AttributeComponent;

class Entity
{
private:											
													
	void initVariables();
protected:			
	sf::Sprite sprite;		

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;

	//Initialization functions
	void initSprite(sf::Texture& texture);
	void initMovementComponent(const float maxVelocity, const float minVelocity, const float acceleration, const float deceleration, const bool canAccelerate);
	void initAnimationComponent(sf::Texture& texture_sheet);
	void initHitboxComponent(sf::Vector2f offset, sf::Vector2f size);
	void initAttributeComponent(const unsigned level);
													
public:												
	Entity(const float x , const float y , sf::Texture& texture);										
	~Entity();		

	//Accessors
	virtual const sf::Vector2f getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned grid_size) const;
	virtual const sf::FloatRect getBounds() const;
	virtual const sf::FloatRect getNextBounds() const;
	virtual const sf::FloatRect getNextBoundsX() const;
	virtual const sf::FloatRect getNextBoundsY() const;

	//Modifiers
	virtual void setPosition(const sf::Vector2f& position);
	virtual void resetVelocityX();
	virtual void resetVelocityY();
				
	//Component functions
	virtual const sf::RectangleShape& getHitbox() const;

	//Functions
	void move(const float& dt, sf::Vector2f dir);	
	void moveConstant(sf::Vector2f dir);
											
	virtual void updateHitboxComponent();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;	
};													

