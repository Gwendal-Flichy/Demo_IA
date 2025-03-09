#include "Fireball.h"

#include "Game.h"

Vec2 getFireballSize()
{
    return { 16.f, 16.f };
}

Fireball::Fireball(IGameObjectContainer& game, const Vec2& position, const Vec2& velocity,const GameObjectType& type)
    : IGameObject(game)
    , m_position(position)
    , m_velocity(velocity)
	, m_type(type)
{
    m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("point.png"));
}

void Fireball::handleInputs(const sf::Event& event)
{

}

void Fireball::update(float deltaTime)
{
    float dt = 1.f / 60.f;
    m_position += m_velocity * dt;
}

void Fireball::render(sf::RenderWindow& window)
{
    m_sprite.setOrigin(getFireballSize().x / 2.f, getFireballSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    window.draw(m_sprite);
}

OBB Fireball::getBoundingBox() const
{
    Vec2 size = getFireballSize();

    float angle = 0.0f;
    if (m_velocity.getLength() > 0.0f) {
        angle = std::atan2(m_velocity.y, m_velocity.x);
    }

    return {
        m_position,
        size / 2.0f,
        angle
    };
}

GameObjectType Fireball::gameObjectType()
{
    return m_type;
}
