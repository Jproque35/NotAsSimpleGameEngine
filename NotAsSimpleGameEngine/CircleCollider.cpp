#include "CircleCollider.h"
#include "GameObject.h"

CircleCollider::CircleCollider(
	GameObject& owner,
	float radius,
	bool solid,
	bool stationary) :
	Collider(owner, ColliderType::CIRCLE, solid, stationary),
	m_Radius(radius) {}

CircleCollider::~CircleCollider() {
	cout << "CircleCollider: Deleting Circle..." << endl;
}

bool CircleCollider::intersectsRectangle() const {
	return false;
}

bool CircleCollider::intersectsCircle(const CircleCollider& col) const {
	float distX = col.m_Owner->getPosition().x - this->m_Owner->getPosition().x;
	float distY = col.m_Owner->getPosition().y - this->m_Owner->getPosition().y;
	float dist = sqrt(distX * distX + distY * distY);

	return dist < this->m_Radius + col.m_Radius;
}

float CircleCollider::getMinX() const {
	return this->m_Owner->getPosition().x - this->m_Radius;
}

float CircleCollider::getMaxX() const {
	return this->m_Owner->getPosition().x + this->m_Radius;
}

float CircleCollider::getMinY() const {
	return this->m_Owner->getPosition().y - this->m_Radius;
}

float CircleCollider::getMaxY() const {
	return this->m_Owner->getPosition().y + this->m_Radius;
}

void CircleCollider::update(float dtAsSeconds) {

}