#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() :
	m_CurrScene(0) {}

SceneManager::~SceneManager() {
	std::cout << "***SceneManager: Deleting Scenes..." << std::endl;
	for (int i = 0; i < this->m_Scenes.size(); ++i) {
		if (this->m_Scenes[i] != NULL) {
			delete(this->m_Scenes[i]);
		}
		this->m_Scenes[i] = NULL;
	}
}

SceneManager* SceneManager::getInstance() {
	if (!instance) {
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::resetInstance() {
	if (instance) {
		delete(instance);
	}
	instance = NULL;
}

void SceneManager::add(Scene& obj) {
	this->m_Scenes.push_back(&obj);
}

void SceneManager::setCurrentScene(int i) {
	this->m_CurrScene = i;
}

Scene& SceneManager::getCurrentScene() const {
	return *this->m_Scenes[m_CurrScene];
}

bool SceneManager::sceneExists(int i) const {
	return i < this->m_Scenes.size()
		&& this->m_Scenes[i] != NULL;
}