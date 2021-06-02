#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H
#pragma once
#include <iostream>

using namespace std;

class GameObject;

class GameObjectComponent {

private:
	GameObjectComponent() = delete;
	GameObjectComponent(const GameObjectComponent& obj) = delete;
	GameObjectComponent& operator=(const GameObjectComponent& rhs) = delete;

protected:
	GameObject *const m_Owner;
	int m_Id;

public:
	GameObjectComponent(GameObject& obj);
	virtual ~GameObjectComponent();

	inline int getId() const {
		return this->m_Id;
	}

	inline GameObject& getOwner() const {
		return *this->m_Owner;
	}

	float getX() const;
	float getY() const;
	virtual void update(float dtAsSeconds) = 0;
	virtual void destroy() const = 0;
};
#endif

