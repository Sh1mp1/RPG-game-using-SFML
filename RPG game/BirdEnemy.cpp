#include "stdafx.h"
#include "BirdEnemy.h"

void BirdEnemy::initComponents(sf::Texture& texture_sheet)
{
	this->initMovementComponent(300.f, 0.f, 1750, 1100, true);

	this->initAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", sf::Vector2i(0, 0), 3, sf::Vector2i(61, 57), 10.f);

	this->animationComponent->addAnimation("MOVING_LEFT", sf::Vector2i(0, 57), 3, sf::Vector2i(60, 57), 10.f);

	this->animationComponent->addAnimation("MOVING_RIGHT", sf::Vector2i(0, 114), 3, sf::Vector2i(60, 57), 10.f);

	this->animationComponent->addAnimation("MOVING_UP", sf::Vector2i(0, 171), 3, sf::Vector2i(60, 57), 10.f);



	this->initHitboxComponent(sf::Vector2f(10.f, 45.f), sf::Vector2f(35.f, 35.f));



	this->attributeComponent->hp = 100;
}

void BirdEnemy::initAnimations(sf::Texture& texture_sheet)
{
}

BirdEnemy::BirdEnemy(const float pos_x, const float pos_y, EnemySpawner& enemy_spawner)
	:birdTexture(), Enemy(pos_x, pos_y, this->birdTexture, enemy_spawner)
{
	if (!this->birdTexture.loadFromFile("Textures/bird1_61x57.png"))
	{
		std::cout << "ERROR::SCORPIONENEMY::COULDNT LOAD TEXTURE" << '\n';
	}
	this->initComponents(this->birdTexture);

	this->damage = 80;
	this->exp = 20;
}

BirdEnemy::~BirdEnemy()
{
}

void BirdEnemy::updateAnimation(const float& dt)
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
			this->animationComponent->play("IDLE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity(), false);
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

void BirdEnemy::update(const float& dt)
{
	this->attributeComponent->update();


	this->movementComponent->update(dt);


	this->hitboxComponent->update();


	this->updateAnimation(dt);

	this->hpBarPos = sf::Vector2f(this->getCenter().x - (this->hpBar->getSize().x / 2.f), this->getPosition().y - this->hpBar->getSize().y);

	this->hpBar->setPosition(this->hpBarPos);
	this->hpBar->update(this->attributeComponent->hp);
}

void BirdEnemy::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox, sf::Vector2f lightPos)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	//target.draw(this->text);																	

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
	
	this->hpBar->render(target);
}
