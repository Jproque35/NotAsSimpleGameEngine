#include "Engine.h"
#include "GameObjectManager.h"
#include "DrawableManager.h"
#include "DrawableObject.h"
#include "FontManager.h"
#include "TextManager.h"

void Engine::draw() {
	this->m_Window.clear(Color::Black);

	DrawableManager* dm = DrawableManager::getInstance();
	TextManager* tm = TextManager::getInstance();

	vector<int> idList = dm->getIdList();
	DrawableObject* currDrawable = NULL;
	for (int i = 0; i < idList.size(); ++i) {
		currDrawable = &dm->get(idList[i]);

		if (currDrawable && currDrawable->getOwner().isActive()) {
			m_Window.draw(currDrawable->getGraphic());
		}
	}

	/*
	Text helloText;
	helloText.setFont(FontManager::getInstance()->get("assets/fonts/game_over.ttf"));
	helloText.setString("Hello World!");
	helloText.setCharacterSize(72);
	helloText.setFillColor(Color::White);
	helloText.setPosition(Vector2f(0.0f,0.0f));

	this->m_Window.draw(helloText);
	*/

	Text* currText = NULL;
	for (int i = 0; i < tm->size(); ++i) {
		currText = &tm->get(i);

		if (currText) {
			this->m_Window.draw(*currText);
		}
	}

	this->m_Window.display();
}