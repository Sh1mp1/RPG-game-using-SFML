#pragma once


enum TileTypes {DEFAULT = 0, DAMAGING, DEFERRED, ENEMY_SPAWNER, NO_OF_TYPES};

class Tile
{
private:

protected:
	sf::Sprite shape;

	sf::IntRect textureRect;

	short type;
	bool collision;

	//Initialization functions
	void initShape(sf::Vector2u grid_pos, float gridSize);
	void initTexture(const sf::Texture& texture, const sf::IntRect& texture_rect);
public:
	Tile();
	Tile(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, short type = 0, bool collision = false);
	~Tile();

	//Accessors
	virtual const bool hasCollision() const;
	virtual const std::string getString() const;
	virtual const sf::Vector2f getPosition() const;
	virtual const sf::Vector2f getTextureRectPosition() const;
	virtual const sf::FloatRect getBounds() const;
	virtual const sf::IntRect& getTextureRect() const;
	virtual const short getType() const;
	virtual const std::string getTypeString(short type) const;
	const sf::Texture& getTexture() const;

	//Functions
	virtual const bool intersects(const sf::FloatRect& bounds) const;	//Returns true if the tile is intersecting with the given bounds

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPos = sf::Vector2f());
};

