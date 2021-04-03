#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#pragma once
#include"GameObject.h"
#include "CompactVector.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObjectManager {

private:
	static GameObjectManager* instance;
	CompactVector<GameObject>* m_Storage;

	GameObjectManager();
	~GameObjectManager();

public:
	static GameObjectManager* getInstance();
	static void resetInstance();
	int add(GameObject& obj);
	GameObject& get(int i) inline const;
	void erase(int i);
	int size() inline const;
	void cleanUp();

};

#endif