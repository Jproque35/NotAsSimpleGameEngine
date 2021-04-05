#include "BasicPlayer.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"

BasicPlayer::BasicPlayer(float x, float y)
	: Entity(x, y),
	m_Speed(150.0f) {
	Vector2f rectSize(50.0f, 50.0f);
	//this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	//this->m_Collider = new Collider(*this, this->m_Position, rectSize);
	this->m_Type = EntityType::Player;


	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Green);
	this->m_Collider = new Collider(*this, rectSize, false);

	this->addComponent(*m_Collider);
	this->addComponent(*m_Graphic);

}

BasicPlayer::~BasicPlayer() {
	cout << this << ": Destroying BasicPlayer..." << endl;
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

	/*
	if (this->m_Collider->getCollisionList().size() > 0) {
		cout << "BasicPlayer: Collision Ocurring..." << endl;
	}*/
}