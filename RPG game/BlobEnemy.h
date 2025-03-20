#pragma once
#include "Enemy.h"
class BlobEnemy :
    public Enemy
{
private:
    sf::Texture blobTexture;

    void initComponents(sf::Texture& texture_sheet);
    void initAnimations(sf::Texture& texture_sheet);
public:
    BlobEnemy(const float pos_x, const float pos_y, EnemySpawner& enemy_spawner);
    ~BlobEnemy();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = 0, sf::Vector2f lightPos = sf::Vector2f());

};

