#include "TestScene.h"
#include "BasicPlayer.h"
#include "GameObjectManager.h"
#include "Box.h"
#include "Mover.h"
#include <iostream>
#include "Collider.h"

TestScene::TestScene() : 
	Scene(320, 320),
	m_Seconds(0.0f) {}

void TestScene::enter(float dtAsSeconds) {
	Scene::enter(dtAsSeconds);
	std::cout << "Entering Test Scene" << std::endl;

	testPlayer = new BasicPlayer(200.0f, 200.0f);
	GameObjectManager::getInstance()->get(testPlayer->getId()).setActive(true);

	testBox = new Box(300.0f, 300.0f);
	GameObjectManager::getInstance()->get(testBox->getId()).setActive(true);

	testMover = new Mover(0.0f, 0.0f);
	GameObjectManager::getInstance()->get(testMover->getId()).setActive(true);
}

void TestScene::update(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
	this->m_Seconds += dtAsSeconds;
	if (this->m_Seconds >= 1.0f) {
		std::cout << "TestScene: Tick" << std::endl;
		this->m_Seconds = 0.0f;
	}
}

void TestScene::exit(float dtAsSeconds) {
	Scene::exit(dtAsSeconds);
}