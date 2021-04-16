#include "PongGameManager.h"
#include "PongBlockManager.h"
#include "TextManager.h"
#include "FontManager.h"
#include "PongBall.h"
#include "PongPaddle.h"
#include "PongBlock.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <sstream>

PongGameManager* PongGameManager::instance = NULL;

PongGameManager::PongGameManager() :
	m_StartCount(3.0f),
	m_SceneWidth(SceneManager::getInstance()->getCurrentScene().getWidth()),
	m_SceneHeight(SceneManager::getInstance()->getCurrentScene().getHeight()),
	m_Lives(3) {
	this->m_Blocks = PongBlockManager::getInstance();

	this->m_ScoreText = new Text();
	m_ScoreText->setFont(FontManager::getInstance()->get("game_over"));
	m_ScoreText->setPosition(Vector2f(0.0f, 0.0f));
	m_ScoreText->setFillColor(Color::White);
	m_ScoreText->setCharacterSize(72.0f);
	TextManager::getInstance()->add(*this->m_ScoreText);

	this->m_WinText = new Text();
	this->m_WinText->setFont(FontManager::getInstance()->get("game_over"));
	this->m_WinText->setPosition(Vector2f(this->m_SceneWidth / 2, this->m_SceneHeight / 2));
	this->m_WinText->setFillColor(Color::White);
	this->m_WinText->setCharacterSize(72.0f);
	TextManager::getInstance()->add(*this->m_WinText);

	this->m_CountdownText = new Text();
	this->m_CountdownText->setFont(FontManager::getInstance()->get("game_over"));
	this->m_CountdownText->setPosition(Vector2f(this->m_SceneWidth / 2, this->m_SceneHeight / 2));
	this->m_CountdownText->setFillColor(Color::White);
	this->m_CountdownText->setString("");
	this->m_CountdownText->setCharacterSize(72.0f);
	TextManager::getInstance()->add(*this->m_CountdownText);

	this->m_Ball = new PongBall();
	this->m_Paddle = new PongPaddle();
}

PongGameManager::~PongGameManager() {
	cout << "PongGameManager: Destroying PongGameManager..." << endl;
	this->m_Blocks->resetInstance();
}

void PongGameManager::reset() {
	this->m_StartCount = 3.0f;
	this->m_Lives = 3;
	this->m_Blocks->deactivateAll();
	this->m_WinText->setString("");

	float xPos = 40.0f, yPos = 16.0f;
	while (this->m_Blocks->getAmountFree() > 0) {
		this->m_Blocks->getFreeBlock().init(xPos, yPos);

		xPos += 80.f;
		if (xPos >= this->m_SceneWidth) {
			xPos = 40.0f;
			yPos += 32.0f;
		}
	}

	this->resetPaddleAndBall();
}

void PongGameManager::resetPaddleAndBall() {
	this->m_Ball->init(this->m_SceneWidth / 2, this->m_SceneHeight * 0.8f);
	this->m_Paddle->init(this->m_SceneWidth / 2, this->m_SceneHeight - 8.0f);
}

void PongGameManager::update(float dtAsSeconds) {
	if (InputManager::getInstance()->isKeyDown(Button::Fire)) {
		this->reset();
	}

	ostringstream ss;
	ss << "Lives: " << this->m_Lives;
	this->m_ScoreText->setString(ss.str());

	if (this->m_Lives == 0) {
		this->m_WinText->setString("You Lose...\n Press Spacebar to try again!");
		this->m_StartCount = 3.0f;
	}
	if (this->m_Blocks->getAmountFree() == this->m_Blocks->getMaxSize()) {
		this->m_WinText->setString("You win!\n Press Spacebar to play again!");
		this->m_StartCount = 3.0f;
	}
	else {
		if (this->m_StartCount >= 0.0f) {
			ostringstream ss;
			ss << this->m_StartCount;
			this->m_CountdownText->setString(ss.str());
			this->m_StartCount -= dtAsSeconds;
		}
		else {
			this->m_CountdownText->setString("");
		}
	}
}