#pragma once
class Tile
{
private:

protected:
	sf::RectangleShape shape;


	//Initialization functions
	void initShape(sf::Vector2f pos, float gridSize);
	void initTexture(const sf::Texture& texture, const sf::IntRect& texture_rect);
public:
	Tile();
	Tile(sf::Vector2f pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect);
	~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

