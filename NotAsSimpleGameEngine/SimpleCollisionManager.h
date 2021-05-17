#ifndef SIMPLECOLLISIONMANAGER_H
#define SIMPLECOLLISIONMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <iostream>

using namespace sf;
using namespace std;

class RectangleColliderOld;

class SimpleCollisionManager final
{

private:
	static SimpleCollisionManager* instance;
	queue<int> m_FreeIds;
	vector<RectangleColliderOld*> m_Colliders;
	queue<RectangleColliderOld*> m_DeletionQueue;
	int m_Size;

	SimpleCollisionManager();
	SimpleCollisionManager(const SimpleCollisionManager& obj) = delete;
	SimpleCollisionManager& operator=(const SimpleCollisionManager& rhs) = delete;
	~SimpleCollisionManager();

	void updateSingleCollider(RectangleColliderOld& collider);

public:
	static SimpleCollisionManager* getInstance();
	static void resetInstance();
	int add(RectangleColliderOld& col);
	void erase(int id);
	vector<RectangleColliderOld*> getCollisionList(int id);
	void update(float dtAsSeconds);
	void cleanUp();


};

#endif

