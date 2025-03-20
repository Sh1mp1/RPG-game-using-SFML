#include "stdafx.h"
#include "Sword.h"

Sword::Sword(sf::Texture& texture, const sf::Vector2f position)
	:WeaponComponent(texture, position, 30, 200)
{
	//if (!this->texture.loadFromFile("Textures/sword.png"))
	//{
	//	std::cout << "ERROR::SWORD::COULDNT LOAD TEXTURE" << '\n';
	//}

	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2.f,
		this->sprite.getGlobalBounds().height
	);
}

Sword::~Sword()
{
}

void Sword::update(const float& dt, const sf::Vector2f& position, const float& angle)
{
	this->sprite.setPosition(position);

	this->sprite.setRotation(angle + 90.f);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	target.draw(this->sprite);
}
