#include "Barrier.h"
#include "Game.h"


Barrier::Barrier(IGameObjectContainer& game, const Vec2& center, const Vec2& size)
    : IGameObject(game)
    , m_bounds{ center, size / 2.0f, 0.0f }
{ }


Barrier::Barrier(IGameObjectContainer& game, const AABB& bbox)
    : IGameObject(game)
{
    Vec2 center = (bbox.min + bbox.max) / 2.0f;
    Vec2 extents = (bbox.max - bbox.min) / 2.0f;
    m_bounds = { center, extents, 0.0f };
}

void Barrier::handleInputs(const sf::Event& event)
{ }

void Barrier::render(sf::RenderWindow& window)
{ }

void Barrier::update(float deltaTime)
{ }

OBB Barrier::getBoundingBox() const
{
    return m_bounds;
}

GameObjectType Barrier::gameObjectType()
{
    return BARRIER_TYPE;
}