#pragma once

#include "MyMath.h"

#include <vector>

namespace sf { class RenderWindow; }
namespace sf { class Event; }

class Game;

enum GameObjectType
{

	  ENEMY_TYPE = 0
	, PLAYERprojectile_TYPE = 1
	, ENEMYprojectile_TYPE = 2
    , PLAYERmelee_TYPE = 3
    , ENEMYmelee_TYPE = 4
	, BARRIER_TYPE = 5
	, PLAYERSHIP_TYPE = 6
	, INVICIBLE_TYPE = 7
    , ENEMYKick_TYPE=8

};

class IGameObject;

class IGameObjectContainer
{
public:
    void _addObject(IGameObject*);
    void _removeObject(IGameObject*);
    void _toBeRemoveObject(IGameObject*);
    void _deferedAddObject(IGameObject*);
    void _deferedAddObjects();
    void _cleanObject();
    std::vector<IGameObject*> getAllGameOjects() const;
    ~IGameObjectContainer();

    virtual Game& getGame() = 0;

protected:
    std::vector<IGameObject*> m_allGameObjects;
    std::vector<IGameObject*> m_toBeRemovedGameObjects;
    std::vector<IGameObject*> m_toBeAddedGameObjects;
};

class IGameObject
{
public:
    IGameObject(IGameObjectContainer& owner);
    virtual ~IGameObject();

    virtual void handleInputs(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual OBB getBoundingBox() const = 0;
    
    virtual GameObjectType gameObjectType() = 0;
    void destroy();
    IGameObjectContainer& getOwner() { return m_owner; }
    const IGameObjectContainer& getOwner() const { return m_owner; }

protected:
    IGameObjectContainer& m_owner;
};

class IGameObjectCompound : public IGameObject, public IGameObjectContainer
{
public:
    IGameObjectCompound(IGameObjectContainer& owner);

    void handleInputs(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
