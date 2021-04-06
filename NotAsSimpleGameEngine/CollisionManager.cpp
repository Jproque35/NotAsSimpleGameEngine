#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

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

int CollisionManager::add(const Collider& col) {
	CollisionManagerEntry xStart;
	xStart.owner = &col;
	xStart.value = col.getX();
	xStart.type = CollisionManagerEntryType::Start;
	this->m_XList.push_back(xStart);

	CollisionManagerEntry xEnd;
	xEnd.owner = &col;
	xEnd.value = col.getX() + col.getWidth();
	xEnd.type = CollisionManagerEntryType::End;
	this->m_XList.push_back(xEnd);

	CollisionManagerEntry yStart;
	yStart.owner = &col;
	yStart.value = col.getY();
	yStart.type = CollisionManagerEntryType::Start;
	this->m_YList.push_back(yStart);

	CollisionManagerEntry yEnd;
	yEnd.owner = &col;
	yEnd.value = col.getY() + col.getHeight();
	yEnd.type = CollisionManagerEntryType::End;
	this->m_YList.push_back(yEnd);

	return -1;
}


void CollisionManager::erase(int id) {

}

vector<Collider*> CollisionManager::getCollisionList(const Collider& col) {
	vector<Collider*> desire;

	return desire;
}

void CollisionManager::updateSingleCollider(Collider& col) {
	vector<Collider*> colList = this->getCollisionList(col);

	if (colList.size() > 0 && !col.isStationary()) {
		for (int i = 0; i < colList.size(); ++i) {
			Collider* currCollider = colList[i];

			if (currCollider) {
				col.repositionAfterObjectCollision(*currCollider);
			}
		}
	}
}

void CollisionManager::updateAxes() {
	for (int i = 0; i < this->m_XList.size(); ++i) {
		CollisionManagerEntry currEntry = this->m_XList.front();
		this->m_XList.pop_front();

		if (currEntry.type == CollisionManagerEntryType::Start) {
			currEntry.value = currEntry.owner->getX();
		}
		else {
			currEntry.value = currEntry.owner->getX() + currEntry.owner->getWidth();
		}

		this->m_XList.push_back(currEntry);
	}

	for (int i = 0; i < this->m_YList.size(); ++i) {
		CollisionManagerEntry currEntry = this->m_YList.front();
		this->m_YList.pop_front();

		if (currEntry.type == CollisionManagerEntryType::Start) {
			currEntry.value = currEntry.owner->getY();
		}
		else {
			currEntry.value = currEntry.owner->getY() + currEntry.owner->getHeight();
		}

		this->m_YList.push_back(currEntry);
	}
}

void CollisionManager::update(float dtAsSeconds) {
	this->updateAxes();
	this->m_XList.sort();
	this->m_YList.sort();

	this->cleanUp();
}

void CollisionManager::cleanUp() {

}

void CollisionManager::print() {
	cout << "CollisionManager: Printing x-axis..." << endl;
	for (int i = 0; i < this->m_XList.size(); ++i) {
		CollisionManagerEntry currEntry = this->m_XList.front();
		this->m_XList.pop_front();
		this->m_XList.push_back(currEntry);

		cout << "{Owner: " << currEntry.owner << ", Value: " << currEntry.value << "}" << endl;
	}

	cout << "CollisionManager: Printing y-axis..." << endl;
	for (int i = 0; i < this->m_YList.size(); ++i) {
		CollisionManagerEntry currEntry = this->m_YList.front();
		this->m_YList.pop_front();
		this->m_YList.push_back(currEntry);

		cout << "{Owner: " << currEntry.owner << ", Value: " << currEntry.value << "}" << endl;
	}
}