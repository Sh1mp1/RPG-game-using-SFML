#pragma once
#include "Tile.h"

class TileMap
{
private:
	void clearMap();

	float gridSizeF;
	unsigned gridSizeU;
	
	sf::Vector2u mapSize;	//Total no. of tiles in both x and y axes
	unsigned layers;		//No of tiles in z axis
	std::vector<std::vector<std::vector<Tile*>>> map;

	std::string texturePath;

	sf::Texture& tileSheet;

	//Initialization functions
	void initTileMap(float grid_size, unsigned width, unsigned height);
	void initTileTextureSheet();
	

public:
	TileMap(float gridSize, unsigned width , unsigned height, sf::Texture& texture, const std::string texture_path);
	~TileMap();

	//Functions
	void savetoFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget& target);

};

