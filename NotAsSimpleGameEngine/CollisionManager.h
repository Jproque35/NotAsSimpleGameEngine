#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Collider;
class CollisionManagerEntry;
class CollisionListEntry;

class CollisionManager {
private:
	static CollisionManager* instance;
	unordered_map<Collider*, CollisionManagerEntry*> m_Entries;
	list<CollisionListEntry*> m_XList;
	list<CollisionListEntry*> m_YList;

	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager& rhs) = delete;


	void updateSingleCollider(Collider& collider);

public:
	static CollisionManager* getInstance();
	static void resetInstance();
	int add(Collider& col);
	void erase(int id);
	vector<Collider*> getCollisionList(const Collider& col);
	void update(float dtAsSeconds);
	void cleanUp();
	void print();
	bool compare_values(CollisionListEntry* lhs, CollisionListEntry* rhs);
};

#endif

