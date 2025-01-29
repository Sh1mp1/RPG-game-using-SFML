#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size, unsigned width, unsigned height)
{
	this->gridSizeF = grid_size;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = width;
	this->mapSize.y = height;
	this->layers = 1;

	this->map.resize(this->mapSize.x);

	for (int x = 0; x < this->mapSize.x; ++x)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());
		this->map[x].resize(this->mapSize.y);
		for (int y = 0; y < this->mapSize.y; ++y)
		{
			this->map[x].push_back(std::vector<Tile*>());
			this->map[x][y].resize(this->layers);
			for (int z = 0; z < this->layers; ++z)
			{
				//this->map[x][y].push_back(new Tile(sf::Vector2f(x * this->gridSizeF, y * this->gridSizeF), this->gridSizeF));

				this->map[x][y].push_back(nullptr);
			}

		}
	}
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

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*
	Takes 2 coordinates from mouse position and adds tile to that position
	*/

	

	if (x < this->mapSize.x && y < this->mapSize.y && z < this->layers &&
		x >= 0 && y >= 0 && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(sf::Vector2f(x, y) * this->gridSizeF, this->gridSizeF);
			std::cout << "added tile" << '\n';
		}
	}

}

void TileMap::removeTile()
{
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
