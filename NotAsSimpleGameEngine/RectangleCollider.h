#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H
#pragma once
#include "Collider.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject;

class RectangleCollider final
	: public Collider {
private:
	static int m_CurrFreeId;
	float m_Width;
	float m_Height;

	RectangleCollider() = delete;
	RectangleCollider(const RectangleCollider& other) = delete;
	RectangleCollider& operator=(const RectangleCollider& rhs) = delete;

	CollisionDirection getRectangleCollisionDirection(
		CollisionDirection& desire, 
		const RectangleCollider& col, 
		const Vector2f& diff) const;

	void repositionAfterRectangleCollision(const RectangleCollider& col) const;
	void repositionAfterCircleCollision(const CircleCollider& col) const;

protected:
	bool intersectsCircle(const CircleCollider& col) const;
	bool intersectsRectangle(const RectangleCollider& col) const;
	CollisionDirection getCollisionDirection(const Collider& col, const Vector2f& diff) const;

public:
	RectangleCollider(GameObject& owner, const Vector2f& dimensions, bool solid, bool stationary);
	~RectangleCollider();

	inline float getWidth() const {
		return this->m_Width;
	}

	inline float getHeight() const {
		return this->m_Height;
	}

	float getMinX() const;
	float getMinY() const;
	float getMaxX() const;
	float getMaxY() const;
	void update(float dtAsSeconds);
};
#endif;
