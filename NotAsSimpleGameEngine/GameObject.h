#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <iostream>
#include <vector>
#include "InputManager.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

enum class GameObjectTag {
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

	GameObject(const GameObject& obj) = delete;
	GameObject& operator=(const GameObject& rhs) = delete;

protected:
	bool m_Active;
	Vector2f m_Position;
	InputManager* input;
	int m_Id;

	void addComponent(GameObjectComponent& component);
	virtual void update(float dtAsSeconds) = 0;

public:
	GameObjectTag m_Tag = GameObjectTag::Generic;

	GameObject();
	virtual ~GameObject();

	virtual void init(float x, float y);
	int getId() const;
	bool isActive() const;
	void setActive(bool isActive);
	const Vector2f& getPosition() const;
	void setPosition(const Vector2f& position);
	void process(float dtAsSeconds);
};

#endif
