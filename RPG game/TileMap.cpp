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
	this->gridSizeI = static_cast<int>(this->gridSizeF);

	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;

	this->maxSizeWorld.x = width * grid_size;
	this->maxSizeWorld.y = height * grid_size;

	this->layers = 3;

	this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}

	std::cout << "X : " << this->map.size() << " Y : " << this->map[0].size() << " Z : " << this->map[0][0].size() << '\n';
}

void TileMap::initTileTextureSheet()
{
	if (!this->tileSheet.loadFromFile("Textures/tilesheet.png"))
	{
		std::cout << "ERROR::TILEMAP::COULDNT LOAD TEXTURE" << '\n';
	}
}

void TileMap::initGUI()
{
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(100, 0, 0, 75));

	this->collisionBox.setOutlineThickness(1.f);
	this->collisionBox.setOutlineColor(sf::Color(150, 0, 0, 150));
}


TileMap::TileMap(float grid_size, unsigned width, unsigned height, sf::Texture& texture, const std::string texture_path)
	:tileSheet(texture), texturePath(texture_path)
{
	this->initTileMap(grid_size, width, height);
	this->initGUI();

	unsigned fromX = 0;
	unsigned fromY = 0;
	unsigned toX = 0;
	unsigned layer = 0;

}

TileMap::~TileMap()
{
	this->clearMap();
}

int TileMap::getTopLayer(sf::Vector2i mousePosGrid)
{
	if (mousePosGrid.x < this->maxSizeGrid.x && mousePosGrid.y < this->maxSizeGrid.y && mousePosGrid.x >= 0 && mousePosGrid.y >= 0)
	{
		for (int i = 0; i < this->layers; ++i)
		{
			if (this->map[mousePosGrid.x][mousePosGrid.y][i] == nullptr)
			{
				return i;
			}
		}
		return this->layers;
	}
	else
	{
		return 0;
	}
	
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
		out_file << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << '\n'
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
		sf::Vector2i size;
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

		this->maxSizeGrid = static_cast<sf::Vector2i>(size);
		this->gridSizeF = grid_size;
		this->gridSizeI = static_cast<int>(this->gridSizeF);
		this->layers = layers;
		this->texturePath = texture_path;

		this->maxSizeWorld = sf::Vector2f(size.x * grid_size, size.y * grid_size);

		this->maxSizeWorldGrid = sf::Vector2i(
			static_cast<unsigned>(this->maxSizeWorld.x) / static_cast<unsigned>(this->gridSizeI),
			static_cast<unsigned>(this->maxSizeWorld.y) / static_cast<unsigned>(this->gridSizeI)
		);


		//Initializing tiles
		this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());
		for (int x = 0; x < this->maxSizeGrid.x; ++x)
		{
			this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());
			for (int y = 0; y < this->maxSizeGrid.y; ++y)
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
				this->gridSizeI, this->gridSizeI),type, collision);
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULDNT LOAD TILEMAP FROM PATH : '" << path << "'" << '\n';
	}
	in_file.close();
}

void TileMap::addTile(const int x, const int y, const sf::IntRect& texture_rect, const short type, const bool collision)
{
	/*
	Takes 3 coordinates from mouse position and adds tile to that position
	*/

	
	if (x < this->maxSizeGrid.x && y < this->maxSizeGrid.y &&
		x >= 0 && y >= 0)
	{
		sf::IntRect previous_texture_rect(0, 0, 0, 0);
		for (int z = 0; z < this->layers; ++z)
		{

			if (this->map[x][y][z])
			{
				previous_texture_rect = this->map[x][y][z]->getTextureRect();
			}


			if (this->map[x][y][z] == nullptr && texture_rect != previous_texture_rect)	//Checks if the tile already added previously doesnt have the texture to be added now
			{
				this->map[x][y][z] = new Tile(sf::Vector2u(x, y), this->gridSizeF, this->tileSheet, texture_rect, type, collision);
				break;
			}
		}
	}

}

