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

int CollisionManager::add(Collider& col) {
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


void CollisionManager::update(float dtAsSeconds) {

	this->cleanUp();
}

void CollisionManager::cleanUp() {

}

void CollisionManager::print() {

}