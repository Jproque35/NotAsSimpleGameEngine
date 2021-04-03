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
	this->m_Collider = new Collider(*this, this->m_Position, rectSize);

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

void BasicPlayer::resolveCollision(const Collider& other) {

	Collision col = this->m_Collider->getCollisionData(other);

	if (std::get<0>(col)) {
		//std::cout << "Collision occurred with BasicPlayer" << std::endl;
		CollisionDirection colDir = std::get<1>(col);
		Vector2f colVector = std::get<2>(col);

		cout << "Collision Vector is " << colVector.x << " " << colVector.y << endl;

		if (colDir == CollisionDirection::Down) {
			this->Move(0.0f, -(this->m_Collider->getHeight() - abs(colVector.y)));
		}
		else if (colDir == CollisionDirection::Right) {
			this->Move(-( this->m_Collider->getWidth() - abs(colVector.x) ), 0.0f);
		}
		else if (colDir == CollisionDirection::Up) {
			this->Move(0.0f, other.getHeight() - abs(colVector.y));
		}
		else if (colDir == CollisionDirection::Left) {
			this->Move(other.getWidth() - abs(colVector.x), 0.0f);
		}
	}

}

void BasicPlayer::update(float dtAsSeconds) {
	Vector2f moveDir = this->inputToVector();

	this->Move(moveDir.x * dtAsSeconds, moveDir.y * dtAsSeconds);

	vector<Collider*> collisionList = this->m_Collider->getCollisionList();

	if (collisionList.size() > 0) {
		for (int i = 0; i < collisionList.size(); ++i) {
			this->resolveCollision(*collisionList[i]);
		}
	}

	//cout << "BasicPlayer position is " << this->m_Pos.x << " " << this->m_Pos.y << endl;
	//this->m_Rect->setPosition(this->m_Position);
	//this->m_Graphic->update(dtAsSeconds);
}