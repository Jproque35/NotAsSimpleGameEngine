#ifndef COLLIDER_H
#define COLLIDER_H
#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjectComponent.h"

using namespace sf;
using namespace std;

enum class ColliderType {
	CIRCLE,
	RECTANGLE
};

enum class CollisionDirection {
Up,
Right,
Down,
Left
};

typedef std::tuple<bool, CollisionDirection, Vector2f> Collision;

class CircleCollider;
class RectangleCollider;
class GameObject;

class Collider
	: public GameObjectComponent {
private:
	static int currFreeId;

	Collider();
	Collider(const Collider& other) = delete;
	Collider& operator=(const Collider& rhs) = delete;

protected:
	ColliderType m_Type;
	bool m_Solid;
	bool m_Stationary;

	virtual bool intersectsRectangle(const RectangleCollider& col) const = 0;
	virtual bool intersectsCircle(const CircleCollider& col) const = 0;
	virtual void repositionAfterRectangleCollision(const RectangleCollider& col) const = 0;
	virtual void repositionAfterCircleCollision(const CircleCollider& col) const = 0;
	virtual CollisionDirection getCollisionDirection(const Collider& col, const Vector2f& diff) const = 0;

public:
	Collider(GameObject& owner, ColliderType type, bool solid, bool stationary);
	virtual ~Collider();

	inline ColliderType getType() const {
		return this->m_Type;
	}

	inline bool isSolid() const {
		return this->m_Solid;
	}

	inline bool isStationary() const {
		return this->m_Stationary;
	}

	Collision getCollisionData(const Collider& col) const;
	vector<CollisionDirection> getBoundaryCollisionData() const;
	void repositionAfterObjectCollision(const Collider& col);
	void repositionAfterBoundaryCollision();
	virtual float getMinX() const = 0;
	virtual float getMinY() const = 0;
	virtual float getMaxX() const = 0;
	virtual float getMaxY() const = 0;
	bool intersects(const Collider& col) const;
	vector<Collider*> getCollisionList() const;
	virtual void update(float dtAsSeconds) = 0;
	void destroy() const;
};

#endif

