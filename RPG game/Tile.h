#pragma once


enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:
	sf::RectangleShape shape;

	sf::IntRect textureRect;

	short type;
	bool collision;

	//Initialization functions
	void initShape(sf::Vector2u grid_pos, float gridSize);
	void initTexture(const sf::Texture& texture, const sf::IntRect& texture_rect);
public:
	Tile();
	Tile(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, short type, bool collision);
	~Tile();

	//Accessors
	const std::string getString() const;
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getTextureRectPosition() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