void TileMap::removeTile(const int x, const int y)
{
	/*
	Takes 3 coordinates from mouse position and removes the tile at that position
	*/

	if (x < this->maxSizeGrid.x && y < this->maxSizeGrid.y &&	//checks if the coordinates are valid i.e. not out of range of the array
		x >= 0 && y >= 0)
	{
		for (int z = this->layers - 1; z >= 0; --z)
		{
			if (this->map[x][y][z] != nullptr)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
				break;
			}
		}
	}
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{				
	//Window / tilemap edge collision
	if (entity)																			
	{																									 
		sf::RectangleShape hitbox = entity->getHitbox();												 
		sf::FloatRect hitbox_bounds = hitbox.getGlobalBounds();		

		if (hitbox_bounds.left < 0.f)
		{
			float overlap = -hitbox_bounds.left;																 
			entity->moveConstant(sf::Vector2f(overlap, 0.f));	
			entity->updateHitboxComponent();
			//entity->resetVelocityX();
		}
		else if (hitbox_bounds.left + hitbox_bounds.width > this->maxSizeWorld.x)
		{
			float overlap = (hitbox_bounds.left + hitbox_bounds.width) - this->maxSizeWorld.x;						 
			entity->moveConstant(sf::Vector2f(-overlap, 0.f));
			entity->updateHitboxComponent();
			//entity->resetVelocityX();
		}

		if (hitbox_bounds.top < 0.f)
		{
			float overlap = -hitbox_bounds.top;
			entity->moveConstant(sf::Vector2f(0.f, overlap));
			entity->updateHitboxComponent();
			//entity->resetVelocityY();
		}
		else if (hitbox_bounds.top + hitbox_bounds.height > this->maxSizeWorld.y)
		{
			float overlap = (hitbox_bounds.top + hitbox_bounds.height) - this->maxSizeWorld.y;
			entity->moveConstant(sf::Vector2f(0.f, -overlap));
			entity->updateHitboxComponent();
			//entity->resetVelocityY();
		}


		//TODO FIX THE TILE COLLISION=========================================================================================================================================


		//Tile collision
		this->layer = 0;

		if (entity->getGridPosition(this->gridSizeI).x >= 1)
		{
			this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
		}
		else
		{
			this->fromX = 0;
		}

		if (entity->getGridPosition(this->gridSizeI).y >= 1)
		{
			this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
		}
		else
		{
			this->fromY = 0;
		}

		this->toX = entity->getGridPosition(this->gridSizeI).x + 3;

		if (this->toX > this->maxSizeWorldGrid.x)
		{
			this->toX = this->maxSizeWorldGrid.x;
		}

		this->toY = entity->getGridPosition(this->gridSizeI).y + 3;

		if (this->toY > this->maxSizeWorldGrid.y)
		{
			this->toY = this->maxSizeWorldGrid.y;
		}

		//TODO FIX THIS SHIT=============================================================================================

		/*
		sf::FloatRect next_bounds = entity->getNextBounds();

		for (int x = this->fromX; x < this->toX; ++x)
		{
			for (int y = this->fromY; y < toY; ++y)
			{
				if (this->map[x][y][this->layer])
				{
					sf::FloatRect tile_bounds = this->map[x][y][this->layer]->getBounds();
					if (next_bounds.intersects(tile_bounds) && this->map[x][y][this->layer]->hasCollision())
					{
						if (entity->getNextBoundsX().intersects(tile_bounds))
						{
							entity->resetVelocityX();
							std::cout << "LEFT" << '\n';
						}

						if (entity->getNextBoundsY().intersects(tile_bounds))
						{
							entity->resetVelocityY();
							std::cout << "TOP" << '\n';
						}
					}
				}
			}
		}
		*/



		for (int x = this->fromX; x < this->toX; ++x)
		{
			for (int y = this->fromY; y < toY; y++)
			{
				if (this->map[x][y][this->layer])
				{

					sf::FloatRect tile_bounds = this->map[x][y][this->layer]->getBounds();
					if (hitbox_bounds.intersects(tile_bounds) && this->map[x][y][this->layer]->hasCollision())
					{
						sf::FloatRect playerBounds = hitbox_bounds;
						sf::FloatRect wallBounds = hitbox_bounds;


						/*if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
						{
						entity->resetVelocityY();
						entity->setPosition(sf::Vector2f(playerBounds.left, wallBounds.top - playerBounds.height));
						}

						//Top collision
						else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
						{
						entity->resetVelocityY();
						entity->setPosition(sf::Vector2f(playerBounds.left, wallBounds.top + wallBounds.height));
						}

						//Right collision
						if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
						{
						entity->resetVelocityX();
						entity->setPosition(sf::Vector2f(wallBounds.left - playerBounds.width, playerBounds.top));
						}

						//Left collision
						else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
						{
						entity->resetVelocityX();
						entity->setPosition(sf::Vector2f(wallBounds.left + wallBounds.width, playerBounds.top));
						}*/











						//std::cout << "INTERSECTION";
						//Check overlap in each direction with respect to player
						float overlapLeft = (tile_bounds.left + tile_bounds.width) - hitbox_bounds.left;
						float overlapRight = (hitbox_bounds.left + hitbox_bounds.width) - (tile_bounds.left);
						float overlapTop = (tile_bounds.top + tile_bounds.height) - (hitbox_bounds.top);
						float overlapBottom = (hitbox_bounds.top + hitbox_bounds.height) - (tile_bounds.top);

						std::vector<float> overlap = { overlapLeft, overlapRight, overlapTop, overlapBottom };

						float smallestOverlap = *std::min_element(overlap.begin(), overlap.end());

						if (smallestOverlap == overlapLeft)
						{
							entity->resetVelocityX();
							//entity->setPosition(sf::Vector2f(tile_bounds.left + tile_bounds.width, hitbox.getPosition().y));
							entity->moveConstant(sf::Vector2f(overlapLeft, 0.f));	//Moves player to the right
							//entity->updateHitboxComponent();
							//std::cout << "LEFT" << '\n';
						}
						else if (smallestOverlap == overlapRight)
						{
							entity->resetVelocityX();
							//entity->setPosition(sf::Vector2f(tile_bounds.left - (hitbox_bounds.width + 2.f), hitbox.getPosition().y));
							entity->moveConstant(sf::Vector2f(-overlapRight, 0.f));	//Moves player to the left
							//entity->updateHitboxComponent();
							//std::cout << "RIGHT" << '\n';
						}

						if (smallestOverlap == overlapTop)
						{
							entity->resetVelocityY();
							//entity->setPosition(sf::Vector2f(hitbox.getPosition().x, tile_bounds.top + tile_bounds.height));
							entity->moveConstant(sf::Vector2f(0.f, overlapTop));	//Moves player downward
							//entity->updateHitboxComponent();
							//std::cout << "TOP" << '\n';


						}
						else if (smallestOverlap == overlapBottom)
						{
							entity->resetVelocityY();
							//entity->setPosition(sf::Vector2f(hitbox.getPosition().x, tile_bounds.top - hitbox_bounds.height));
							entity->moveConstant(sf::Vector2f(0.f, -overlapBottom));	//Moves player upward
							//entity->updateHitboxComponent();
							//std::cout << "BOTTOM" << '\n';
						}
					}
				}				
			}
		}

			
		//TODO:- FIX THIS SHIT===============================================================================================================================
		// 
		//if (hitbox.getPosition().x < 0.f)																			 
		//{
		//	std::cout << hitbox.getPosition().x << " " << hitbox.getPosition().y << '\n';
		//	entity->setPosition(sf::Vector2f(0.f, hitbox.getPosition().y));
		//}																								 
		//if (bounds.left + bounds.width > this->maxSizeWorld.x)										 
		//{	
		//	std::cout << "CURRENT " <<  bounds.left + bounds.width << " " << this->maxSizeWorld.x << '\n'
		//		<< "SETTING " << this->maxSizeWorld.x - bounds.width << " " << hitbox.getPosition().y << '\n';
		//	entity->setPosition(sf::Vector2f(this->maxSizeWorld.x - hitbox.getSize().x, hitbox.getPosition().y));
		//}
		//
		////std::cout << this->maxSizeWorld.x << " " << this->maxSizeWorld.y << '\n';
		//																								 
		//if (bounds.top < 0.f)																			 
		//{														
		//	entity->setPosition(sf::Vector2f(hitbox.getPosition().x, 0.f));
		//}																								 
		//if (bounds.top + bounds.height > this->maxSizeWorld.y)										 
		//{	
		//	entity->setPosition(sf::Vector2f(hitbox.getPosition().x, this->maxSizeWorld.y - bounds.height));
		//}																								 
	}																									 
}																										 
																										 
