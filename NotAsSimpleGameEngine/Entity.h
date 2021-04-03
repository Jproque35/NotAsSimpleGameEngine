#ifndef ENTITY_H
#define ENTITY_H
#pragma once
#include "GameObject.h"
#include "Collider.h"

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

enum class EntityType {
    Generic,
    Player,
    Enemy,
    World
};

class Entity :
    public GameObject {
private:
    Entity() = delete;
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& rhs) = delete;

protected:
    Direction m_CurrDir;
    EntityType m_Type;
    Collider* m_Collider;

    virtual void update(float dtAsSeconds) = 0;

public:
    Entity(float x, float y);
    virtual ~Entity();

    void Move(float x, float y);
    Collider& getCollider();
};

#endif

