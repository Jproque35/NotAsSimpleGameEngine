#include "DrawableManager.h"
#include "Container.cpp"

DrawableManager* DrawableManager::instance = NULL;

DrawableManager::DrawableManager() {
	this->m_Storage = new Container<DrawableObject>(128);
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

void DrawableManager::add(DrawableObject& obj) {
	cout << "DrawableManager: Adding DrawableObject to manager..." << endl;
	this->m_Ids.push_back( obj.getId() );
	this->m_Storage->add(obj, obj.getId());
}

DrawableObject& DrawableManager::get(int id) const {
	return this->m_Storage->get(id);
}

int DrawableManager::size() const {
	return this->m_Storage->size();
}

void DrawableManager::cleanUp() {
	this->m_Storage->cleanUp();
}

vector<int> DrawableManager::getIdList() const {
	return this->m_Ids;
}