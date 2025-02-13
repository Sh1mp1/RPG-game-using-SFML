#pragma once


enum TileTypes {DEFAULT = 0, DAMAGING, NO_OF_TYPES};

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
	Tile(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, short type = 0, bool collision = 0);
	~Tile();

	//Accessors
	const bool hasCollision() const;
	const std::string getString() const;
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getTextureRectPosition() const;
	const sf::FloatRect getBounds() const;
	const sf::IntRect& getTextureRect() const;

	//Functions
	const bool intersects(const sf::FloatRect& bounds) const;	//Returns true if the tile is intersecting with the given bounds

	void update();
	void render(sf::RenderTarget& target);
};

