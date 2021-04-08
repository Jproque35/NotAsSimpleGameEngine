#include "Engine.h"
#include "GameObjectManager.h"
#include "DrawableManager.h"
#include "DrawableObject.h"

void Engine::draw() {
	this->m_Window.clear(Color::Black);

	DrawableManager* dm = DrawableManager::getInstance();

	vector<int> idList = dm->getIdList();
	for (int i = 0; i < idList.size(); ++i) {
		DrawableObject* currDrawable = &dm->get(idList[i]);

		if (currDrawable && currDrawable->getOwner().isActive()) {
			m_Window.draw(currDrawable->getGraphic());
		}
	}

	this->m_Window.display();
}