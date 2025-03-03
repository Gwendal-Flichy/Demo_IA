#pragma once

#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class IGameObjectContainer;

class Fireball : public IGameObject
{
public:
    Fireball(IGameObjectContainer& game, const Vec2& position, const Vec2& velocity, const GameObjectType& type);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    OBB getBoundingBox() const override;
    GameObjectType gameObjectType() override;

private:
    sf::Sprite m_sprite;

    Vec2 m_position;
    Vec2 m_velocity;
    GameObjectType m_type;
};


