#include "RectangleCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"

SSCollisionManager* SSCollisionManager::instance = NULL;

SSCollisionManager::SSCollisionManager() :
	currTime(0.0f) {}

SSCollisionManager::~SSCollisionManager() {

	cout << "***CollisionManager: Destroying CollisionManager.." << endl;

	for (auto it = this->m_Colliders.begin(); it != this->m_Colliders.end(); ++it) {
		if (it->second != NULL) {
			delete(it->second);
		}
		this->m_Colliders[it->first] = NULL;
	}
}

SSCollisionManager* SSCollisionManager::getInstance() {
	if (!instance) {
		instance = new SSCollisionManager();
	}

	return instance;
}

void SSCollisionManager::resetInstance() {
	if (instance) {
		delete(instance);
	}

	instance = NULL;
}

void SSCollisionManager::addXEntries(RectangleColliderOld& col) {
	CollisionEntry xStart;
	CollisionEntry xEnd;

	xStart.owner = &col;
	xStart.value = col.getLeft();
	xStart.type = CollisionEntryType::Start;

	xEnd.owner = &col;
	xEnd.value = col.getLeft() + col.getWidth();
	xEnd.type = CollisionEntryType::End;

	this->m_XList.push_back(xStart);
	//cout << "CollisionManager: Added start entry for Collider with id " << col.getId() << " and value " << xStart.value << endl;
	this->m_XList.push_back(xEnd);
	//cout << "CollisionManager: Added end entry for Collider with id " << col.getId() << " and value " << xEnd.value << endl;
}

void SSCollisionManager::addYEntries(RectangleColliderOld& col) {
	CollisionEntry yStart;
	CollisionEntry yEnd;

	yStart.owner = &col;
	yStart.value = col.getTop();
	yStart.type = CollisionEntryType::Start;

	yEnd.owner = &col;
	yEnd.value = col.getTop() + col.getHeight();
	yEnd.type = CollisionEntryType::End;

	this->m_YList.push_back(yStart);
	//cout << "CollisionManager: Added start entry for Collider with id " << col.getId() << " and value " << yStart.value << endl;
	this->m_YList.push_back(yEnd);
	//cout << "CollisionManager: Added end entry for Collider with id " << col.getId() << " and value " << yEnd.value << endl;
}

void SSCollisionManager::add(RectangleColliderOld& col) {
	this->m_Colliders[col.getId()] = &col;

	this->addXEntries(col);
	this->addYEntries(col);
}

RectangleColliderOld& SSCollisionManager::get(int id) {
	return *this->m_Colliders[id];
}

vector<RectangleColliderOld*> SSCollisionManager::getCollisionList(const RectangleColliderOld& col) {
	return this->m_CollisionLists[col.getId()];
}

void SSCollisionManager::updateXList() {
	float x, width;
	for (auto it = this->m_XList.begin(); it != this->m_XList.end(); ++it) {
		x = it->owner->getLeft();
		width = it->owner->getWidth();

		if (it->type == CollisionEntryType::Start) {
			it->value = x;
		}
		else {
			it->value = x + width;
		}
	}

	sort(this->m_XList.begin(), this->m_XList.end());
}

void SSCollisionManager::updateYList() {
	float y, height;
	for (auto it = this->m_YList.begin(); it != this->m_YList.end(); ++it) {
		y = it->owner->getTop();
		height = it->owner->getHeight();

		if (it->type == CollisionEntryType::Start) {
			it->value = y;
		}
		else {
			it->value = y + height;
		}
	}

	sort(this->m_YList.begin(), this->m_YList.end());
}

void SSCollisionManager::processCollisionEntry(
	CollisionEntry entry, 
	unordered_map<int, vector<RectangleColliderOld*>>& intersectionLists, 
	list<int>& activeColliderIds) {
	RectangleColliderOld* currCollider = entry.owner;
	CollisionEntryType currType = entry.type;

	if (currType == CollisionEntryType::Start) {
		for (auto it = activeColliderIds.begin(); it != activeColliderIds.end(); ++it) {
			intersectionLists[currCollider->getId()].push_back(this->m_Colliders[*it]);
		}

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

unordered_map<int, vector<RectangleColliderOld*>> SSCollisionManager::buildSingleAxisList(
	vector<CollisionEntry>& axisList) {
	unordered_map<int, vector<RectangleColliderOld*>> intersectionLists;
	list<int> activeColliderIds;

	for(int i = 0; i < axisList.size(); ++i) {
		if (axisList[i].owner->getOwner().isActive()) {
			this->processCollisionEntry(axisList[i], intersectionLists, activeColliderIds);
		}
	}

	return intersectionLists;
}

void SSCollisionManager::buildSingleCollisionList(
	int id, 
	vector<RectangleColliderOld*>& colList, 
	vector<RectangleColliderOld*>& checkList) {
	for (int i = 0; i < colList.size(); ++i) {
		for (int j = 0; j < checkList.size(); ++j) {
			if ((colList[i] == checkList[j])
					&& this->m_Colliders[id]->intersects(*colList[i]) ) {
				this->m_CollisionLists[id].push_back(colList[i]);
			}
		}
	}
}

void SSCollisionManager::buildCollisionLists() {
	unordered_map<int, vector<RectangleColliderOld*>> xLists = this->buildSingleAxisList(this->m_XList);
	unordered_map<int, vector<RectangleColliderOld*>> yLists = this->buildSingleAxisList(this->m_YList);

	for (auto it = this->m_CollisionLists.begin(); it != this->m_CollisionLists.end(); ++it) {
		it->second.clear();
	}

	for (auto it = xLists.begin(); it != xLists.end(); ++it) {
		this->buildSingleCollisionList(it->first, it->second, yLists[it->first]);
	}
}

void SSCollisionManager::updateSingleCollider(RectangleColliderOld& col) {
	vector<RectangleColliderOld*> colList = this->getCollisionList(col);

	if (colList.size() > 0 
		&& (!col.isStationary() && col.isSolid())) {
		for (int i = 0; i < colList.size(); ++i) {
			RectangleColliderOld* currCollider = colList[i];

			if (currCollider && currCollider->isSolid()) {
				col.repositionAfterObjectCollision(*currCollider);
			}
		}
	}
}

void SSCollisionManager::update(float dtAsSeconds) {
	this->updateXList();
	this->updateYList();

	this->buildCollisionLists();

	for (auto it = this->m_Colliders.begin(); it != this->m_Colliders.end(); ++it) {
		this->updateSingleCollider(*it->second);
	}

	this->cleanUp();
}

void SSCollisionManager::cleanUp() {

}

void SSCollisionManager::print() {

}