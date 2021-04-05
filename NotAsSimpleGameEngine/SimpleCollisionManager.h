#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <iostream>

using namespace sf;
using namespace std;

class Collider;

class SimpleCollisionManager
{

private:
	static SimpleCollisionManager* instance;
	queue<int> m_FreeIds;
	vector<Collider*> m_Colliders;
	queue<Collider*> m_DeletionQueue;
	int m_Size;

	SimpleCollisionManager();
	SimpleCollisionManager(const SimpleCollisionManager& obj) = delete;
	SimpleCollisionManager& operator=(const SimpleCollisionManager& rhs) = delete;
	~SimpleCollisionManager();

	void updateSingleCollider(Collider& collider);

public:
	static SimpleCollisionManager* getInstance();
	static void resetInstance();
	int add(Collider& col);
	void erase(int id);
	vector<Collider*> getCollisionList(int id);
	void update(float dtAsSeconds);
	void cleanUp();


};

#endif

