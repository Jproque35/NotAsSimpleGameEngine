#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <iostream>
#include <vector>
#include "InputManager.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class Tag {
	Generic,
	Player,
	Enemy,
	Obstacle
};

class GameObjectComponent;

class GameObject {
private:
	vector<GameObjectComponent*> m_Components;
	static int m_CurrId;

	GameObject() = delete;
	GameObject(const GameObject& obj) = delete;
	GameObject& operator=(const GameObject& rhs) = delete;

protected:
	bool m_Active;
	Vector2f m_Position;
	InputManager* input;
	int m_Id;

	void addComponent(GameObjectComponent& component);

public:
	GameObject(float x, float y);
	virtual ~GameObject();

	int getId() const;
	bool isActive() const;
	void setActive(bool isActive);
	const Vector2f& getPosition() const;
	void setPosition(float x, float y);
	virtual void update(float dtAsSeconds) = 0;
	void process(float dtAsSeconds);
};

#endif
