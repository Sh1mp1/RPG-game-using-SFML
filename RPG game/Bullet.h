#pragma once
#include "Entity.h"

class Bullet:
	public Entity
{
private:

	float movementSpeed;

	sf::Vector2f velocity;

	//Initialize

public:
	Bullet(sf::Vector2f dir, sf::Vector2f pos, sf::Texture& texture, float angle);
	~Bullet();

	//Accessor
	const sf::Vector2f getPosition() const;

	void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false, sf::Vector2f lightPos = sf::Vector2f());
};

