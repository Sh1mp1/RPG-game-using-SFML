#include "stdafx.h"
#include "Enemy.h"

void Enemy::initComponents(sf::Texture& texture_sheet)
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

	this->initAttributeComponent(static_cast<unsigned>(1));

	this->attributeComponent->hp = this->attributeComponent->hpMax;
	this->attributeComponent->damage = 5;
}

void Enemy::initAnimations(sf::Texture& texture_sheet)
{
}

void Enemy::initHpBar()
{
	sf::Vector2f size = sf::Vector2f(100.f, 20.f);

	this->hpBarPos = sf::Vector2f(this->getPosition().x - (size.x / 2.f), this->getPosition().y - size.y);

	this->hpBar = new gui::ProgressBar(this->hpBarPos, size, this->attributeComponent->hpMax, this->attributeComponent->hp, sf::Color(0, 0, 0, 0), sf::Color::Red);
}

Enemy::Enemy(const float pos_x, const float pos_y, sf::Texture& texture_sheet, EnemySpawner& enemy_spawner)
	:enemySpawner(enemy_spawner), Entity(pos_x, pos_y, texture_sheet), attackCooldownMax(2.f), attackCooldown(2.f)
{
	this->initComponents(texture_sheet);
	this->initHpBar();
}

Enemy::~Enemy()
{

}

const EnemySpawner& Enemy::getSpawner() const
{
	return this->enemySpawner;
}

AttributeComponent& Enemy::getAttributeComponent() const
{
	return *this->attributeComponent;
}

const bool Enemy::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0;
		return true;
	}
	return false;
}

const int Enemy::getExp() const
{
	return this->exp;
}

void Enemy::removeEnemy()
{
	this->enemySpawner.removeEnemy();
}

void Enemy::updateAttackCooldown(const float& dt)
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += dt;
	}
}

void Enemy::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();

	this->hpBarPos = sf::Vector2f(this->getPosition().x - (this->hpBar->getSize().x / 2.f), this->getPosition().y - this->hpBar->getSize().y);

	this->hpBar->setPosition(this->hpBarPos);

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

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox, sf::Vector2f lightPos)
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

