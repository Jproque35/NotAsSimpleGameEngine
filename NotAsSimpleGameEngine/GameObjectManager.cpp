#include "GameObjectManager.h"
#include "CompactVector.cpp"
#include <iostream>

GameObjectManager* GameObjectManager::instance = NULL;

GameObjectManager::GameObjectManager() {
	this->m_Storage = new CompactVector<GameObject>(128);
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

int GameObjectManager::add(GameObject& obj) {
	return this->m_Storage->add(obj);
}

GameObject& GameObjectManager::get(int i) inline const {
	return this->m_Storage->get(i);
}

void GameObjectManager::erase(int i) {
	cout << "GameObjectManager: Marking object with address " << &this->m_Storage->get(i) << " for deletion." << endl;
	this->m_Storage->erase(i);
}

int GameObjectManager::size() const {
	return this->m_Storage->size();
}

void GameObjectManager::cleanUp() {
	this->m_Storage->cleanUp();
}