
#include "OrbitalProjectile.h"

#include "Game.h"
#include "PlayerShip.h"
#include "Boss.h"


#define PI  3.14159265f
#define TWO_PI  (2.0f * PI)


float normalizeAngle(float angle) {
    while (angle >= TWO_PI)
        angle -= TWO_PI;
    while (angle < 0.0f)
        angle += TWO_PI;
    return angle;
}


float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

Vec2 getOrbitalProjectileSize()
{
    return { 64.f, 16.f };
}

OrbitalProjectile::OrbitalProjectile(IGameObjectContainer& game, IGameObject* owner,
    float initialAngle, float orbitalRadius, float angularSpeed, float totalAngleToDestroy,float Width,float Height,const GameObjectType& type)
    : IGameObject(game)
    , m_owner(owner)
    , m_orbitalRadius(orbitalRadius)
    , m_angle(initialAngle)
    , m_initialAngle(initialAngle)
    , m_angularSpeed(angularSpeed)
    , m_velocity(0.f, 0.f)
    , m_position(0.f, 0.f)
    , m_hasEndAngle(totalAngleToDestroy > 0.0f)
    , m_totalRotation(0.f)
	, m_totalAngleToDestroy(totalAngleToDestroy)
	, m_type(type)
	, m_Width(Width)
	, m_Height(Height)
{

    m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("point.png"));


    if (m_hasEndAngle)
    {

        m_angle = degreesToRadians(m_angle);
        m_initialAngle = degreesToRadians(m_initialAngle);
    	m_totalAngleToDestroy = degreesToRadians(m_totalAngleToDestroy);

        m_endAngle = normalizeAngle(m_initialAngle + m_totalAngleToDestroy);
    }
    else
    {
        m_endAngle = -1.0f;
    }


    Vec2 ownerPos = getOwnerPosition();
    m_position.x = ownerPos.x + m_orbitalRadius * std::cos(m_angle);
    m_position.y = ownerPos.y + m_orbitalRadius * std::sin(m_angle);
}

void OrbitalProjectile::handleInputs(const sf::Event& event)
{
}

void OrbitalProjectile::update(float deltaTime)
{
    if (IsOwnerDead())
    {
        destroy();
    }
    Vec2 ownerPos = getOwnerPosition();


    float previousAngle = m_angle;


    m_angle += m_angularSpeed * deltaTime;
    m_angle = normalizeAngle(m_angle);


    float deltaAngle = m_angle - previousAngle;
    if (deltaAngle < -PI)
        deltaAngle += TWO_PI;
    else if (deltaAngle > PI)
        deltaAngle -= TWO_PI;


    m_totalRotation += std::abs(deltaAngle);


    bool shouldDestroy = false;

    if (m_hasEndAngle)
    {

        if (m_totalRotation >= std::abs(m_totalAngleToDestroy))
        {
            shouldDestroy = true;
        }

        if (shouldDestroy)
        {
            destroy();
            return;
        }
    }

    m_position.x = ownerPos.x + m_orbitalRadius * std::cos(m_angle);
    m_position.y = ownerPos.y + m_orbitalRadius * std::sin(m_angle);
}

void OrbitalProjectile::render(sf::RenderWindow& window)
{
    m_sprite.setOrigin(m_Width / 2.f, m_Height / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    m_sprite.setRotation(m_angle * 180.f / PI);
    window.draw(m_sprite);
}

OBB OrbitalProjectile::getBoundingBox() const
{
    Vec2 size = { m_Width ,m_Height };
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType OrbitalProjectile::gameObjectType()
{
    return m_type;
}

Vec2 OrbitalProjectile::getOwnerPosition() const
{
    if (!m_owner)
        return { 0.f, 0.f };

    switch (m_owner->gameObjectType())
    {
    case PLAYERSHIP_TYPE:
        return static_cast<PlayerShip*>(m_owner)->getPositon();
    case ENEMY_TYPE:
        return static_cast<Boss*>(m_owner)->getPosition();
    default:
        OBB ownersOBB = m_owner->getBoundingBox();
        return ownersOBB.center;
    }
}

bool OrbitalProjectile::IsOwnerDead() const
{
    if (!m_owner)
        return true;

    switch (m_owner->gameObjectType())
    {
    case PLAYERSHIP_TYPE:
        return static_cast<PlayerShip*>(m_owner)->getHP() <=0;
    case ENEMY_TYPE:
        return static_cast<Boss*>(m_owner)->getHP() <= 0;
    default:
        return true;
    }
}