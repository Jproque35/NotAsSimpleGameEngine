#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"

CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager() :
	currTime(0.0f) {}

CollisionManager::~CollisionManager() {
	cout << "***CollisionManager: Destroying CollisionManager.." << endl;

	for (auto it = this->m_Colliders.begin(); it != this->m_Colliders.end(); ++it) {
		if (it->second != NULL) {
			delete(it->second);
		}
		this->m_Colliders[it->first] = NULL;
	}
}

RectangleCollider* CollisionManager::createRectangleCollider(GameObject& owner,
	const Vector2f& dimensions,
	bool solid,
	bool stationary) {
	RectangleCollider* desire = new RectangleCollider(owner, dimensions, solid, stationary);
	this->add(*desire);
	return desire;
}

CircleCollider* CollisionManager::createCircleCollider(
	GameObject& owner,
	float radius,
	bool solid,
	bool stationary) {
	CircleCollider* desire = new CircleCollider(owner, radius, solid, stationary);
	this->add(*desire);
	return desire;
}

void CollisionManager::addXEntries(Collider& col) {
	CollisionEntry xStart;
	CollisionEntry xEnd;

	xStart.owner = &col;
	xStart.value = col.getMinX();
	xStart.type = CollisionEntryType::Start;

	xEnd.owner = &col;
	xEnd.value = col.getMaxX();
	xEnd.type = CollisionEntryType::End;

	this->m_XList.push_back(xStart);
	this->m_XList.push_back(xEnd);
}

void CollisionManager::addYEntries(Collider& col) {
	CollisionEntry yStart;
	CollisionEntry yEnd;

	yStart.owner = &col;
	yStart.value = col.getMinY();
	yStart.type = CollisionEntryType::Start;

	yEnd.owner = &col;
	yEnd.value = col.getMaxY();
	yEnd.type = CollisionEntryType::End;

	this->m_YList.push_back(yStart);
	this->m_YList.push_back(yEnd);
}

void CollisionManager::add(Collider& col) {
	this->m_Colliders[col.getId()] = &col;

	this->addXEntries(col);
	this->addYEntries(col);

	cout << "CollisionManager: Added Collider with id " << col.getId() << " to CollisionManager" << endl;
}

Collider& CollisionManager::get(int id) {
	return *this->m_Colliders[id];
}

vector<Collider*> CollisionManager::getCollisionList(const Collider& col) {
	return this->m_CollisionLists[col.getId()];
}

void CollisionManager::updateXList() {
	for (register auto it = this->m_XList.begin(); it != this->m_XList.end(); ++it) {
		if (it->type == CollisionEntryType::Start) {
			it->value = it->owner->getMinX();
		}
		else {
			it->value = it->owner->getMaxX();
		}
	}

	sort(this->m_XList.begin(), this->m_XList.end());
}

void CollisionManager::updateYList() {
	for (register auto it = this->m_YList.begin(); it != this->m_YList.end(); ++it) {
		if (it->type == CollisionEntryType::Start) {
			it->value = it->owner->getMinY();
		}
		else {
			it->value = it->owner->getMaxY();
		}
	}

	sort(this->m_YList.begin(), this->m_YList.end());
}

void CollisionManager::processCollisionEntry(
	CollisionEntry entry, 
	unordered_map<int, vector<Collider*>>& intersectionLists, 
	list<int>& activeColliderIds) {
	Collider* currCollider = entry.owner;
	CollisionEntryType currType = entry.type;

	if (currType == CollisionEntryType::Start) {
		for (register auto it = activeColliderIds.begin(); it != activeColliderIds.end(); ++it) {
			intersectionLists[currCollider->getId()].push_back(this->m_Colliders[*it]);
		}

		activeColliderIds.push_back(currCollider->getId());
	}
	else {
		activeColliderIds.remove(currCollider->getId());
	}

	for (register auto it2 = activeColliderIds.begin(); it2 != activeColliderIds.end(); ++it2) {
		if (*it2 != currCollider->getId()) {
			intersectionLists[*it2].push_back(currCollider);
		}
	}
}

unordered_map<int, vector<Collider*>> CollisionManager::buildSingleAxisList(
	vector<CollisionEntry>& axisList) {
	unordered_map<int, vector<Collider*>> intersectionLists;
	list<int> activeColliderIds;

	for(register int i = 0; i < axisList.size(); ++i) {
		if (axisList[i].owner->getOwner().isActive()) {
			this->processCollisionEntry(axisList[i], intersectionLists, activeColliderIds);
		}
	}

	return intersectionLists;
}

void CollisionManager::buildSingleCollisionList(
	int id, 
	vector<Collider*>& colList, 
	vector<Collider*>& checkList) {
	for (register int i = 0; i < colList.size(); ++i) {
		for (register int j = 0; j < checkList.size(); ++j) {
			if ((colList[i] == checkList[j])
					&& this->m_Colliders[id]->intersects(*colList[i]) ) {
				this->m_CollisionLists[id].push_back(colList[i]);
			}
		}
	}
}

void CollisionManager::buildCollisionLists() {
	unordered_map<int, vector<Collider*>> xLists = this->buildSingleAxisList(this->m_XList);
	unordered_map<int, vector<Collider*>> yLists = this->buildSingleAxisList(this->m_YList);

	for (register auto it = this->m_CollisionLists.begin(); it != this->m_CollisionLists.end(); ++it) {
		it->second.clear();
	}

	for (register auto it = xLists.begin(); it != xLists.end(); ++it) {
		this->buildSingleCollisionList(it->first, it->second, yLists[it->first]);
	}
}

void CollisionManager::updateSingleCollider(Collider& col) {
	vector<Collider*> colList = this->getCollisionList(col);

	if (colList.size() > 0 
		&& (!col.isStationary() && col.isSolid())) {
		Collider* currCollider = NULL;
		for (register int i = 0; i < colList.size(); ++i) {
			currCollider = colList[i];

			if (currCollider && currCollider->isSolid()) {
				col.repositionAfterObjectCollision(*currCollider);
			}
		}
	}
}

void CollisionManager::update(float dtAsSeconds) {
	this->updateXList();
	this->updateYList();

	this->buildCollisionLists();

	for (register auto it = this->m_Colliders.begin(); it != this->m_Colliders.end(); ++it) {
		this->updateSingleCollider(*it->second);
	}

	this->cleanUp();
}

void CollisionManager::cleanUp() {

}

void CollisionManager::print() {

}