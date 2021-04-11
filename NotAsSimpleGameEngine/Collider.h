#ifndef COLLIDER_H
#define COLLIDER_H
#pragma once
#include "GameObjectComponent.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class CollisionDirection {
	Down,
	Right,
	Up,
	Left
};

typedef std::tuple<bool, CollisionDirection, Vector2f> Collision;

class GameObject;

class Collider 
	: public GameObjectComponent {
private:
	static int m_CurrFreeId;
	bool m_Stationary;
	bool m_Solid;
	float m_Height;
	float m_Width;

	Collider() = delete;
	Collider(const Collider& other) = delete;
	Collider& operator=(const Collider& rhs) = delete;

	bool horizontalCollision(const Collider& other) const;
	bool verticalCollision(const Collider& other) const;
	CollisionDirection getRelativeDirection(const Collider& other, Vector2f diff) const;

public:
	Collider(GameObject& owner, const Vector2f& dimensions, bool solid, bool stationary);
	~Collider();

	bool isStationary() const;
	bool isSolid() const;
	float getTop() const;
	float getLeft() const;
	float getWidth() const;
	float getHeight() const;
	bool intersects(const Collider& other) const ;
	vector<Collider*> getCollisionList() const;
	Collision getObjectCollisionData(const Collider& other) const ;
	vector<CollisionDirection> getBoundaryCollisionData() const;
	void repositionAfterObjectCollision(const Collider& other);
	void update(float dtAsSeconds);
	void destroy() const;
};
#endif;
