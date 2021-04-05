#include "Engine.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SimpleCollisionManager.h"
#include "DrawableManager.h"
#include "TestScene.h"

Engine* Engine::instance = NULL;

Engine::Engine() {
	//this->resolution.x = VideoMode::getDesktopMode().width;
	//this->resolution.x = VideoMode::getDesktopMode().height;
	//this->resolution.y = VideoMode::getDesktopMode().height;

	this->resolution.x = 640.0f;
	this->resolution.y = 640.0f;

	this->m_Window.create(VideoMode(resolution.x, resolution.y), "Simple Game Engine");
	TestScene* testScene = new TestScene();
	SceneManager::getInstance()->add(*testScene);
}

Engine::~Engine() {
	GameObjectManager::resetInstance();
	SceneManager::resetInstance();
	InputManager::resetInstance();
	SimpleCollisionManager::resetInstance();
	DrawableManager::resetInstance();
}

Engine* Engine::getInstance() {
	if (!instance) {
		instance = new Engine();
	}
	return instance;
}

void Engine::resetInstance() {
	if (instance) {
		delete(instance);
	}
	instance = NULL;
}

void Engine::start() {

	Clock clock;

	while (this->m_Window.isOpen()) {

		Event event;
		while (this->m_Window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				this->m_Window.close();

			}

		}

		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();

	}

}