#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#pragma once
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class RectangleCollider;

enum class CollisionEntryType {
	Start,
	End
};

struct CollisionEntry {
	RectangleCollider* owner = NULL;
	float value = 0.0f;
	CollisionEntryType type = CollisionEntryType::Start;

	bool operator<(const CollisionEntry& rhs) {
		return this->value < rhs.value;
	}
};


class CollisionManager final {
private:
	static CollisionManager* instance;
	unordered_map<int, RectangleCollider*> m_Colliders;
	unordered_map<int, vector<RectangleCollider*>> m_CollisionLists;
	vector<CollisionEntry> m_XList;
	vector<CollisionEntry> m_YList;
	float currTime;

	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager& rhs) = delete;


	void addXEntries(RectangleCollider& col);
	void addYEntries(RectangleCollider& col);
	void updateSingleCollider(RectangleCollider& collider);
	void updateXList();
	void updateYList();
	void processCollisionEntry(CollisionEntry entry, unordered_map<int, vector<RectangleCollider*>>& intersectionLists, list<int>& activeColliderIds);
	unordered_map<int, vector<RectangleCollider*>> buildSingleAxisList( vector<CollisionEntry>& axiList );
	void buildSingleCollisionList(int id, vector<RectangleCollider*>& colList, vector<RectangleCollider*>& checkList);
	void buildCollisionLists();

public:
	static CollisionManager* getInstance();
	static void resetInstance();
	void add(RectangleCollider& col);
	RectangleCollider& get(int id);
	vector<RectangleCollider*> getCollisionList(const RectangleCollider& col);
	void update(float dtAsSeconds);
	void cleanUp();
	void print();
};

#endif

