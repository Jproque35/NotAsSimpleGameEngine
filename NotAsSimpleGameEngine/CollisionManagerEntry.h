#ifndef COLLISIONMANAGERENTRY_H
#define COLLISIONMANAGERENTRY_H
#pragma once
#include <stdlib.h>

class Collider;
class CollisionListEntry;

class CollisionManagerEntry {
private:
	Collider* m_Owner;
	CollisionListEntry* m_XStart;
	CollisionListEntry* m_XEnd;
	CollisionListEntry* m_YStart;
	CollisionListEntry* m_YEnd;

	CollisionManagerEntry() = delete;
	CollisionManagerEntry(const CollisionManagerEntry& obj) = delete;
	CollisionManagerEntry& operator=(const CollisionManagerEntry& rhs) = delete;

public:
	CollisionManagerEntry(const Collider& owner);
	~CollisionManagerEntry();

	Collider& getOwner() const;
	CollisionListEntry& getXStart() inline const;
	CollisionListEntry& getXEnd() inline const;
	CollisionListEntry& getYStart() inline const;
	CollisionListEntry& getYEnd() inline const;
};

#endif
