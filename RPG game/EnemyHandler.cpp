#include "stdafx.h"
#include "EnemyHandler.h"



EnemyHandler::EnemyHandler(std::vector<Enemy*>& enemies)
	:enemies(enemies)
{
}


EnemyHandler::~EnemyHandler()
{
}

const bool EnemyHandler::isValidDistance(const sf::Vector2f pos1, const sf::Vector2f pos2, const float range)
{
	if (std::sqrtf(std::powf((pos1.x - pos2.x), 2.f) + std::powf((pos1.y - pos2.y), 2.f)) <= range)
	{
		return true;
	}
	return false;
}


void EnemyHandler::damageEnemy(int damage, const sf::Vector2f mouse_pos, const sf::Vector2f player_pos)
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		if (this->isValidDistance(this->enemies[i]->getCenter(), player_pos, 100.f))
		{
			if (this->isValidDistance(this->enemies[i]->getCenter(), mouse_pos, 50.f))
			{
				this->enemies[i]->getAttributeComponent().takeDamage(damage);


				if (this->enemies[i]->getAttributeComponent().isDead())
				{
					this->despawnEnemy(i);
					--i;
				}
			}
		}
	}
}

void EnemyHandler::spawnEnemy(short enemy_type, const sf::Vector2f pos, EnemySpawner& enemy_spawner)
{
	switch (enemy_type)
	{
	case 0:
		this->enemies.push_back(new BirdEnemy(pos.x, pos.y, enemy_spawner));
		break;

	case 1:
		this->enemies.push_back(new BlobEnemy(pos.x, pos.y, enemy_spawner));
		break;

	case 2:
		this->enemies.push_back(new RatEnemy(pos.x, pos.y, enemy_spawner));
		break;

	case 3:
		this->enemies.push_back(new ScorpionEnemy(pos.x, pos.y, enemy_spawner));
		break;

	case 4:
		this->enemies.push_back(new SpiderEnemy(pos.x, pos.y, enemy_spawner));
		break;

	default:
		std::cout << "ERROR::ENEMYHANDLER::UNEXPECTED ENEMY TYPE" << '\n';
		break;
	}
}

void EnemyHandler::despawnEnemy(const int index)
{
	this->enemies[index]->removeEnemy();

	delete this->enemies[index];

	this->enemies.erase(this->enemies.begin() + index);
}

void EnemyHandler::update(const float& dt, const sf::Vector2f player_pos, AttributeComponent& player_attribute)
{
	for (auto& i : this->enemies)
	{
		i->update(dt);

		sf::Vector2f distance = player_pos - i->getCenter();

		this->move = atan2(distance.y, distance.x);
		this->direction = sf::Vector2f(std::cos(this->move), std::sin(this->move));

		//Move the enemy towards the player
		i->move(dt, this->direction);
		

		if (this->isValidDistance(i->getCenter(), player_pos, 100.f))
		{
			//Attack the player
			player_attribute.takeDamage(i->getAttributeComponent().damage);
		}

	}
}

void EnemyHandler::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox, sf::Vector2f lightPos)
{
	for (auto& i : this->enemies)
	{
		i->render(target, shader, show_hitbox, lightPos);
	}
}
