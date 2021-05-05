#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#pragma once
#include"GameObject.h"
#include "Container.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObjectManager final {

private:
	static GameObjectManager* instance;
	static const int maxSize = 128;
	int m_CurrFreeSlot;
	GameObject* m_Objs[maxSize];
	Container<GameObject>* m_Storage;

	GameObjectManager();
	~GameObjectManager();

public:
	static GameObjectManager* getInstance();
	static void resetInstance();
	void add(GameObject& obj);
	GameObject& get(int i) const;
	int size() const;
	void cleanUp();

};

#endif