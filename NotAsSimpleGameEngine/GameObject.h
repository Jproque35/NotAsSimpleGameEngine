#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
#include <iostream>
#include <vector>
#include "InputManager.h"
#include "RectangleCollider.h"
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
	Vector2f m_UpAxis;
	Vector2f m_RightAxis;
	InputManager* input;
	int m_Id;

	void addComponent(GameObjectComponent& component);
	virtual void update(float dtAsSeconds) = 0;

public:
	GameObjectTag m_Tag = GameObjectTag::Generic;

	GameObject();
	virtual ~GameObject();

	virtual void init(float x, float y);

	inline int getId() const {
		return this->m_Id;
	}

	inline bool isActive() const {
		return this->m_Active;
	}

	inline void setActive(bool isActive) {
		this->m_Active = isActive;
	}

	inline const Vector2f& getPosition()  const {
		return this->m_Position;
	}

	inline void setPosition(const Vector2f& position) {
		this->m_Position = position;
	}

	const Vector2f& getVerticalAxis() const;
	const Vector2f& getHorizontalAxis() const;
	void process(float dtAsSeconds);
};

#endif
