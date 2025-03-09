#include "PlayerShip.h"

#include <iostream>

#include "Game.h"
#include "Fireball.h"
#include "OrbitalProjectile.h"


Vec2 getPlayerShipSize() { return { 32.f, 32.f }; }
float getPlayerShipThrust() { return 3000.f; }
float getPlayerShipRateOfTurn() { return 0.08f; }
float getPlayerShipFluidFrictionCoef() { return 10.0f; }
float getPlayerShipMaxVelocity() { return 600.f; }


PlayerShip::PlayerShip(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , m_HP(15)
	, m_MaxHP(m_HP)
    , m_angle(0.f)
    , m_position(position)
    , m_velocity(0.f, 0.f)
    , m_isDead(false)
    , m_isAccelerating(false)
	, m_firerate(0.3f)
	, m_Shooting(false)
	, m_daching(false)
	, m_isInvincible(false)
	, m_invincibility(0.7f)
	, m_dashCooldown(1.f)
	, m_dashTime(0.3f)
	, isKick(false)
	, KBTime(0.5f)  
{
    m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("point.png"));
}

void PlayerShip::handleInputs(const sf::Event& event)
{
    m_elapsedTimeFire =m_clockFire.getElapsedTime();
    

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_elapsedTimeFire.asSeconds() >= m_firerate)
        {
            m_Shooting = true;
            m_clockFire.restart();
        }

    }
    m_elapsedTimeDashCooldown = m_clockDashCooldown.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (m_elapsedTimeDashCooldown.asSeconds() >= m_dashCooldown)
        {

            m_daching = true;
            m_clockDashCooldown.restart();
            m_clockDashTime.restart();
        }

    }


    m_isAccelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    m_isDecelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    m_isTurningLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    m_isTurningRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

}

void PlayerShip::update(float deltaTime)
{
    decelerating={ 0.f, 0.f };
    acceleration={ 0.f, 0.f };
    if (m_Shooting)
    {
        m_Shooting = false;
        new Fireball(m_owner, m_position, Vec2{ 250.f * std::cos(m_angle) ,  250.f * std::sin(m_angle) },PLAYERprojectile_TYPE);
    }
    if (m_daching)
    {
        m_elapsedTimeDashTime = m_clockDashTime.getElapsedTime();

        if (m_elapsedTimeDashTime.asSeconds() >= m_dashTime)
        {

            m_daching = false;
            m_clockDashTime.restart();
        }
        
        
        acceleration += 5000 * Vec2 { std::cos(m_angle), std::sin(m_angle) };

    }
    if (isKick)
    {
        m_elapsedKBTime = m_clockKBTime.getElapsedTime();

        if (m_elapsedKBTime.asSeconds() >= KBTime)
        {

            isKick = false;
            m_clockKBTime.restart();
        }


        m_velocity -= 170 * Vec2{ std::cos(m_angle), std::sin(m_angle) };

    }
    if (m_isTurningLeft) m_angle -= getPlayerShipRateOfTurn();
    if (m_isTurningRight) m_angle += getPlayerShipRateOfTurn();

    
    if (!m_isAccelerating&&!isKick)
        acceleration = -getPlayerShipFluidFrictionCoef() * m_velocity;

    if (m_isAccelerating)
    {
	    acceleration += getPlayerShipThrust() * Vec2{std::cos(m_angle), std::sin(m_angle) };
        
    }

    if (!m_isDecelerating && !isKick)
    {
        decelerating = getPlayerShipFluidFrictionCoef() * m_velocity;
    }
    if (m_isDecelerating)
    {
        acceleration -= getPlayerShipThrust() * Vec2 { std::cos(m_angle), std::sin(m_angle) };

    }

    Vec2 PreviousPos = m_position;
    if (m_position.x > m_owner.getGame().getWindowSize().x - 200.f )
        m_position = {PreviousPos.x-0.5f,PreviousPos.y };
    else if (m_position.y > m_owner.getGame().getWindowSize().y - 150.f)
        m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
    else if (m_position.x < 200)
        m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    else if (m_position.y < 150)
        m_position = { PreviousPos.x ,PreviousPos.y+0.5f };
    else
		m_position += m_velocity * deltaTime;
    m_velocity += (acceleration-decelerating) * deltaTime;

    if (m_velocity.getLength() > getPlayerShipMaxVelocity()&&!m_daching)
        m_velocity = m_velocity * (getPlayerShipMaxVelocity() / m_velocity.getLength());
   
}

void PlayerShip::render(sf::RenderWindow& window)
{
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_daching || m_isInvincible)
    {
	    m_sprite.setColor(sf::Color(255, 50, 50, 128));
    	m_isInvincible = false;
    }
	
    m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setOrigin(getPlayerShipSize().x / 2.f, getPlayerShipSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    sf::Text HP("HP : "+std::to_string(m_HP)+" / "+ std::to_string(m_MaxHP),m_owner.getGame().font,45);
    HP.setPosition(50, 50);
    window.draw(m_sprite);
    window.draw(HP);
}

OBB PlayerShip::getBoundingBox() const
{
    Vec2 size = getPlayerShipSize();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType PlayerShip::gameObjectType()
{
    if (m_daching)
        return INVICIBLE_TYPE;
    return PLAYERSHIP_TYPE;
}

void PlayerShip::takeDamage(int dmg)
{
    m_elapsedTimeHit = m_clockHit.getElapsedTime();
    
    if (m_elapsedTimeHit.asSeconds() >= m_invincibility&&!m_daching)
    {
        m_isInvincible = true;
        m_HP -= dmg;
        if (m_HP <= 0)
            die();
        m_clockHit.restart();
    }

    
}

void PlayerShip::die()
{
    if (m_isDead)
        return;

    m_isDead = true;

    destroy();
}

Vec2 PlayerShip::getPositon() const
{
    return m_position;
}

int PlayerShip::getHP() const
{
    return m_HP;
}

float PlayerShip::getAngle() const
{
    return m_angle;
}

