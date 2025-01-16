#pragma once
#include "Entity.h"
#include "Bullet.h"


class Player:
	public Entity
{
private:

	sf::Font font;
	sf::Text text;

	sf::CircleShape topLeftCircle;
	sf::CircleShape topRightCircle;
	sf::CircleShape	bottomLeftCircle;
	sf::CircleShape bottomRightCircle;

	//Initializer functions
	void initVariables();
	void initComponents(sf::Texture& texture_sheet);
	void initText();
	void initFramework();

public:
	Player(const float x, const float y, sf::Texture& texture_sheet);
	~Player();

	void updateFramework();
	void updateText();
	void updateMovement(const float& dt, sf::Vector2f dir);
	void updateInput();
	void update(const float& dt);

	void render(sf::RenderTarget* target);
};

