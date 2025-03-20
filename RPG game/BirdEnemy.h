#pragma once
#include "Enemy.h"
#include "EnemySpawner.h"

class BirdEnemy :
    public Enemy
{
    sf::Texture birdTexture;


    void initComponents(sf::Texture& texture_sheet);
    void initAnimations(sf::Texture& texture_sheet);
public:
    BirdEnemy(const float pos_x, const float pos_y, EnemySpawner& enemy_spawner);
    ~BirdEnemy();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = 0, sf::Vector2f lightPos = sf::Vector2f());
};

