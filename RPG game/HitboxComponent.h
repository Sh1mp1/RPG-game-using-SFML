#pragma once
class HitboxComponent
{
private:
	sf::RectangleShape hitbox;
	sf::Sprite& sprite;

	sf::FloatRect nextPosition;
	sf::FloatRect nextPositionX;
	sf::FloatRect nextPositionY;

	sf::Vector2f offset;


public:
	HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);
	~HitboxComponent();
	
	//Accessors
	const sf::RectangleShape& getHitbox() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	const sf::FloatRect& getNextPositionX(const float velocity);
	const sf::FloatRect& getNextPositionY(const float velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	//Functions
	bool checkIntersect(const sf::FloatRect& rect);

	void update();
	void render(sf::RenderTarget& target);
};

