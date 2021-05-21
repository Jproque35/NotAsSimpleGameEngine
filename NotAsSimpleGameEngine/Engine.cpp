#include "Engine.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "DrawableManager.h"
#include "FontManager.h"
#include "SoundFileManager.h"
#include "TextManager.h"
#include "TestScene.h"
#include "PongScene.h"
#include "SimpleCollisionManager.h"

Engine* Engine::instance = NULL;

Engine::Engine() {
	//this->resolution.x = VideoMode::getDesktopMode().width;
	//this->resolution.x = VideoMode::getDesktopMode().height;
	//this->resolution.y = VideoMode::getDesktopMode().height;

	this->resolution.x = 640.0f;
	this->resolution.y = 720.0f;

	this->m_Window.create(VideoMode(resolution.x, resolution.y), "Simple Game Engine");
}

Engine::~Engine() {
	GameObjectManager::resetInstance();
	SceneManager::resetInstance();
	InputManager::resetInstance();
	CollisionManager::resetInstance();
	DrawableManager::resetInstance();
	FontManager::resetInstance();
	SoundFileManager::resetInstance();
	TextManager::resetInstance();
	SimpleCollisionManager::resetInstance();
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

	TestScene* testScene = new TestScene();
	SceneManager::getInstance()->add(*testScene);

	//PongScene* pongScene = new PongScene();
	//SceneManager::getInstance()->add(*pongScene);

	FontManager::getInstance()->loadFile("game_over");

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