#pragma once
#include <unordered_map>

using namespace std;
class CollisionListNode;
class Collider;

typedef tuple<CollisionListNode*, CollisionListNode*> CollisionListEntry;
class CollisionList
{
private:
	unordered_map<Collider*, CollisionListEntry> m_Colliders;
	CollisionListNode* m_Head;
	CollisionListNode* m_Tail;
	int m_Size;

	void push_front(CollisionListNode& node);
	void push_back(CollisionListNode& node);

public:
	CollisionList();
	~CollisionList();

	int size() const;
	void add(Collider& collider);
	void sort();
};

