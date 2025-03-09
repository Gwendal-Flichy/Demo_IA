#pragma once

#include "IGameObject.h"
#include "Tree.h"
#include <SFML/Graphics.hpp>

#include "PlayerShip.h"

class IGameObjectContainer;

class Boss : public IGameObject
{
public:
    Boss(IGameObjectContainer& game, const Vec2& position);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB getBoundingBox() const override;
    GameObjectType gameObjectType() override;
    void takeDamage(int dmg = 1);
    void die();

    void fireWithPistol() const;
    void fireWithShotgun()const;
    void Laser();
    void RightMelee();
    void LeftMelee();
    void Kick();

    bool findValidTarget();
    bool isCurrentTargetValid() const;
    void setSpeed(const int& Speed);
    float calculateAngleToTarget() const;
    void Dash(const float& angle);

    Vec2 getPosition() const;
    Vec2 getDistanceToPlayer() const;
    Vec2 getDistanceToCenter() const;
    Vec2 getCenter()const;
    int getHP()const;
    int getMaxHP()const;
    bool IsKickedPlayer()const;
    bool m_dashing;
    float SpeedLimit;
    bool GoingToCenter;
private:
    int m_speed;
    float m_angle;

    int m_HP;
    int m_MaxHP;
    bool m_isDead;
    bool m_isInvincible;
    sf::Sprite m_sprite;
    BT::RootNode m_rootNode;
    Vec2 m_position;
    Vec2 m_velocity;
    std::vector<IGameObject*> m_allGameObjects;
    PlayerShip* m_currentTarget;
};

