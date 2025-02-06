#pragma once
#include "Tile.h"
#include "Entity.h"

class TileMap;
class Entity;

class TileMap
{
private:
	void clearMap();

	float gridSizeF;
	unsigned gridSizeU;
	
	sf::Vector2u maxSizeGrid;	//Total no. of tiles in both x and y axes.
	sf::Vector2f maxSizeWorld;

	unsigned layers;		//No of tiles in z axis
	std::vector<std::vector<std::vector<Tile*>>> map;

	std::string texturePath;

	sf::Texture& tileSheet;

	sf::RectangleShape collisionBox;

	//Initialization functions
	void initTileMap(float grid_size, unsigned width, unsigned height);
	void initTileTextureSheet();
	void initGUI();
public:
	TileMap(float gridSize, unsigned width , unsigned height, sf::Texture& texture, const std::string texture_path);
	~TileMap();

	//Functions
	void savetoFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const short type = 0, const bool collision = false);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void updateCollision(Entity* entity, const float& dt);

	void update(Entity* entity, const float& dt);
	void render(sf::RenderTarget& target);

};

