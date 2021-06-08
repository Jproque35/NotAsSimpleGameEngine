#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H
#pragma once
#include <iostream>

using namespace std;

class GameObject;

class GameObjectComponent {

private:
	GameObject* const m_Owner;
	int m_Id;

	GameObjectComponent() = delete;
	GameObjectComponent(const GameObjectComponent& obj) = delete;
	GameObjectComponent& operator=(const GameObjectComponent& rhs) = delete;

protected:

public:
	GameObjectComponent(GameObject& obj, int id);
	virtual ~GameObjectComponent();

	inline const int getId() const {
		return this->m_Id;
	}

	inline GameObject& getOwner() const {
		return *this->m_Owner;
	}

	const float getX() const;
	const float getY() const;
	virtual void update(float dtAsSeconds) = 0;
	virtual void destroy() const = 0;
};
#endif

