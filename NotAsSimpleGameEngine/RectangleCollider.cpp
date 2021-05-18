#include "RectangleCollider.h"
#include "GameObject.h"
#include "CircleCollider.h"

RectangleCollider::RectangleCollider(
	GameObject& owner,
	const Vector2f& dimensions,
	bool solid,
	bool stationary) : 
	Collider(owner, ColliderType::RECTANGLE, solid, stationary),
	m_Height(dimensions.y),
	m_Width(dimensions.x) {}

RectangleCollider::~RectangleCollider() {
	cout << "RectangleCollider: Deleting RectangleCollider" << endl;
}

bool RectangleCollider::intersectsCircle(const CircleCollider& col) const {
	return col.intersects(*this);
}

bool RectangleCollider::intersectsRectangle(const RectangleCollider& col) const {
	bool xIntersection = this->getMinX() < col.getMaxX() && this->getMaxX() > col.getMinX();
	bool yIntersection = this->getMinY() < col.getMinY() && this->getMaxY() > col.getMaxY();

	return xIntersection && yIntersection;
}

float RectangleCollider::getMinX() const {
	return this->m_Owner->getPosition().x - this->m_Width / 2;
}

float RectangleCollider::getMinY() const {
	return this->m_Owner->getPosition().y - this->m_Height / 2;
}

float RectangleCollider::getMaxX() const {
	return this->m_Owner->getPosition().x + this->m_Width / 2;
}

float RectangleCollider::getMaxY() const {
	return this->m_Owner->getPosition().y + this->m_Height / 2;
}

void RectangleCollider::update(float dtAsSeconds) {

}