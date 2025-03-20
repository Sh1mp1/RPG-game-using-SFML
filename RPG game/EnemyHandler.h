#pragma once

#include "Enemy.h"
#include "RatEnemy.h"
#include "ScorpionEnemy.h"
#include "SpiderEnemy.h"
#include "BlobEnemy.h"
#include "BirdEnemy.h"

enum EnemyTypes { BIRD = 0, BLOB, RAT, SCORPION, SPIDER, NUMBER_OF_TYPES};

class EnemyHandler
{
private:
	std::vector<Enemy*>& enemies;

	float move;
	sf::Vector2f direction;

public:
	EnemyHandler(std::vector<Enemy*>& enemies);
	~EnemyHandler();

	//Functions
	//Returns true if the distance between the points is less than or equal to range
	const bool isValidDistance(const sf::Vector2f pos1, const sf::Vector2f pos2, const float range);	


	void damageEnemy(int damage, const sf::Vector2f mouse_pos, const sf::Vector2f player_pos);

	void spawnEnemy(short enemy_type, const sf::Vector2f pos, EnemySpawner& enemy_spawner);
	void despawnEnemy(const int index);


	void update(const float& dt, const sf::Vector2f player_pos, AttributeComponent& player_attribute);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false, sf::Vector2f lightPos = sf::Vector2f());
};

