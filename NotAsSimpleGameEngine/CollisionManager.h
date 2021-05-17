#ifndef SSCOLLISIONMANAGER_H
#define SSCOLLISIONMANAGER_H
#pragma once
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class RectangleColliderOld;

enum class CollisionEntryType {
	Start,
	End
};

struct CollisionEntry {
	RectangleColliderOld* owner = NULL;
	float value = 0.0f;
	CollisionEntryType type = CollisionEntryType::Start;

	bool operator<(const CollisionEntry& rhs) {
		return this->value < rhs.value;
	}
};


class SSCollisionManager final {
private:
	static SSCollisionManager* instance;
	unordered_map<int, RectangleColliderOld*> m_Colliders;
	unordered_map<int, vector<RectangleColliderOld*>> m_CollisionLists;
	vector<CollisionEntry> m_XList;
	vector<CollisionEntry> m_YList;
	float currTime;

	SSCollisionManager();
	~SSCollisionManager();
	SSCollisionManager(const SSCollisionManager& other) = delete;
	SSCollisionManager& operator=(const SSCollisionManager& rhs) = delete;


	void addXEntries(RectangleColliderOld& col);
	void addYEntries(RectangleColliderOld& col);
	void updateSingleCollider(RectangleColliderOld& collider);
	void updateXList();
	void updateYList();
	void processCollisionEntry(CollisionEntry entry, unordered_map<int, vector<RectangleColliderOld*>>& intersectionLists, list<int>& activeColliderIds);
	unordered_map<int, vector<RectangleColliderOld*>> buildSingleAxisList( vector<CollisionEntry>& axiList );
	void buildSingleCollisionList(int id, vector<RectangleColliderOld*>& colList, vector<RectangleColliderOld*>& checkList);
	void buildCollisionLists();

public:
	static SSCollisionManager* getInstance();
	static void resetInstance();
	void add(RectangleColliderOld& col);
	RectangleColliderOld& get(int id);
	vector<RectangleColliderOld*> getCollisionList(const RectangleColliderOld& col);
	void update(float dtAsSeconds);
	void cleanUp();
	void print();
};

#endif

