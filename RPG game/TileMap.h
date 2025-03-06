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
	
	sf::Vector2i maxSizeGrid;	//Total no. of tiles in both x and y axes.
	sf::Vector2f maxSizeWorld;	//Total size of entire tile sheet 1920 x 1080 if it only spans across the window
	sf::Vector2i maxSizeWorldGrid;

	int layers;		//No. of tiles in z axis
	std::vector<std::vector<std::vector<Tile*>>> map;

	std::string texturePath;

	sf::Texture& tileSheet;

	sf::RectangleShape collisionBox;

	std::stack<Tile*> deferredTiles;

	//Culling
	int fromX;
	int fromY;
	int toX;
	int toY;
	int layer;

	//Initialization functions
	void initTileMap(float grid_size, unsigned width, unsigned height);
	void initTileTextureSheet();
	void initGUI();
public:
	TileMap(float gridSize, unsigned width , unsigned height, sf::Texture& texture, const std::string texture_path);
	~TileMap();

	//Accessors
	// 
	//Returns the total number of tiles added to a grid position
	int getTopLayer(sf::Vector2i mousePosGrid);	

	//Returns the total size of tileMap
	const sf::Vector2f getMaxSizeWorld() const;

	//Functions
	void savetoFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const int x, const int y, const sf::IntRect& texture_rect, const short type = 0, const bool collision = false);
	void removeTile(const int x, const int y);

	void updateCollision(Entity* entity, const float& dt);

	void update(Entity* entity, const float& dt);
	void render(sf::RenderTarget& target,  sf::Vector2i grid_pos , bool draw_collision_box = false, sf::Shader* shader = nullptr, const sf::Vector2f playerPos = sf::Vector2f());

	void deferredRender(sf::RenderTarget& target, sf::Vector2i grid_pos, bool draw_collision_box = false, sf::Shader* shader = nullptr, const sf::Vector2f playerPos = sf::Vector2f());
};

