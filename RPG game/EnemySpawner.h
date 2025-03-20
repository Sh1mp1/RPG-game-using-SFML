#pragma once
#include "Tile.h"
class EnemySpawner :
    public Tile
{
private:

    short enemyType;


    int noOfEnemies;    //Total no. of enemies the tile has spawned
    int maxEnemies;     //Total no. of enemies the tile can spawn

    float timer;
    float timerMax; //Stores the delay for spawning enemies

    bool canSpawn;  //Stores whether the tile should spawn an enemy


public:
    EnemySpawner(sf::Vector2u grid_pos, float gridSize, const sf::Texture& texture, const sf::IntRect& texture_rect, const short enemy_type);

    ~EnemySpawner();


    const bool getCanSpawn(); //Returns true if the tile should spawn an enemy, if true the value is reset to false
    const short getEnemyType() const;

    const std::string getString() const;

    void addEnemy();
    void removeEnemy();


    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos);
};

