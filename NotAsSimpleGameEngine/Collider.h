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
	//FloatRect m_RectCol;
	bool m_Stationary;
	float m_Height;
	float m_Width;

	Collider() = delete;
	Collider(const Collider& other) = delete;
	Collider& operator=(const Collider& rhs) = delete;

	bool horizontalCollision(const Collider& other) inline const;
	bool verticalCollision(const Collider& other) inline const;
	CollisionDirection getRelativeDirection(const Collider& other, Vector2f diff) const;

public:
	Collider(GameObject& owner, const Vector2f& size, bool stationary);
	~Collider();

	bool isStationary() inline const;
	float getWidth() inline const;
	float getHeight() inline const;
	bool intersects(const Collider& other) inline const ;
	Collision getCollisionData(const Collider& other) inline const ;
	vector<Collider*> getCollisionList() const;
	void repositionAfterCollision(const Collider& other);
	void update(float dtAsSeconds);
	void destroy() const;
};
#endif;
