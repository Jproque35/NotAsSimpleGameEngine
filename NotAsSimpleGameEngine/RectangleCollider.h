#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H
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

class RectangleCollider final
	: public GameObjectComponent {
private:
	static int m_CurrFreeId;
	bool m_Stationary;
	bool m_Solid;
	float m_Height;
	float m_Width;

	RectangleCollider() = delete;
	RectangleCollider(const RectangleCollider& other) = delete;
	RectangleCollider& operator=(const RectangleCollider& rhs) = delete;

	bool horizontalCollision(const RectangleCollider& other) const;
	bool verticalCollision(const RectangleCollider& other) const;
	CollisionDirection getRelativeDirection(const RectangleCollider& other, Vector2f diff) const;

public:
	RectangleCollider(GameObject& owner, const Vector2f& dimensions, bool solid, bool stationary);
	~RectangleCollider();

	bool isStationary() const;
	bool isSolid() const;
	float getTop() const;
	float getLeft() const;
	float getWidth() const;
	float getHeight() const;
	bool intersects(const RectangleCollider& other) const ;
	vector<RectangleCollider*> getCollisionList() const;
	Collision getObjectCollisionData(const RectangleCollider& other) const ;
	vector<CollisionDirection> getBoundaryCollisionData() const;
	void repositionAfterObjectCollision(const RectangleCollider& other);
	void update(float dtAsSeconds);
	void destroy() const;
};
#endif;
