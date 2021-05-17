#include "TestScene.h"
#include "BasicPlayer.h"
#include "GameObjectManager.h"
#include "Box.h"
#include "Mover.h"
#include <iostream>
#include "RectangleCollider.h"
#include "CollisionManager.h"
#include "FontManager.h"
#include "TextManager.h"
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

	Text* helloText = new Text();
	helloText->setFont(FontManager::getInstance()->get("assets/fonts/game_over.ttf"));
	helloText->setString("Hello World!");
	helloText->setCharacterSize(72);
	helloText->setFillColor(Color::White);
	helloText->setPosition(Vector2f(0.0f, 0.0f));

	TextManager::getInstance()->add(*helloText);
}

void TestScene::update(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
	this->m_Seconds += dtAsSeconds;
	if (this->m_Seconds >= 20.0f) {
		std::cout << "TestScene: Tick" << std::endl;
		SSCollisionManager::getInstance()->print();
		this->m_Seconds = 0.0f;
	}
}

void TestScene::exit(float dtAsSeconds) {
	Scene::exit(dtAsSeconds);
}