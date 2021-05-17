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

class RectangleColliderOld final
	: public GameObjectComponent {
private:
	static int m_CurrFreeId;
	bool m_Stationary;
	bool m_Solid;
	float m_Height;
	float m_Width;

	RectangleColliderOld() = delete;
	RectangleColliderOld(const RectangleColliderOld& other) = delete;
	RectangleColliderOld& operator=(const RectangleColliderOld& rhs) = delete;

	bool horizontalCollision(const RectangleColliderOld& other) const;
	bool verticalCollision(const RectangleColliderOld& other) const;
	CollisionDirection getRelativeDirection(const RectangleColliderOld& other, Vector2f diff) const;

public:
	RectangleColliderOld(GameObject& owner, const Vector2f& dimensions, bool solid, bool stationary);
	~RectangleColliderOld();

	bool isStationary() const;
	bool isSolid() const;
	float getTop() const;
	float getLeft() const;
	float getWidth() const;
	float getHeight() const;
	bool intersects(const RectangleColliderOld& other) const ;
	vector<RectangleColliderOld*> getCollisionList() const;
	Collision getObjectCollisionData(const RectangleColliderOld& other) const ;
	vector<CollisionDirection> getBoundaryCollisionData() const;
	void repositionAfterObjectCollision(const RectangleColliderOld& other);
	void update(float dtAsSeconds);
	void destroy() const;
};
#endif;
