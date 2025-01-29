#pragma once
#include "Tile.h"

class TileMap
{
private:

	float gridSizeF;
	unsigned gridSizeU;
	
	sf::Vector2u mapSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;

	sf::Texture& tileSheet;

	//Initialization functions
	void initTileMap(float grid_size, unsigned width, unsigned height);
	void initTileTextureSheet();
		
public:
	TileMap(float gridSize, unsigned width , unsigned height, sf::Texture& texture);
	~TileMap();

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);
};

