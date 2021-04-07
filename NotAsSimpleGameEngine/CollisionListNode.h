#pragma once
#include <stdlib.h>
#include <iostream>

using namespace std;

class Collider;

enum CollisionListNodeType {
	Start,
	End
};

class CollisionListNode {
private:
	Collider* m_Owner;
	float m_Value;
	CollisionListNodeType m_Type;
	CollisionListNode* m_Next;
	CollisionListNode* m_Prev;

	CollisionListNode() = delete;
	CollisionListNode(const CollisionListNode& other) = delete;
	CollisionListNode& operator=(const CollisionListNode& rhs) = delete;

public:
	CollisionListNode(Collider& owner, CollisionListNodeType type);
	~CollisionListNode();

	Collider& getOwner();
	CollisionListNodeType getType() const;
	void setValue(float value);
	float getValue() const;
	void setNext(CollisionListNode* next);
	CollisionListNode* getNext();
	void setPrev(CollisionListNode* prev);
	CollisionListNode* getPrev();
};

