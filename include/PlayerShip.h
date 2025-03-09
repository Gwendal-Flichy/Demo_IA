#pragma once

#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class IGameObjectContainer;

class PlayerShip : public IGameObject
{
public:
    PlayerShip(IGameObjectContainer& game, const Vec2& position);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB  getBoundingBox() const override;
    virtual GameObjectType gameObjectType() override;
    void takeDamage(int dmg = 1);
    void die();
    Vec2 getPositon() const;
    int getHP() const;
    float getAngle() const;

    bool isKick;
private:
    sf::Sprite m_sprite;

    //  Inputs
    bool m_isAccelerating;
    bool m_isTurningLeft;
    bool m_isTurningRight;
    bool m_isDecelerating;

    //  Gameplay
    int m_HP;
    int m_MaxHP;
    bool m_isDead;

    //  Physics
    float m_angle;
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 acceleration;
    Vec2 decelerating;
    bool m_isInvincible;
    bool m_daching;
    bool m_Shooting;
    const float m_dashCooldown;
    const float m_dashTime;
    const float m_firerate;
    const float m_invincibility;
    const float KBTime;
    sf::Clock m_clockFire;
    sf::Time m_elapsedTimeFire;
    sf::Clock m_clockHit;
    sf::Time m_elapsedTimeHit;
    sf::Clock m_clockDashCooldown;
    sf::Time m_elapsedTimeDashCooldown;
    sf::Clock m_clockDashTime;
    sf::Time m_elapsedTimeDashTime;
    sf::Clock m_clockKBTime;
    sf::Time m_elapsedKBTime;
};


