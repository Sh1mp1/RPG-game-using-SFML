#pragma once
class Tile
{
private:

protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(sf::Vector2f pos, float gridSize);
	~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

