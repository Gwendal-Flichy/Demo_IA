#pragma once

#include "IGameObject.h"
#include <SFML/Graphics.hpp>

class IGameObject;

class OrbitalProjectile : public IGameObject
{
public:
    OrbitalProjectile(IGameObjectContainer& game, IGameObject* owner,
        float initialAngle, float orbitalRadius, float angularSpeed, float totalAngleToDestroy, float Width, float Height, const GameObjectType& type);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB getBoundingBox() const override;
    GameObjectType gameObjectType() override;

private:
    sf::Sprite m_sprite;
    IGameObject* m_owner;
    Vec2 m_position;
    Vec2 m_velocity;
    GameObjectType m_type;
    float m_orbitalRadius;
    float m_angle;
    float m_initialAngle;
    float m_angularSpeed;
    float m_endAngle;
    bool m_hasEndAngle;
    float m_totalRotation;
    float m_totalAngleToDestroy;
    float m_Width;
    float m_Height;
    Vec2 getOwnerPosition() const;
    bool IsOwnerDead() const;
};