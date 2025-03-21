#include "stdafx.h"
#include "ScorpionEnemy.h"

void ScorpionEnemy::initComponents(sf::Texture& texture_sheet)
{
	this->initMovementComponent(100.f, 0.f, 9999, 1100, true);

	this->initAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("MOVING_DOWN", sf::Vector2i(0, 0), 3, sf::Vector2i(60, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_LEFT", sf::Vector2i(0, 64), 3, sf::Vector2i(60, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_RIGHT", sf::Vector2i(0, 128), 3, sf::Vector2i(60, 64), 10.f);

	this->animationComponent->addAnimation("MOVING_UP", sf::Vector2i(0, 192), 3, sf::Vector2i(60, 64), 10.f);



	this->initHitboxComponent(sf::Vector2f(17.f, 38.f), sf::Vector2f(28.f, 28.f));
}

void ScorpionEnemy::initAnimations(sf::Texture& texture_sheet)
{
}

ScorpionEnemy::ScorpionEnemy(const float pos_x, const float pos_y, EnemySpawner& enemy_spawner)
	:scorpionTexture(), Enemy(pos_x, pos_y, this->scorpionTexture, enemy_spawner)
{
	if (!this->scorpionTexture.loadFromFile("Textures/scorpion1_60x64.png"))
	{
		std::cout << "ERROR::SCORPIONENEMY::COULDNT LOAD TEXTURE" << '\n';
	}
	this->initComponents(this->scorpionTexture);

	this->damage = 7;
	this->exp = 15;
}

ScorpionEnemy::~ScorpionEnemy()
{
}

void ScorpionEnemy::updateAnimation(const float& dt)
{
	if (this->animationComponent)
	{
		switch (this->movementComponent->getState())
		{
		case STATE::IDLE:
			//this->animationComponent->play("IDLE", dt, false);
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

void ScorpionEnemy::update(const float& dt)
{
	this->attributeComponent->update();


	this->movementComponent->update(dt);


	this->hitboxComponent->update();


	this->updateAnimation(dt);

	this->hpBarPos = sf::Vector2f(this->getCenter().x - (this->hpBar->getSize().x / 2.f), this->getPosition().y - this->hpBar->getSize().y);

	this->hpBar->setPosition(this->hpBarPos);
	this->hpBar->update(this->attributeComponent->hp);
}

void ScorpionEnemy::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox, sf::Vector2f lightPos)
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