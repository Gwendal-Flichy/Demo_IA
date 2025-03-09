#include "Boss.h"

#include "BossBehavior.h"
#include "Fireball.h"
#include "Game.h"
#include "OrbitalProjectile.h"


int getPistolBulletSpeed() { return 300; }
int getShotGunBulletSpeed() { return 220; }
float getBossFluidFrictionCoef() { return 5.0f; }

Vec2 getBossSize()
{
    return { 72.f, 72.f };
}

Vec2 getVelo() { return { 32.f, 32.f }; }

Boss::Boss(IGameObjectContainer& game, const Vec2& position)
    : IGameObject(game)
    , m_position(position)
    , m_velocity(0,0)   
	,m_rootNode(this)
	,m_speed(0)
	, m_dashing(false)
	, m_isDead(false)
	, m_HP(50)
	, m_MaxHP(m_HP)
	, SpeedLimit(0)
	, GoingToCenter(false)
{
    m_sprite.setTexture(getOwner().getGame().getTextureCache().getTexture("point.png"));

		//Phase 1 du boss
        auto* behavior = new BT::Retry(&m_rootNode);
        auto* Combo1 = new BT::PlayerDictance(behavior, 0.f, 150.f);
        auto* Combo2 = new BT::PlayerDictance(behavior, 160.f, 600);
        auto* Combo3 = new BT::PlayerDictance(behavior, 610.f, 700.f);
        auto* Combo4 = new BT::PlayerDictance(behavior, 690.f, 2000.f);

        auto* SequenceP1_1 = new BT::Sequence(Combo1);
        new BT::Sprint(SequenceP1_1);
        //new BT::Walk(SequenceP1_4);
        new BT::DoKick(SequenceP1_1);
        new BT::FireShotgunAfterKick(SequenceP1_1);

        auto* SequenceP1_2 = new BT::Sequence(Combo2);
        new BT::Walk(SequenceP1_2);
        new BT::FirePistol(SequenceP1_2);

        auto* SequenceP1_3 = new BT::Sequence(Combo3);
        new BT::Sprint(SequenceP1_3);
        new BT::FirePistol(SequenceP1_3);

        auto* SequenceP1_4 = new BT::Sequence(Combo4);
        new BT::Idle(SequenceP1_4);
        new BT::Dash(SequenceP1_4, 20, 7, 45);
        new BT::Dash(SequenceP1_4, 20, 2);
        new BT::DoubleMelee(SequenceP1_4);

        
        //Phase 2 du boss
        auto* Second = new BT::SecondPhase(behavior);
        new BT::IsPlayerDead(behavior);
        auto* SequenceP2_1 = new BT::Sequence(Second);
        auto* debutP2 = new BT::Retry(SequenceP2_1);

        new BT::GotoCenter(debutP2);
        new BT::Walk(debutP2);
        new BT::IsInCenter(debutP2);
        new BT::Idle(debutP2);
        new BT::FireLaser(debutP2);


        auto* P2 = new BT::Retry(SequenceP2_1);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                new BT::FireShotgun(P2);
            }

            new BT::FireLaser(P2);
        }
        auto* untilTheEnd = new BT::DoUntilFailure(P2);

        new BT::FireLaser(untilTheEnd);


        new BT::IsPlayerDead(P2);
        

        

        
        


}
Vec2 Boss::getCenter()const
{
    return Vec2{ m_owner.getGame().getWindowSize().x / 2.f,m_owner.getGame().getWindowSize().y / 2.f};
}

Vec2 Boss::getDistanceToPlayer() const
{
	return m_currentTarget->getPositon() - m_position;
}
Vec2 Boss::getDistanceToCenter() const
{
    return getCenter() - m_position;
}


float Boss::calculateAngleToTarget() const
{
    if (!m_currentTarget)
        return m_angle;


    Vec2 directionToPlayer = getDistanceToPlayer();
    if (GoingToCenter)
        directionToPlayer = getDistanceToCenter();
    return std::atan2(directionToPlayer.y, directionToPlayer.x);
}

bool Boss::findValidTarget()
{
    

    for (auto& target : m_allGameObjects)
    {
        if (target->gameObjectType()==PLAYERSHIP_TYPE)
        {
            m_currentTarget = static_cast<PlayerShip*>(target);
            if (isCurrentTargetValid())
				return true;

        }

    }
    return false;

}

bool Boss::isCurrentTargetValid() const
{
    if (m_currentTarget->getHP() <= 0)
        return false;

    return true;
}
void Boss::setSpeed(const int& Speed)
{
    m_speed = Speed;
}

void Boss::fireWithPistol()const
{
    
    new Fireball(m_owner, m_position, Vec2{ getPistolBulletSpeed() * std::cos(m_angle) ,  getPistolBulletSpeed() * std::sin(m_angle) },ENEMYprojectile_TYPE);

}

