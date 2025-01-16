#pragma once
class HitboxComponent
{
private:
	sf::RectangleShape hitbox;
	sf::Sprite& sprite;

	sf::Vector2f offset;


public:
	HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);
	~HitboxComponent();
	
	//Functions
	bool checkIntersect(const sf::FloatRect& rect);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

