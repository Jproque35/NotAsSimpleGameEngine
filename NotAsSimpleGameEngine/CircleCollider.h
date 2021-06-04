#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H
#pragma once
#include "Collider.h"

class RectangleCollider;

class CircleCollider final :
    public Collider {
private:
    CircleCollider();
    CircleCollider(const CircleCollider& other) = delete;
    CircleCollider& operator=(const CircleCollider& rhs) = delete;

protected:
    float m_Radius;

    bool intersectsRectangle(const RectangleCollider& col) const;
    bool intersectsCircle(const CircleCollider& col) const;
    CollisionDirection getCollisionDirection(const Collider& col, const Vector2f& diff) const;
    void repositionAfterRectangleCollision(const RectangleCollider& col) const;
    void repositionAfterCircleCollision(const CircleCollider& col) const;

public:
    CircleCollider(GameObject& owner, float radius, bool solid, bool stationary);
    ~CircleCollider();

    inline float getRadius() const {
        return this->m_Radius;
    }

    float getMinX() const;
    float getMinY() const;
    float getMaxX() const;
    float getMaxY() const;
    void update(float dtAsSeconds);
};
#endif

