#include "TestScene.h"
#include "BasicPlayer.h"
#include "GameObjectManager.h"
#include "Box.h"
#include "Mover.h"
#include <iostream>
#include "Collider.h"
#include "CollisionManager.h"
//#include "Engine.h"

TestScene::TestScene() : 
	Scene(640.0f, 640.0f),
	m_Seconds(0.0f) {}

void TestScene::enter(float dtAsSeconds) {
	Scene::enter(dtAsSeconds);
	std::cout << "Entering Test Scene" << std::endl;

	testPlayer = new BasicPlayer();
	testBox = new Box();
	testMover = new Mover();

	testPlayer->init(200.0f, 200.0f);
	testBox->init(300.0f, 300.0f);
	testMover->init(0.0f, 0.0f);
}

void TestScene::update(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
	this->m_Seconds += dtAsSeconds;
	if (this->m_Seconds >= 20.0f) {
		std::cout << "TestScene: Tick" << std::endl;
		CollisionManager::getInstance()->print();
		this->m_Seconds = 0.0f;
	}
}

void TestScene::exit(float dtAsSeconds) {
	Scene::exit(dtAsSeconds);
}