#pragma once
class WeaponComponent
{
protected:

	sf::Sprite sprite;

	int damage;
	int range;

public:
	WeaponComponent();
	WeaponComponent(sf::Texture& texture, sf::Vector2f pos, const int damage, const int range);
	~WeaponComponent();

	const int getDamage() const;

	virtual void update(const float& dt, const sf::Vector2f& playerPos, const float& angle) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false) = 0;
};

