#include "Game.h"

#include "IGameObject.h"

#include "Barrier.h"
#include "Boss.h"
#include "Fireball.h"
#include "OrbitalProjectile.h"
#include "PlayerShip.h"

#define HANDLE_COLLIDE(Type1, Type2, EnumType1, EnumType2, fn) \
if (go1->gameObjectType() == EnumType1 && go2->gameObjectType() == EnumType2)\
{\
    fn(static_cast<Type1*>(go1), static_cast<Type2*>(go2));\
}\
if (go1->gameObjectType() == EnumType2 && go2->gameObjectType() == EnumType1)\
{\
    fn(static_cast<Type1*>(go2), static_cast<Type2*>(go1));\
}


void collision_Barrier_Fireball(Barrier* go1, Fireball* go2)
{
    go2->destroy();
}

void collision_Barrier_Boss(Barrier* go1, Boss* go2)
{
    go2->destroy();
}
void collision_Barrier_PlayerShip(Barrier* go1, PlayerShip* go2)
{
    go2->destroy();
}
void collision_Ship_EnemyFireball(PlayerShip* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_EnemyMelee(PlayerShip* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(1);
}
void collision_Boss_PlayerProjectile(Boss* go1, Fireball* go2)
{
    go1->takeDamage(1);
    go2->destroy();
}
void collision_Ship_Boss(PlayerShip* go1, Boss* go2)
{
    go1->takeDamage(1);
}
void collision_Ship_Kick(PlayerShip* go1, OrbitalProjectile* go2)
{
    go1->takeDamage(1);
    if (!go1->isKick)
		go1->isKick = true;
}

void Game::onCollision(IGameObject* go1, IGameObject* go2)
{

    HANDLE_COLLIDE(Barrier, Fireball, BARRIER_TYPE, ENEMYprojectile_TYPE, collision_Barrier_Fireball)
	HANDLE_COLLIDE(Barrier, Boss, BARRIER_TYPE, ENEMY_TYPE, collision_Barrier_Boss)
	HANDLE_COLLIDE(Barrier, Fireball, BARRIER_TYPE, PLAYERprojectile_TYPE, collision_Barrier_Fireball)
    HANDLE_COLLIDE(Barrier, PlayerShip, BARRIER_TYPE, PLAYERSHIP_TYPE, collision_Barrier_PlayerShip)
	HANDLE_COLLIDE(PlayerShip, Fireball, PLAYERSHIP_TYPE, ENEMYprojectile_TYPE, collision_Ship_EnemyFireball)
	HANDLE_COLLIDE(PlayerShip, OrbitalProjectile, PLAYERSHIP_TYPE, ENEMYmelee_TYPE, collision_Ship_EnemyMelee)
	HANDLE_COLLIDE(Boss, Fireball, ENEMY_TYPE, PLAYERprojectile_TYPE, collision_Boss_PlayerProjectile)
	HANDLE_COLLIDE(PlayerShip, Boss, PLAYERSHIP_TYPE, ENEMY_TYPE, collision_Ship_Boss)
	HANDLE_COLLIDE(PlayerShip, OrbitalProjectile, PLAYERSHIP_TYPE, ENEMYKick_TYPE, collision_Ship_Kick)
}
