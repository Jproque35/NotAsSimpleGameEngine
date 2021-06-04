#include "BasicPlayer.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"
#include "SceneManager.h"
#include "CollisionManager.h"

BasicPlayer::BasicPlayer()
	: Entity(),
	m_Speed(150.0f) {
	Vector2f rectSize(24.0f, 32.0f);
	this->m_Type = EntityType::Player;

	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	//this->m_Collider = new RectangleCollider(*this, rectSize, true, false);
	//this->m_Collider = CollisionManager::getInstance()->createRectangleCollider(*this, rectSize, true, false);
	this->m_Collider = CollisionManager::getInstance()->createCircleCollider(*this, 16.0f, true, false);
	this->addComponent(*m_Collider);
	this->addComponent(*m_Graphic);
}

BasicPlayer::~BasicPlayer() {
	cout << this << ": Destroying BasicPlayer..." << endl;
}

void BasicPlayer::init(float x, float y) {
	GameObject::init(x, y);
	cout << "BasePlayer: Initialized at position " << x << ", " << y << endl;
}

Vector2f BasicPlayer::inputToVector() {
	bool upPressed = this->input->isKeyPressed(Button::Up);
	bool downPressed = this->input->isKeyPressed(Button::Down);
	bool leftPressed = this->input->isKeyPressed(Button::Left);
	bool rightPressed = this->input->isKeyPressed(Button::Right);

	Vector2f direction(0.0f, 0.0f);

	if (upPressed && !downPressed) {
		direction.y = -this->m_Speed;
		this->m_CurrDir = Direction::Up;
	}
	else if (!upPressed && downPressed) {
		direction.y = this->m_Speed;
		this->m_CurrDir = Direction::Down;
	}

	if (leftPressed && !rightPressed) {
		direction.x = -this->m_Speed;
		this->m_CurrDir = Direction::Left;
	}
	else if (!leftPressed && rightPressed) {
		direction.x = this->m_Speed;
		this->m_CurrDir = Direction::Right;
	}

	return direction;
}

void BasicPlayer::update(float dtAsSeconds) {
	Vector2f moveDir = this->inputToVector() * dtAsSeconds;

	this->Move(moveDir);

	vector<Collider*> colList = CollisionManager::getInstance()->getCollisionList(*this->m_Collider);

	if (colList.size() > 0) {
		for (int i = 0; i < colList.size(); ++i) {
			Collision newCol = this->m_Collider->getCollisionData(*colList[i]);

			string dir = "";
			CollisionDirection colDir = std::get<1>(newCol);
			if (colDir == CollisionDirection::Right) {
				dir = "Right";
			}
			else if (colDir == CollisionDirection::Left) {
				dir = "Left";
			}
			else if (colDir == CollisionDirection::Up) {
				dir = "Up";
			}
			else if (colDir == CollisionDirection::Down) {
				dir = "Down";
			}

			cout << "BasicPlayer: CollisionDirection is " << dir << endl;

		}
	}
}