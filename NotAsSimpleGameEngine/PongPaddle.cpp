#include "PongPaddle.h"
#include "RectangleGraphic.h"
#include "MathLib.h"
#include "SceneManager.h"
#include "PongGameManager.h"

PongPaddle::PongPaddle() :
	m_Speed(500.0f) {
	this->m_Tag = GameObjectTag::Player;

	Vector2f rectSize(60.0f, 16.0f);

	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	this->m_Collider = new RectangleColliderOld(*this, rectSize, true, true);

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

PongPaddle::~PongPaddle() {
	cout << "PongPaddle: Deleting PongPaddle..." << endl;
}

void PongPaddle::init(float x, float y) {
	GameObject::init(x, y);
	cout << "PongPaddle: Initialized at position " << this->m_Position.x << ", " << this->m_Position.y << endl;
}

Vector2f PongPaddle::inputToVector() {
	bool upPressed = this->input->isKeyPressed(Button::Up);
	bool downPressed = this->input->isKeyPressed(Button::Down);
	bool leftPressed = this->input->isKeyPressed(Button::Left);
	bool rightPressed = this->input->isKeyPressed(Button::Right);

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

		if (moveDir.x < 0 && this->m_Collider->getLeft() < 0) {
		}
		else if (moveDir.x > 0 && this->m_Collider->getLeft()
			+ this->m_Collider->getWidth() > SceneManager::getInstance()->getCurrentScene().getWidth()) {
		}
		else {
			this->Move(moveDir);
		}
	}
}
