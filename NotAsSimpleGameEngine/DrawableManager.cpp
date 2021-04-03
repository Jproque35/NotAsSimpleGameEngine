#include "DrawableManager.h"
#include "CompactVector.cpp"

DrawableManager* DrawableManager::instance = NULL;

DrawableManager::DrawableManager() {
	this->m_Storage = new CompactVector<DrawableObject>(128);
}

DrawableManager::~DrawableManager() {
	cout << "***DrawableManager: Deleting DrawableManager..." << endl;
	
	delete(this->m_Storage);
}

DrawableManager* DrawableManager::getInstance() {
	if (!instance) {
		instance = new DrawableManager();
	}

	return instance;
}

void DrawableManager::resetInstance() {
	if (instance) {
		delete(instance);
	}

	instance = NULL;
}

int DrawableManager::add(DrawableObject& obj) {
	cout << "DrawableManager: Adding DrawableObject to manager..." << endl;
	return this->m_Storage->add(obj);
}

DrawableObject& DrawableManager::get(int id) inline const {
	return this->m_Storage->get(id);
}

void DrawableManager::erase(int id) {
	cout << "DrawableManager: Marking object with address " << &this->m_Storage->get(id) << " for deletion." << endl;
	this->m_Storage->erase(id);
}

int DrawableManager::size() inline const {
	return this->m_Storage->size();
}

void DrawableManager::cleanUp() {
	this->m_Storage->cleanUp();
}