#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents(sf::Texture& texture_sheet)
{
	this->initMovementComponent(400.f, 10.f, 20.f, 6.f, true);
	this->initAnimationComponent(texture_sheet);
	
	this->animationComponent->addAnimation("IDLE_LEFT",
		sf::Vector2i(12, 62), sf::Vector2i(1508, 62), sf::Vector2i(192,120), 15.f);
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
	this->text.setCharacterSize(20.f);
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
	ss << "X : " << this->sprite.getPosition().x << " Y : " << this->sprite.getPosition().y;
	this->text.setString(ss.str());
}

//Functions
void Player::updateMovement(const float& dt, sf::Vector2f dir)
{
	
}

void Player::updateInput()
{
	
}

void Player::update(const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->update(dt);
	}

	if (this->animationComponent)
	{
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	this->updateText();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->text);
}
