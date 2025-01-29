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
		
public:
	TileMap(float gridSize, unsigned width , unsigned height);
	~TileMap();

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z);
	void removeTile();

	void update();
	void render(sf::RenderTarget& target);
};

