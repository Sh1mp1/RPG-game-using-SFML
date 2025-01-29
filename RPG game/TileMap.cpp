#include "stdafx.h"
#include "TileMap.h"

void TileMap::initTileMap(float grid_size, unsigned width, unsigned height)
{
	this->gridSizeF = grid_size;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = width;
	this->mapSize.y = height;
	this->layers = 1;

	this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
	for (int x = 0; x < this->mapSize.x; ++x)
	{
		this->map[x].resize(this->mapSize.y, std::vector<Tile*>());
		for (int y = 0; y < this->mapSize.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}
}

void TileMap::initTileTextureSheet()
{
	if (!this->tileSheet.loadFromFile("Textures/tilesheet.png"))
	{
		std::cout << "ERROR::TILEMAP::COULDNT LOAD TEXTURE" << '\n';
	}
}

TileMap::TileMap(float grid_size, unsigned width, unsigned height, sf::Texture& texture)
	:tileSheet(texture)
{
	this->initTileMap(grid_size, width, height);
	//this->initTileTextureSheet();
}

TileMap::~TileMap()
{
	for (int x = 0; x < this->map.size(); ++x)
	{
		for (int y = 0; y < this->map[x].size(); ++y)
		{
			for (int z = 0 ; z < this->layers; ++z)
			{
				delete this->map[x][y][z];
			}
		}
	} 
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	/*
	Takes 3 coordinates from mouse position and adds tile to that position
	*/

	

	if (x < this->mapSize.x && y < this->mapSize.y && z < this->layers &&
		x >= 0 && y >= 0 && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(sf::Vector2f(x, y) * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
		}
	}

}

void TileMap::removeTile(const unsigned x, const unsigned y , const unsigned z)
{
	/*
	Takes 3 coordinates from mouse position and removes the tile at that position
	*/

	if (x < this->mapSize.x && y < this->mapSize.y && z < this->layers &&	//checks if the coordinates are valid i.e. not out of range of the array
		x >= 0 && y >= 0 && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

//Functions

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z)
					z->render(target);
			}
		}
	}
}
