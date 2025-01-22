#pragma once
class WeaponComponent
{
protected:

	sf::Sprite sprite;


public:
	WeaponComponent();
	WeaponComponent(sf::Texture& texture, sf::Vector2f pos);
	~WeaponComponent();



	virtual void update(const sf::Vector2f& playerPos, const float& angle);
	virtual void render(sf::RenderTarget& target);
};

