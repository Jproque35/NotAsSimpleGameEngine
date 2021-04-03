#include "Engine.h"
#include "GameObjectManager.h"
#include "DrawableManager.h"
#include "DrawableObject.h"

void Engine::draw() {
	this->m_Window.clear(Color::Black);

	/*
	GameObjectManager* gm = GameObjectManager::getInstance();

	for (int i = 0; i < gm->size(); ++i) {
		GameObject* currObj = &gm->get(i);
		if (currObj != NULL && currObj->isActive()) {
			m_Window.draw(currObj->getGraphic());
		}
	}*/

	DrawableManager* dm = DrawableManager::getInstance();

	for (int i = 0; i < dm->size(); ++i) {
		DrawableObject* currDrawable = &dm->get(i);

		if (currDrawable && currDrawable->getOwner().isActive()) {
			m_Window.draw(currDrawable->getGraphic());
		}
	}

	this->m_Window.display();
}