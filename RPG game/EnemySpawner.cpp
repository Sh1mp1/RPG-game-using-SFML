#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, const short enemy_type)
	:Tile(grid_pos, gridSize, texture, texture_rect, TileTypes::ENEMY_SPAWNER, false), canSpawn(true), enemyType(enemy_type)
{
	this->timer = 0.f;

	switch (this->enemyType)
	{
	case 0:
		this->timerMax = 20.f;
		break;

	case 1:
		this->timerMax = 15.f;
		break;

	case 2:
		this->timerMax = 5.f;
		break;

	case 3:
		this->timerMax = 10.f;
		break;

	case 4:
		this->timerMax = 10.f;
		break;
	}
	

	this->noOfEnemies = 0;
	this->maxEnemies = 2;
}

EnemySpawner::~EnemySpawner()
{
}

const bool EnemySpawner::getCanSpawn()
{
	
	if (this->canSpawn && (this->noOfEnemies < this->maxEnemies))
	{
		this->canSpawn = false;
		this->noOfEnemies++;
		return true;
	}

	return false;
}

const short EnemySpawner::getEnemyType() const
{
	return this->enemyType;
}

const std::string EnemySpawner::getString() const
{
	std::stringstream ss;
	ss << this->textureRect.left << " " << this->textureRect.top << " " <<
		this->collision << " " << this->type << " " << this->enemyType;
	return ss.str();
}

void EnemySpawner::addEnemy()
{
	if (this->noOfEnemies < this->maxEnemies)
	{
		++this->noOfEnemies;
	}
}

void EnemySpawner::removeEnemy()
{
	if (this->noOfEnemies > 0)
	{
		--this->noOfEnemies;
	}
}

void EnemySpawner::update(const float& dt)
{
	this->timer += dt;


	if (this->timer >= this->timerMax)
	{
		//Spawn enemy
		this->canSpawn = true;

		//Reset timer
		this->timer = 0.f;
	}
}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos)
{	
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
