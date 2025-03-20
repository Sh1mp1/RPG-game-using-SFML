#pragma once
#include "Enemy.h"
class RatEnemy :
    public Enemy
{
private:
    sf::Texture ratTexture;

    void initComponents(sf::Texture& texture_sheet);
    void initAnimations(sf::Texture& texture_sheet);
public:
    RatEnemy(const float pos_x, const float pos_y, EnemySpawner& enemy_spawner);
    ~RatEnemy();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = 0, sf::Vector2f lightPos = sf::Vector2f());
};

