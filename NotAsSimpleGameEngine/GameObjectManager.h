#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#pragma once
#include"GameObject.h"
#include "Container.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObjectManager {

private:
	static GameObjectManager* instance;
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