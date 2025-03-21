#pragma once
#include "Entity.h"
#include "EnemySpawner.h"
#include "GUI.h"

class Enemy :
    public Entity
{
private:
    //Initialization functions 
    virtual void initComponents(sf::Texture& texture_sheet) = 0;
    virtual void initAnimations(sf::Texture& texture_sheet) = 0;
    void initHpBar();
protected:
    EnemySpawner& enemySpawner;

    gui::ProgressBar* hpBar;
    sf::Vector2f hpBarPos;

    int damage;
    int exp;

    float attackCooldown;
    float attackCooldownMax;

public:
    Enemy(const float pos_x, const float pos_y, sf::Texture& texture_sheet, EnemySpawner& enemy_spawner);
    ~Enemy();

    const EnemySpawner& getSpawner() const;
    AttributeComponent& getAttributeComponent() const;
    const bool canAttack();
    const int getExp() const;

    void removeEnemy();

    void updateAttackCooldown(const float& dt);
    virtual void updateAnimation(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = 0, sf::Vector2f lightPos = sf::Vector2f()) = 0;
};

