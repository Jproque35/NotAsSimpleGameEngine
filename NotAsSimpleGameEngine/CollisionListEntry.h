#ifndef COLLISIONLISTENTRY_H
#define COLLISIONLISTENTRY_H
#pragma once
#include <stdlib.h>

class Collider;

class CollisionListEntry {
private:
	Collider* m_Owner;
	float m_Value;
	CollisionListEntry* m_Next;

	CollisionListEntry() = delete;
	CollisionListEntry(const CollisionListEntry& obj) = delete;
	CollisionListEntry& operator=(const CollisionListEntry& rhs) = delete;

public:
	CollisionListEntry(const Collider& collider);
	~CollisionListEntry();

	Collider& getOwner() const;
	void setValue(float value);
	float getValue() inline const;
	void setNext(const CollisionListEntry& entry);
	CollisionListEntry& getNext() const;
};

#endif
