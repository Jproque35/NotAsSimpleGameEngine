#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT
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
	GameObject* m_Owner;
	int m_Id;

public:
	GameObjectComponent(GameObject& obj);
	virtual ~GameObjectComponent();

	int getId() const;
	GameObject& getOwner() const;
	virtual void update(float dtAsSeconds) = 0;
	virtual void destroy() const = 0;
};
#endif

