#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Collider;

enum CollisionManagerEntryType {
	Start,
	End
};

struct CollisionManagerEntry {
public:
	const Collider* owner;
	float value;
	CollisionManagerEntryType type;

	bool operator<(const CollisionManagerEntry& rhs) {
		return this->value < rhs.value;
	}

	void print() {
		cout << "CollisionManagerEntry: {Owner: " << owner << ", Value: " << value << endl;
	}
};

class CollisionManager {
private:
	static CollisionManager* instance;
	list<CollisionManagerEntry> m_XList;
	list<CollisionManagerEntry> m_YList;
	unordered_map<Collider*, vector<Collider*>> m_CollisionLists;

	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager& rhs) = delete;

	void updateSingleCollider(Collider& collider);
	void updateAxes();

public:
	static CollisionManager* getInstance();
	static void resetInstance();
	int add(const Collider& col);
	void erase(int id);
	vector<Collider*> getCollisionList(const Collider& col);
	void update(float dtAsSeconds);
	void cleanUp();
	void print();

};

#endif

