#include "RectangleCollider.h"
#include "GameObject.h"
#include "CircleCollider.h"
#include "MathLib.h"

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
	bool yIntersection = this->getMinY() < col.getMaxY() && this->getMaxY() > col.getMinY();

	return xIntersection && yIntersection;
}

CollisionDirection RectangleCollider::getRectangleCollisionDirection(
	CollisionDirection& desire,
	const RectangleCollider& col,
	const Vector2f& diff) const {

	if (desire == CollisionDirection::Left || desire == CollisionDirection::Right) {
		cout << "Side Check" << endl;
		if (col.getHeight() / col.getWidth() < 1
			&& abs(diff.y) > col.getHeight() / 2) {
			if (desire == CollisionDirection::Left && diff.y > 0) {
				return CollisionDirection::Down;
			}
			else if (desire == CollisionDirection::Left && diff.y < 0) {
				return CollisionDirection::Up;
			}
			else if (desire == CollisionDirection::Right && diff.y > 0) {
				return CollisionDirection::Down;
			}
			else if (desire == CollisionDirection::Right && diff.y < 0) {
				return CollisionDirection::Up;
			}
		}
	}

	if (desire == CollisionDirection::Up || desire == CollisionDirection::Down) {
		if (col.getHeight() / col.getWidth() > 1
			&& abs(diff.x) > col.getWidth() / 2) {
			if (desire == CollisionDirection::Up && diff.x > 0) {
				return CollisionDirection::Right;
			}
			else if (desire == CollisionDirection::Up && diff.x < 0) {
				return CollisionDirection::Left;
			}
			else if (desire == CollisionDirection::Down && diff.x > 0) {
				return CollisionDirection::Right;
			}
			else if (desire == CollisionDirection::Up && diff.x < 0) {
				return CollisionDirection::Left;
			}
		}
	}

	return desire;
}

CollisionDirection RectangleCollider::getCollisionDirection(
	const Collider& col,
	const Vector2f& diff) const {

	Vector2f compass[4] = 
		{ Vector2f(0.0f, -1.0f), Vector2f(1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector2f(-1.0f, 0.0f)};

	CollisionDirection desire = CollisionDirection::Up;
	Vector2f uDiff = MathLib::normalize(diff);
	float currDot = 0.0f;
	float maxDot = FLT_MIN;
	for (int i = 0; i < 4; ++i) {
		currDot = MathLib::dot(compass[i], uDiff);

		if (currDot > maxDot) {
			maxDot = currDot;
			desire = (CollisionDirection)i;
		}
	}

	if (col.getType() == ColliderType::RECTANGLE) {
		return this->getRectangleCollisionDirection(desire, dynamic_cast<const RectangleCollider&>(col), diff);
	}
	else {
		return desire;
	}
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