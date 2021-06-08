#include "CircleCollider.h"
#include "GameObject.h"
#include "MathLib.h"

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

bool CircleCollider::intersectsRectangle(const RectangleCollider& col) const {
	Vector2f ownerPos = this->getOwner().getPosition();
	float testX = ownerPos.x;
	float testY = ownerPos.y;

	if (ownerPos.x < col.getMinX()) {
		testX = col.getMinX();
	}
	else if (ownerPos.x > col.getMaxX()) {
		testX = col.getMaxX();
	}

	if (ownerPos.y < col.getMinY()) {
		testY = col.getMinY();
	}
	else if (ownerPos.y > col.getMaxY()) {
		testY = col.getMaxY();
	}
	
	float diffX = testX - ownerPos.x;
	float diffY = testY - ownerPos.y;

	float dist = sqrt(diffX * diffX + diffY * diffY);

	return dist < this->m_Radius;
}

bool CircleCollider::intersectsCircle(const CircleCollider& col) const {
	float distX = col.getOwner().getPosition().x - this->getOwner().getPosition().x;
	float distY = col.getOwner().getPosition().y - this->getOwner().getPosition().y;
	float dist = sqrt(distX * distX + distY * distY);

	return dist < this->m_Radius + col.m_Radius;
}

CollisionDirection CircleCollider::getCollisionDirection(const Collider& col, const Vector2f& diff) const {
	Vector2f compass[4] = {
	Vector2f(0.0f, -1.0f),
	Vector2f(1.0f, 0.0f),
	Vector2f(0.0f, 1.0f),
	Vector2f(-1.0f, 0.0f)
	};

	CollisionDirection desire = CollisionDirection::Up;
	Vector2f unitDiff = MathLib::normalize(diff);
	float currDot = 0.0f;
	float maxDot = FLT_MIN;
	for (int i = 0; i < 4; ++i) {
		currDot = MathLib::dot(compass[i], unitDiff);

		if (currDot > maxDot) {
			maxDot = currDot;
			desire = (CollisionDirection)i;
		}
	}

	return desire;
}


void CircleCollider::repositionAfterRectangleCollision(const RectangleCollider& col) const {
	if (this->intersects(col)) {
		CollisionDirection dir = this->getCollisionDirection(col, col.getOwner().getPosition() - this->getOwner().getPosition());

		Vector2f newPos = this->getOwner().getPosition();
		switch (dir) {
		case(CollisionDirection::Up):
			newPos.y += this->m_Radius - (newPos.y - col.getMaxY());
			break;
		case(CollisionDirection::Down):
			newPos.y -= this->m_Radius - (col.getMinY() - newPos.y);
			break;
		case(CollisionDirection::Left):
			newPos.x += this->m_Radius - (newPos.x - col.getMaxX());
			break;
		case(CollisionDirection::Right):
			newPos.x -= this->m_Radius - (col.getMinX() - newPos.x);
			break;
		}

		this->getOwner().setPosition(newPos);
	}
}

void CircleCollider::repositionAfterCircleCollision(const CircleCollider& col) const {

}

float CircleCollider::getMinX() const {
	return this->getOwner().getPosition().x - this->m_Radius;
}

float CircleCollider::getMaxX() const {
	return this->getOwner().getPosition().x + this->m_Radius;
}

float CircleCollider::getMinY() const {
	return this->getOwner().getPosition().y - this->m_Radius;
}

float CircleCollider::getMaxY() const {
	return this->getOwner().getPosition().y + this->m_Radius;
}

void CircleCollider::update(float dtAsSeconds) {

}