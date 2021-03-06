#include "GameObjectManager.h"
#include "Container.cpp"
#include <iostream>

GameObjectManager* GameObjectManager::instance = NULL;

GameObjectManager::GameObjectManager() :
	m_CurrFreeSlot(0) {
	this->m_Storage = new Container<GameObject>(128);

	for (int i = 0; i < maxSize; ++i) {
		this->m_Objs[i] = NULL;
	}
}

GameObjectManager::~GameObjectManager() {
	cout << "***GameObjectManager: Deleting GameObjects..." << endl;
	delete(this->m_Storage);
}

GameObjectManager* GameObjectManager::getInstance() {
	if (!instance) {
		instance = new GameObjectManager();
	}

	return instance;
}

void GameObjectManager::resetInstance() {
	if (instance) {
		delete(instance);
	}
	instance = NULL;
}

void GameObjectManager::add(GameObject& obj) {
	this->m_Storage->add(obj, obj.getId());
}

GameObject& GameObjectManager::get(int i) const {
	return this->m_Storage->get(i);
}

int GameObjectManager::size() const {
	return this->m_Storage->size();
}

void GameObjectManager::cleanUp() {
	this->m_Storage->cleanUp();
}