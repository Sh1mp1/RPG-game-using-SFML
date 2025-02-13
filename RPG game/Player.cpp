#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->sprite.setPosition(980, 500);
}

void Player::initComponents(sf::Texture& texture_sheet)
{
	this->initMovementComponent(400.f, 0.f, 9999, 1100, true);

	this->initAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("MOVING_DOWN",
		sf::Vector2i(0, 64), 4, sf::Vector2i(64, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_UP",
		sf::Vector2i(768, 64), 4, sf::Vector2i(64, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_LEFT",
		sf::Vector2i(256, 64), 4, sf::Vector2i(64, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_RIGHT",
		sf::Vector2i(512, 64), 4, sf::Vector2i(64, 64), 10.f);

	this->animationComponent->addAnimation("IDLE",
		sf::Vector2i(0, 0), 9, sf::Vector2i(64, 64), 10.f);


	this->initHitboxComponent(sf::Vector2f(10.f, 0.f), sf::Vector2f(44.f, 64.f));
}

void Player::initText()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::PLAYER::COULDNT LOAD FONT";
	}
	this->text.setFont(this->font);
	this->text.setPosition(sf::Vector2f(1000.f, 10.f));
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(20);
}


//Constructor / Destructor
Player::Player(const float x, const float y, sf::Texture& texture_sheet)
	:Entity(x, y , texture_sheet)
{
	//this->initSprite(texture_sheet);
	this->initVariables();
	this->initText();

	this->initComponents(texture_sheet);



}

Player::~Player()
{
	
}



void Player::updateText()
{
	std::stringstream ss;
	ss << "X : " << this->sprite.getPosition().x << " Y : " << this->sprite.getPosition().y << '\n'
		<< "Vel X " << this->movementComponent->getVelocity().x << " Vel Y " << this->movementComponent->getVelocity().y;
	this->text.setString(ss.str());
}

//Functions
void Player::updateMovement(const float& dt, sf::Vector2f dir)
{
	
}

void Player::updateInput()
{
	
}

void Player::updateAnimation(const float& dt)
{
	if (this->animationComponent)
	{
		switch (this->movementComponent->getState())
		{
		case STATE::IDLE:
			this->animationComponent->play("IDLE", dt, false);

			break;

		case STATE::MOVING_UP:
			this->animationComponent->play("MOVING_UP", dt, -this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
			break;

		case STATE::MOVING_DOWN:
			this->animationComponent->play("MOVING_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
			break;

		case STATE::MOVING_LEFT:
			this->animationComponent->play("MOVING_LEFT", dt, -this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
			break;

		case STATE::MOVING_RIGHT:
			this->animationComponent->play("MOVING_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity(), false);
			break;
		}
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->updateText();																			
											
	this->hitboxComponent->update();
}																								
																								
void Player::render(sf::RenderTarget& target)													
{																								
	target.draw(this->sprite);																	
	target.draw(this->text);																	
																								
	this->hitboxComponent->render(target);				
}