//Functions																								 
																										 
void TileMap::update(Entity* entity, const float& dt)													 
{																										 
	this->updateCollision(entity, dt);																	 
}																										 
																										 
void TileMap::render(sf::RenderTarget& target, sf::Vector2i grid_pos, bool draw_collision_box)
{

	sf::Vector2i window_size = static_cast<sf::Vector2i>(target.getSize());
	sf::Vector2i number_of_tiles = window_size / this->gridSizeI;

	this->fromX = grid_pos.x - ((number_of_tiles.x / 2) + 1);
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}

	this->toX = grid_pos.x + ((number_of_tiles.x / 2) + 2);
	if (this->toX > this->maxSizeGrid.x)
	{
		this->toX = this->maxSizeGrid.x;
	}

	this->fromY = grid_pos.y - ((number_of_tiles.y / 2) + 1);
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}

	this->toY = grid_pos.y + ((number_of_tiles.y / 2) + 2);
	if (this->toY > this->maxSizeGrid.y)
	{
		this->toY = this->maxSizeGrid.y;
	}

	for (int x = this->fromX; x < this->toX; ++x)
	{
		for (int y = this->fromY; y < this->toY; ++y)
		{
			for (int z = 0; z < this->layers; ++z)
			{
				if (this->map[x][y][z])
				{
					this->map[x][y][z]->render(target);
					if (this->map[x][y][z]->hasCollision() && draw_collision_box)
					{
						this->collisionBox.setPosition(this->map[x][y][z]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}

	/*if (entity)
	{
		
	}
	else
	{
		for (int x = 0; x < this->map.size(); ++x)
		{
			for (int y = 0; y < this->map[x].size(); ++y)
			{
				for (int z = 0; z < this->layers; ++z)
				{
					if (this->map[x][y][z])
					{
						this->map[x][y][z]->render(target);
						if (this->map[x][y][z]->hasCollision() && draw_collision_box)
						{
							this->collisionBox.setPosition(this->map[x][y][z]->getPosition());
							target.draw(this->collisionBox);
						}
					}

				}
			}
		}
	}*/

	





	/*if (entity)
	{
		
	}

	
	else
	{
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					if (z)
					{
						z->render(target);
						if (z->hasCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);
						}
					}

				}
			}
		}
	}	*/
}																										 
																										 