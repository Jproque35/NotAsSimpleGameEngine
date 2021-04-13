#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"

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

CollisionManager* CollisionManager::getInstance() {
	if (!instance) {
		instance = new CollisionManager();
	}

	return instance;
}

void CollisionManager::resetInstance() {
	if (instance) {
		delete(instance);
	}

	instance = NULL;
}

void CollisionManager::addXEntries(Collider& col) {
	CollisionEntry xStart;
	CollisionEntry xEnd;

	xStart.owner = &col;
	xStart.value = col.getOwner().getPosition().x;
	//xStart.value = col.getLeft();
	xStart.type = CollisionEntryType::Start;

	xEnd.owner = &col;
	xEnd.value = col.getOwner().getPosition().x + col.getWidth();
	//xEnd.value = col.getLeft() + col.getWidth();
	xEnd.type = CollisionEntryType::End;

	this->m_XList.push_back(xStart);
	cout << "CollisionManager: Added start entry for Collider with id " << col.getId() << " and value " << xStart.value << endl;
	this->m_XList.push_back(xEnd);
	cout << "CollisionManager: Added end entry for Collider with id " << col.getId() << " and value " << xEnd.value << endl;
}

void CollisionManager::addYEntries(Collider& col) {
	CollisionEntry yStart;
	CollisionEntry yEnd;

	yStart.owner = &col;
	yStart.value = col.getOwner().getPosition().y;
	//yStart.value = col.getTop();
	yStart.type = CollisionEntryType::Start;

	yEnd.owner = &col;
	yEnd.value = col.getOwner().getPosition().y + col.getHeight();
	//yEnd.value = col.getTop() + col.getHeight();
	yEnd.type = CollisionEntryType::End;

	this->m_YList.push_back(yStart);
	cout << "CollisionManager: Added start entry for Collider with id " << col.getId() << " and value " << yStart.value << endl;
	this->m_YList.push_back(yEnd);
	cout << "CollisionManager: Added end entry for Collider with id " << col.getId() << " and value " << yEnd.value << endl;
}

void CollisionManager::add(Collider& col) {
	this->m_Colliders[col.getId()] = &col;

	this->addXEntries(col);
	this->addYEntries(col);
}

Collider& CollisionManager::get(int id) {
	return *this->m_Colliders[id];
}

vector<Collider*> CollisionManager::getCollisionList(const Collider& col) {
	return this->m_CollisionLists[col.getId()];
}

void CollisionManager::updateXList() {
	for (auto it = this->m_XList.begin(); it != this->m_XList.end(); ++it) {
		float x = it->owner->getOwner().getPosition().x;
		//float x = it->owner->getLeft();
		float width = it->owner->getWidth();
		//float width = it->owner->getWidth();

		if (it->type == CollisionEntryType::Start) {
			it->value = x;
		}
		else {
			it->value = x + width;
		}
	}

	sort(this->m_XList.begin(), this->m_XList.end());
}

void CollisionManager::updateYList() {
	for (auto it = this->m_YList.begin(); it != this->m_YList.end(); ++it) {
		float y = it->owner->getOwner().getPosition().y;
		//float y = it->owner->getTop();
		float height = it->owner->getHeight();
		//float height = it->owner->getHeight();

		if (it->type == CollisionEntryType::Start) {
			it->value = y;
		}
		else {
			it->value = y + height;
		}
	}

	sort(this->m_YList.begin(), this->m_YList.end());
}

void CollisionManager::processCollisionEntry(CollisionEntry entry, unordered_map<int, vector<Collider*>>& intersectionLists, list<int>& activeColliderIds) {
	Collider* currCollider = entry.owner;
	CollisionEntryType currType = entry.type;

	if (currType == CollisionEntryType::Start) {
		activeColliderIds.push_back(currCollider->getId());
	}
	else {
		activeColliderIds.remove(currCollider->getId());
	}

	for (auto it2 = activeColliderIds.begin(); it2 != activeColliderIds.end(); ++it2) {
		if (*it2 != currCollider->getId()) {
			intersectionLists[*it2].push_back(currCollider);
		}
	}
}

unordered_map<int, vector<Collider*>> CollisionManager::buildSingleAxisList(vector<CollisionEntry>& axisList) {
	unordered_map<int, vector<Collider*>> intersectionLists;
	list<int> activeColliderIds;

	for(int i = 0; i < axisList.size(); ++i) {
		if (axisList[i].owner->getOwner().isActive()) {
			this->processCollisionEntry(axisList[i], intersectionLists, activeColliderIds);
		}
	}

	return intersectionLists;
}

void CollisionManager::buildSingleCollisionList(int id, vector<Collider*>& colList, vector<Collider*>& checkList) {
	for (int i = 0; i < colList.size(); ++i) {
		for (int j = 0; j < checkList.size(); ++j) {
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

	for (auto it = this->m_CollisionLists.begin(); it != this->m_CollisionLists.end(); ++it) {
		it->second.clear();
	}

	for (auto it = xLists.begin(); it != xLists.end(); ++it) {
		this->buildSingleCollisionList(it->first, it->second, yLists[it->first]);
	}
}

void CollisionManager::updateSingleCollider(Collider& col) {
	vector<Collider*> colList = this->getCollisionList(col);

	if (colList.size() > 0 
		&& (!col.isStationary() && col.isSolid())) {
		for (int i = 0; i < colList.size(); ++i) {
			Collider* currCollider = colList[i];

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

	for (auto it = this->m_Colliders.begin(); it != this->m_Colliders.end(); ++it) {
		this->updateSingleCollider(*it->second);
	}

	this->cleanUp();
}

void CollisionManager::cleanUp() {

}

void CollisionManager::print() {

}