#include "stdafx.h"
#include "TileMap.h"

void TileMap::clearMap()
{
	for (int x = 0; x < this->map.size(); ++x)
	{
		for (int y = 0; y < this->map[x].size(); ++y)
		{
			for (int z = 0; z < this->layers; ++z)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

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


TileMap::TileMap(float grid_size, unsigned width, unsigned height, sf::Texture& texture, const std::string texture_path)
	:tileSheet(texture), texturePath(texture_path)
{
	this->initTileMap(grid_size, width, height);
}

TileMap::~TileMap()
{
	this->clearMap();
}

//Functions

void TileMap::savetoFile(const std::string path)
{
	/*
	Saves the entire map to a text file
	Format:-
	Size: x, y
	gridSize
	layers
	texture (file path)

	(ALL TILES)
	gridPos x, y (all tiles) , textureRect left, top , collision , type
	*/

	std::ofstream out_file;

	out_file.open(path);

	if (out_file.is_open())
	{
		out_file << this->mapSize.x << " " << this->mapSize.y << '\n'
			<< this->gridSizeF << '\n'
			<< this->layers << '\n'
			<< this->texturePath << '\n';

		for (int x = 0; x < this->map.size(); ++x)
		{
			for (int y = 0; y < this->map[x].size(); ++y)
			{
				for (int z = 0; z < this->layers; ++z)
				{
					//out_file << 0 << 0 << 0 << 0 << " ";

					if (this->map[x][y][z])
					{
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getString() << "\n";
					}
				}
			}
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULDNT SAVE TILEMAP TO PATH : '" << path << "'" << '\n';
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string path)
{/*
	Loads the entire map from a text file
	Format:-
	Size: x, y
	gridSize
	layers
	texture (file path)

	(ALL TILES)
	gridPos x, y (all tiles) , textureRect left, top , collision , type
	*/

	std::ifstream in_file;

	in_file.open(path);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		float grid_size = 0;
		unsigned layers = 0;
		std::string texture_path;
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned texture_rect_left = 0;
		unsigned texture_rect_top = 0;
		bool collision = false;;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> grid_size >> layers >> texture_path;

		this->mapSize = size;
		this->gridSizeF = grid_size;
		this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->layers = layers;
		this->texturePath = texture_path;




		//Initializing tiles
		this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			this->map[x].resize(this->mapSize.y, std::vector<Tile*>());
			for (int y = 0; y < this->mapSize.y; ++y)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}

		if (!this->tileSheet.loadFromFile(this->texturePath))
		{
			std::cout << "ERROR::TILEMAP::COULDNT LOAD TEXTURE FROM PATH : " << this->texturePath << '\n';
		}

		//Load all tiles
		while (in_file >> x >> y >> z >> texture_rect_left >> texture_rect_top >> collision >> type)
		{
			this->map[x][y][z] = new Tile(sf::Vector2u(x, y), this->gridSizeF, this->tileSheet, sf::IntRect(texture_rect_left, texture_rect_top,
				this->gridSizeU, this->gridSizeU),type, collision);
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULDNT LOAD TILEMAP FROM PATH : '" << path << "'" << '\n';
	}
	in_file.close();
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
			this->map[x][y][z] = new Tile(sf::Vector2u(x, y), this->gridSizeF, this->tileSheet, texture_rect, TileTypes::DEFAULT, false);
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
