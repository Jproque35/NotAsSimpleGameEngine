#include "PongScene.h"
#include "FontManager.h"
#include "TextManager.h"
#include "PongBlock.h"
#include "PongBlockManager.h"
#include "PongBall.h"
#include "Engine.h"
#include "PongPaddle.h"
#include "PongGameManager.h"

PongScene::PongScene() :
	Scene(Engine::getInstance()->resolution.x, Engine::getInstance()->resolution.y) {
}

PongScene::~PongScene() {
	PongGameManager::resetInstance();
}

void PongScene::enter(float dtAsSeconds) {
	Scene::enter(dtAsSeconds);
	PongGameManager::getInstance()->reset();
}

void PongScene::update(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
	PongGameManager::getInstance()->update(dtAsSeconds);
}

void PongScene::exit(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
}