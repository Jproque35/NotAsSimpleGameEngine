#include "BasicPlayer.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"

BasicPlayer::BasicPlayer()
	: Entity(),
	m_Speed(150.0f) {
	Vector2f rectSize(32.0f, 32.0f);
	this->m_Type = EntityType::Player;

	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	this->m_Collider = new Collider(*this, rectSize, true, false);

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
	Vector2f moveDir = this->inputToVector();

	this->Move(moveDir.x * dtAsSeconds, moveDir.y * dtAsSeconds);
}