void Boss::fireWithShotgun()const
{
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle) ,  getShotGunBulletSpeed() * std::sin(m_angle) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle+0.2f) ,  getShotGunBulletSpeed() * std::sin(m_angle+ 0.2f) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle- 0.2f) ,  getShotGunBulletSpeed() * std::sin(m_angle- 0.2f) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle+ 0.5f) ,  getShotGunBulletSpeed() * std::sin(m_angle + 0.5f) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle - 0.5f) ,  getShotGunBulletSpeed() * std::sin(m_angle- 0.5f) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle + 0.7f) ,  getShotGunBulletSpeed() * std::sin(m_angle + 0.7f) }, ENEMYprojectile_TYPE);
    new Fireball(m_owner, m_position, Vec2{ getShotGunBulletSpeed() * std::cos(m_angle - 0.7f) ,  getShotGunBulletSpeed() * std::sin(m_angle - 0.7f) }, ENEMYprojectile_TYPE);
}
void Boss::Laser()
{

    new OrbitalProjectile(m_owner, this, 270.f, m_owner.getGame().getWindowSize().y/2.f,3.f,359.9f,m_owner.getGame().getWindowSize().y,70.f, ENEMYmelee_TYPE);

}
void Boss::RightMelee()
{

    new OrbitalProjectile(m_owner, this, (m_angle / 3.14159265f * 180.f)+90-30, 40, -6.f, 120 , 80.f, 20.f, ENEMYmelee_TYPE);
    
}
void Boss::LeftMelee()
{

    new OrbitalProjectile(m_owner, this, (m_angle / 3.14159265f * 180.f) - 90 + 30, 40.f, 6.f, 120, 80.f, 20.f, ENEMYmelee_TYPE);
    
}
void Boss::Kick()
{
    new OrbitalProjectile(m_owner, this, (m_angle / 3.14159265f * 180.f), 34.f, 0.03f, 0.5f, 68.f, 40.f, ENEMYKick_TYPE);
}

Vec2 Boss::getPosition() const
{
    return m_position;
}

void Boss::Dash(const float& angle)
{
    m_dashing = true;
    m_velocity += 700 * Vec2{ std::cos(m_angle+ angle), std::sin(m_angle+angle) };
}


void Boss::handleInputs(const sf::Event& event)
{

}

void Boss::update(float deltaTime)
{
    m_allGameObjects = getOwner().getAllGameOjects();
    findValidTarget();
    m_rootNode.tick();
    if (!m_dashing)
		m_angle = calculateAngleToTarget();

    Vec2 acceleration{ 0.f, 0.f };

    if (m_speed==0)
        acceleration = -getBossFluidFrictionCoef() * m_velocity;

    if (m_speed>0)
		acceleration += m_speed * Vec2 { std::cos(m_angle), std::sin(m_angle) };


    Vec2 PreviousPos = m_position;
    if (m_position.x > m_owner.getGame().getWindowSize().x - 200.f)
        m_position = { PreviousPos.x - 0.5f,PreviousPos.y };
    else if (m_position.y > m_owner.getGame().getWindowSize().y - 200.f)
        m_position = { PreviousPos.x ,PreviousPos.y - 0.5f };
    else if (m_position.x < 200)
        m_position = { PreviousPos.x + 0.5f ,PreviousPos.y };
    else if (m_position.y < 200)
        m_position = { PreviousPos.x ,PreviousPos.y + 0.5f };
    else
        m_position += m_velocity * deltaTime;
    m_velocity += acceleration * deltaTime;

    if (m_velocity.getLength() > SpeedLimit&&!m_dashing)
        m_velocity = m_velocity * (SpeedLimit / m_velocity.getLength());
}

void Boss::render(sf::RenderWindow& window)
{
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
    if (m_isInvincible)
    {
	    m_sprite.setColor(sf::Color(255, 50, 50, 128));
    	m_isInvincible = false;
    }
    m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setOrigin(getBossSize().x / 2.f, getBossSize().y / 2.f);
    m_sprite.setPosition(m_position.x, m_position.y);
    sf::Text HP("Boss : " + std::to_string(m_HP) + " / " + std::to_string(m_MaxHP), m_owner.getGame().font,45);
    HP.setOrigin(HP.getLocalBounds().width /2.f, HP.getLocalBounds().height / 2.f);
    HP.setPosition(m_owner.getGame().getWindowSize().x / 2.f, m_owner.getGame().getWindowSize().y - 100);
    HP.setStyle(sf::Text::Bold);
    window.draw(m_sprite);
    window.draw(HP);
}

OBB Boss::getBoundingBox() const
{
    Vec2 size = getBossSize();
    return {
        m_position,
        size / 2.0f,
        m_angle
    };
}

GameObjectType Boss::gameObjectType()
{
    return ENEMY_TYPE;
}


void Boss::takeDamage(int dmg)
{
    m_isInvincible = true;
    m_HP -= dmg;
    if (m_HP <= 0)
        die();
}


void Boss::die()
{
    if (m_isDead)
        return;

    m_isDead = true;
    const int nbFireball = 16;
    const float speed = 36.f;

    float dAngle = 2.0f * 3.1415926535f / static_cast<float>(nbFireball);

    for (int i = 0; i < nbFireball; ++i)
    {
        float cAngle = dAngle * static_cast<float>(i);
        new Fireball(m_owner, m_position, Vec2{ speed * std::cos(cAngle) , speed * std::sin(cAngle) }, ENEMYprojectile_TYPE);
    }

    destroy();
}

int Boss::getHP() const
{
    return m_HP;
}
int Boss::getMaxHP()const
{
    return m_MaxHP;
}


bool Boss::IsKickedPlayer()const
{
    return m_currentTarget->isKick;
}