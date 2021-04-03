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
	Collider() = delete;
	Collider(const Collider& other) = delete;
	Collider& operator=(const Collider& rhs) = delete;

	FloatRect m_RectCol;
	CollisionDirection getCollisionDirection(const FloatRect& other) const;

public:
	Collider(GameObject& owner, const Vector2f& pos, const Vector2f& size);
	~Collider();

	float getX() const;
	float getY() const;
	void setWidth(float width);
	float getWidth() const;
	void setHeight(float height);
	float getHeight() const;
	void setPosition(float x, float y);
	bool intersects(const Collider& other) const;
	void printCollider() const;
	Collision getCollisionData(const Collider& other) const;
	vector<Collider*> getCollisionList() const;
	void update(float dtAsSeconds);
	void destroy() const;
};
#endif;
