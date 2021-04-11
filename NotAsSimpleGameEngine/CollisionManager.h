#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Collider;

enum CollisionEntryType {
	Start,
	End
};

struct CollisionEntry {
	Collider* owner = NULL;
	float value = 0.0f;
	CollisionEntryType type = CollisionEntryType::Start;

	bool operator<(const CollisionEntry& rhs) {
		return this->value < rhs.value;
	}
};


class CollisionManager {
private:
	static CollisionManager* instance;
	unordered_map<int, Collider*> m_Colliders;
	unordered_map<int, vector<Collider*>> m_CollisionLists;
	vector<CollisionEntry> m_XList;
	vector<CollisionEntry> m_YList;
	float currTime;

	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager& rhs) = delete;


	void addXEntries(Collider& col);
	void addYEntries(Collider& col);
	void updateSingleCollider(Collider& collider);
	void updateXList();
	void updateYList();
	void processCollisionEntry(CollisionEntry entry, unordered_map<int, vector<Collider*>>& intersectionLists, list<int>& activeColliderIds);
	unordered_map<int, vector<Collider*>> buildSingleAxisList( vector<CollisionEntry>& axiList );
	void buildSingleCollisionList(int id, vector<Collider*>& colList, vector<Collider*>& checkList);
	void buildCollisionLists();

public:
	static CollisionManager* getInstance();
	static void resetInstance();
	void add(Collider& col);
	Collider& get(int id);
	vector<Collider*> getCollisionList(const Collider& col);
	void update(float dtAsSeconds);
	void cleanUp();
	void print();
};

#endif

