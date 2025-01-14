#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{
	this->initMovementComponent(400.f ,10.f,  20.f, 6.f, true);
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
Player::Player(const float x, const float y, sf::Texture& texture)
	:Entity(x, y , texture)
{
	this->initSprite(texture);
	this->initVariables();
	this->initComponents();
	this->initText();
}

Player::~Player()
{
}


void Player::updateText()
{
	std::stringstream ss;
	ss << "X : " << this->movementComponent->getVelocity().x << " Y : " << this->movementComponent->getVelocity().y;
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
	this->updateText();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->text);
}
