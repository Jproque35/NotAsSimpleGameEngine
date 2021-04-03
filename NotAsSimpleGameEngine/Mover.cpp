#include "Mover.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"

Mover::Mover(float x, float y)
	: Entity(x, y),
	m_Speed(20.0f),
	m_TravelDirection(0.0f, 0.0f) {
	Vector2f rectSize(50.0f, 50.0f);
	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Red);

	this->m_Collider = new Collider(*this, this->m_Position, rectSize);
	this->m_TravelDirection.x = this->m_Speed;
	this->m_TravelDirection.y = this->m_Speed;

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

Mover::~Mover() {
	std::cout << "Destroying Mover..." << std::endl;
}

void Mover::processCollisions(float dtAsSeconds) {
	vector<Collider*> collisionList = this->m_Collider->getCollisionList();

	if (collisionList.size() > 0) {

		for (int i = 0; i < collisionList.size(); ++i) {
			Collision currCollision = this->m_Collider->getCollisionData(*collisionList[i]);

			CollisionDirection colDir = std::get<1>(currCollision);

			if (colDir == CollisionDirection::Up && this->m_TravelDirection.y < 0.0f) {
				this->m_TravelDirection.y = -1 * this->m_TravelDirection.y;
			}
			else if (colDir == CollisionDirection::Down && this->m_TravelDirection.y > 0.0f) {
				this->m_TravelDirection.y = -1 * this->m_TravelDirection.y;
			}
			else if (colDir == CollisionDirection::Left && this->m_TravelDirection.x < 0.0f) {
				this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
			}
			else if (colDir == CollisionDirection::Right && this->m_TravelDirection.x > 0.0f) {
				this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
			}
		}

	}

}

void Mover::update(float dtAsSeconds) {
	this->processCollisions(dtAsSeconds);

	this->Move(this->m_TravelDirection.x * dtAsSeconds, this->m_TravelDirection.y * dtAsSeconds);
}