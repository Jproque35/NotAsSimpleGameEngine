#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H
#pragma once
#include "Collider.h"
class CircleCollider final :
    public Collider {
private:
    CircleCollider();
    CircleCollider(const CircleCollider& other) = delete;
    CircleCollider& operator=(const CircleCollider& rhs) = delete;

protected:
    float m_Radius;

    bool intersectsRectangle() const;
    bool intersectsCircle(const CircleCollider& col) const;

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

