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
	int gridSizeI;
	
	sf::Vector2u maxSizeGrid;	//Total no. of tiles in both x and y axes.
	sf::Vector2f maxSizeWorld;	//Total size of entire tile sheet 1920 x 1080 if it only spans across the window
	sf::Vector2u maxSizeWorldGrid;

	unsigned layers;		//No. of tiles in z axis
	std::vector<std::vector<std::vector<Tile*>>> map;

	std::string texturePath;

	sf::Texture& tileSheet;

	sf::RectangleShape collisionBox;

	//Culling
	unsigned fromX;
	unsigned fromY;
	unsigned toX;
	unsigned toY;
	unsigned layer;

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

	void addTile(const unsigned x, const unsigned y, const sf::IntRect& texture_rect, const short type = 0, const bool collision = false);
	void removeTile(const unsigned x, const unsigned y);

	void updateCollision(Entity* entity, const float& dt);

	void update(Entity* entity, const float& dt);
	void render(sf::RenderTarget& target, Entity* entity);

};

