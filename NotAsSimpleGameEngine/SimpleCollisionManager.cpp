#include "SimpleCollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
#include <iostream>

SimpleCollisionManager* SimpleCollisionManager::instance = NULL;

SimpleCollisionManager::SimpleCollisionManager()
	: m_Size(0) {

}

SimpleCollisionManager::~SimpleCollisionManager() {
	cout << "***SimpleCollisionManager: Deleting SimpleCollisionManager..." << endl;
	for (int i = 0; i < this->m_Colliders.size(); ++i) {
		if (this->m_Colliders[i]) {
			delete(this->m_Colliders[i]);
		}

		this->m_Colliders[i] = NULL;
	}

	this->cleanUp();
}

SimpleCollisionManager* SimpleCollisionManager::getInstance() {
	if (!instance) {
		instance = new SimpleCollisionManager();
	}

	return instance;
}

void SimpleCollisionManager::resetInstance() {
	if (instance) {
		delete(instance);
		instance = NULL;
	}
}

int SimpleCollisionManager::add(Collider& col) {
	std::cout << "Adding Collider to Manager..." << std::endl;

	if (this->m_FreeIds.size() <= 0) {
		this->m_Colliders.push_back(&col);
		++this->m_Size;
		return this->m_Size - 1;
	}
	else {
		int id = this->m_FreeIds.front();
		this->m_FreeIds.pop();
		this->m_Colliders[id] = &col;
		++this->m_Size;
		return id;
	}
}

void SimpleCollisionManager::erase(int id) {
	try {
		Collider* desire = this->m_Colliders[id];
		this->m_Colliders[id] = NULL;
		--this->m_Size;
		this->m_FreeIds.push(id);
		this->m_DeletionQueue.push(desire);
	}
	catch (exception& e) {
		cout << "CollisionManager: Collider with id " << id << " does not exist!" << endl;
	}
}

vector<Collider*> SimpleCollisionManager::getCollisionList(int id) {
	try {
		vector<Collider*> desire;

		if (id < this->m_Colliders.size() && this->m_Colliders[id] != NULL) {
			Collider* currCollider = this->m_Colliders[id];

			for (int i = 0; i < this->m_Colliders.size(); ++i) {

				if ((currCollider != this->m_Colliders[i] && this->m_Colliders[i]->getOwner().isActive())
					&& currCollider->intersects(*this->m_Colliders[i])) {
					desire.push_back(this->m_Colliders[i]);
				}
			}
		}

		return desire;
	}
	catch (exception& e) {
		cout << "CollisionManager: Collider with id " << id << " does not exist!" << endl;
	}
}

void SimpleCollisionManager::updateSingleCollider(Collider& collider) {
	vector<Collider*> colList = this->getCollisionList(collider.getId());

	if (colList.size() > 0 && !collider.isStationary()) {
		for (int j = 0; j < colList.size(); ++j) {
			Collider* currCollider = colList[j];

			if (currCollider) {
				collider.repositionAfterObjectCollision(*currCollider);
			}
		}
	}
}

void SimpleCollisionManager::update(float dtAsSeconds) {
	for (int i = 0; i < this->m_Colliders.size(); ++i) {
		Collider* currCollider = this->m_Colliders[i];
		
		if (currCollider && currCollider->getOwner().isActive()) {
			updateSingleCollider(*currCollider);
		}
	}

	this->cleanUp();
}

void SimpleCollisionManager::cleanUp() {
	while (this->m_DeletionQueue.size() > 0) {
		Collider* desire = this->m_DeletionQueue.front();
		this->m_DeletionQueue.pop();
		delete(desire);
		desire = NULL;
	}
}