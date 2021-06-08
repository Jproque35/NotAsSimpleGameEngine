#include "PongPaddle.h"
#include "RectangleGraphic.h"
#include "MathLib.h"
#include "SceneManager.h"
#include "PongGameManager.h"
#include "CollisionManager.h"

PongPaddle::PongPaddle() :
	m_Speed(500.0f) {
	this->m_Tag = GameObjectTag::Player;

	Vector2f rectSize(60.0f, 16.0f);

	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	//this->m_Collider = new RectangleCollider(*this, rectSize, true, true);
	this->m_Collider = CollisionManager::getInstance()->createRectangleCollider(*this, rectSize, true, true);

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

PongPaddle::~PongPaddle() {
	cout << "PongPaddle: Deleting PongPaddle..." << endl;
}

void PongPaddle::init(float x, float y) {
	GameObject::init(x, y);
	cout << "PongPaddle: Initialized at position " << this->getPosition().x << ", " << this->getPosition().y << endl;
}

Vector2f PongPaddle::inputToVector() {
	bool upPressed = InputManager::getInstance()->isKeyPressed(Button::Up);
	bool downPressed = InputManager::getInstance()->isKeyPressed(Button::Down);
	bool leftPressed = InputManager::getInstance()->isKeyPressed(Button::Left);
	bool rightPressed = InputManager::getInstance()->isKeyPressed(Button::Right);

	Vector2f direction(0.0f, 0.0f);

	if (leftPressed && !rightPressed) {
		direction.x = -this->m_Speed;
		this->m_CurrDir = Direction::Left;
	}
	else if (!leftPressed && rightPressed) {
		direction.x = this->m_Speed;
		this->m_CurrDir = Direction::Right;
	}

	if (MathLib::magnitude(direction) > 0.0f) {
		//cout << "PongPaddle: Position is " << this->m_Position.x << ", " << this->m_Position.y << endl;
	}

	return direction;
}

void PongPaddle::update(float dtAsSeconds) {
	if (PongGameManager::getInstance()->getStartCount() <= 0.0f) {
		Vector2f moveDir = this->inputToVector() * dtAsSeconds;

		if (moveDir.x < 0 && this->m_Collider->getMinX() < 0) {
		}
		else if (moveDir.x > 0 && this->m_Collider->getMaxX() 
			> SceneManager::getInstance()->getCurrentScene().getWidth()) {
		}
		else {
			this->Move(moveDir);
		}
	}
}
