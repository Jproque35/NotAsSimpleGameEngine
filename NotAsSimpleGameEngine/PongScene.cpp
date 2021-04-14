#include "PongScene.h"
#include "FontManager.h"
#include "TextManager.h"
#include "PongBlock.h"
#include "PongBlockManager.h"
#include "PongBall.h"

PongScene::PongScene() :
	Scene(640.0, 640.0) {
	this->blockManager = PongBlockManager::getInstance();
}

PongScene::~PongScene() {
	PongBlockManager::resetInstance();
}

void PongScene::enter(float dtAsSeconds) {
	Scene::enter(dtAsSeconds);

	Text* scoreText = new Text();
	scoreText->setFont(FontManager::getInstance()->get("assets/fonts/game_over.ttf"));
	scoreText->setPosition(Vector2f(0.0f, 0.0f));
	scoreText->setFillColor(Color::White);
	scoreText->setString("Score: ");
	scoreText->setCharacterSize(72.0f);
	TextManager::getInstance()->add(*scoreText);
	
	float xPos = 40.0f, yPos = 16.0f;
	//for (int i = 0; i < 32; ++i) {
	while(this->blockManager->getAmountFree() > 0) {
		this->blockManager->getFreeBlock().init(xPos, yPos);

		xPos += 80.f;
		if (xPos >= this->getWidth()) {
			xPos = 40.0f;
			yPos += 32.0f;
		}
	}

	this->ball = new PongBall();
	this->ball->init(this->getWidth() / 2, this->getHeight());

}

void PongScene::update(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
}

void PongScene::exit(float dtAsSeconds) {
	Scene::update(dtAsSeconds);
}