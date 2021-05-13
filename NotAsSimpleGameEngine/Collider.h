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

class GameObject;

class Collider
	: public GameObjectComponent {
private:
	Collider(const Collider& other) = delete;
	Collider& operator=(const Collider& rhs) = delete;

protected:
	ColliderType m_Type;
	bool m_Solid;
	bool m_Stationary;

	virtual bool intersectsRectangle() const = 0;
	virtual bool intersectsCircle() const = 0;

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

	virtual float getMinX() const = 0;
	virtual float getMinY() const = 0;
	virtual float getMaxX() const = 0;
	virtual float getMaxY() const = 0;
	bool intersects(const Collider& col) const;
	vector<Collider*> getCollisionList() const;
	virtual void update(float dtAsSeconds) = 0;
};

#endif

