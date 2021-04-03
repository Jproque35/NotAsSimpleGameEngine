#include "Engine.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "SimpleCollisionManager.h"

void Engine::update(float dtAsSeconds) {
	SceneManager::getInstance()->getCurrentScene().process(dtAsSeconds);
	GameObjectManager* gm = GameObjectManager::getInstance();

	for (int i = 0; i < gm->size(); ++i) {
		GameObject* currObj = &gm->get(i);
		if (currObj != NULL && currObj->isActive()) {
			//currObj->update(dtAsSeconds);
			currObj->process(dtAsSeconds);
		}
	}

	GameObjectManager::getInstance()->cleanUp();
	SimpleCollisionManager::getInstance()->cleanUp();
}