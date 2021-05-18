#ifndef ENTITY_H
#define ENTITY_H
#pragma once
#include "GameObject.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include <math.h>

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
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& rhs) = delete;

protected:
    Direction m_CurrDir;
    EntityType m_Type;
    RectangleCollider* m_Collider;

    virtual void update(float dtAsSeconds) = 0;

public:
    Entity();
    virtual ~Entity();

    void Move(const Vector2f& direction);
};

#endif

