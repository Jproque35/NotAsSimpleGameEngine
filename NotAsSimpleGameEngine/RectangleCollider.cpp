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

void RectangleCollider::repositionAfterRectangleCollision(const RectangleCollider& col) const {
	Collision collision = this->getCollisionData(col);

	if (std::get<0>(collision)) {
		CollisionDirection colDir = std::get<1>(collision);
		Vector2f colVector = std::get<2>(collision);
		Vector2f ownerPos = this->getOwner().getPosition();
		Vector2f newPos = this->getOwner().getPosition();

		if (colDir == CollisionDirection::Down) {
			cout << "Collision Direction is Down" << endl;
			newPos.y -= this->getMaxY() - col.getMinY();
		}
		else if (colDir == CollisionDirection::Right) {
			newPos.x -= this->getMaxX() - col.getMinX();
		}
		else if (colDir == CollisionDirection::Up) {
			newPos.y += col.getMaxY() - this->getMinY();
		}
		else if (colDir == CollisionDirection::Left) {
			newPos.x += col.getMaxX() - this->getMinX();
		}

		this->getOwner().setPosition(newPos);
	}
}

void RectangleCollider::repositionAfterCircleCollision(const CircleCollider& col) const {

}

CollisionDirection RectangleCollider::getRectangleCornerCollisionDirection(
	CollisionDirection& desire,
	const Vector2f& ownerCorner,
	const Vector2f& colCorner,
	const Vector2f& colPos,
	const CollisionDirection& compDir) const {

	Vector2f compass[4] = {
		Vector2f(0.0f, -1.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, 1.0f),
		Vector2f(-1.0f, 0.0f)
	};

	int compassIdx = 0;
	switch (compDir) {
	case(CollisionDirection::Up):
		compassIdx = 2;
		break;
	case(CollisionDirection::Right):
		compassIdx = 3;
		break;
	case(CollisionDirection::Down):
		compassIdx = 0;
		break;
	case(CollisionDirection::Left):
		compassIdx = 1;
		break;
	}

	Vector2f ownerUnitVector = MathLib::normalize(ownerCorner - colPos);
	Vector2f colUnitVector = MathLib::normalize(colCorner - colPos);

	if (MathLib::dot(compass[compassIdx], ownerUnitVector) > MathLib::dot(compass[compassIdx], colUnitVector)) {
		return compDir;
	}
	else {
		return desire;
	}
}

CollisionDirection RectangleCollider::correctRectangleHorizontalCollision(
	CollisionDirection& desire,
	const RectangleCollider& col,
	const Vector2f& diff) const {

	Vector2f ownerPos = this->getOwner().getPosition();
	Vector2f upperLeft(this->getMinX(), this->getMinY());
	Vector2f upperRight(this->getMaxX(), this->getMinY());
	Vector2f lowerLeft(this->getMinX(), this->getMaxY());
	Vector2f lowerRight(this->getMaxX(), this->getMaxY());

	Vector2f otherPos = col.getOwner().getPosition();
	Vector2f otherUpperLeft(col.getMinX(), col.getMinY());
	Vector2f otherUpperRight(col.getMaxX(), col.getMinY());
	Vector2f otherLowerLeft(col.getMinX(), col.getMaxY());
	Vector2f otherLowerRight(col.getMaxX(), col.getMaxY());

	if (desire == CollisionDirection::Left && diff.y > 0) {
		return this->getRectangleCornerCollisionDirection(desire, lowerLeft, otherUpperRight, otherPos, CollisionDirection::Down);
	}
	//Checking for Up Collision from Left
	else if (desire == CollisionDirection::Left && diff.y < 0) {
		return this->getRectangleCornerCollisionDirection(desire, upperLeft, otherLowerRight, otherPos, CollisionDirection::Up);
	}
	//Checking for Down Collision from Right
	else if (desire == CollisionDirection::Right && diff.y > 0) {
		return this->getRectangleCornerCollisionDirection(desire, lowerRight, otherUpperLeft, otherPos, CollisionDirection::Down);
	}
	//Checking for Up Collision from Right
	else if (desire == CollisionDirection::Right && diff.y < 0) {
		return this->getRectangleCornerCollisionDirection(desire, upperRight, otherLowerLeft, otherPos, CollisionDirection::Up);
	}
	else {
		return desire;
	}
}

CollisionDirection RectangleCollider::correctRectangleVerticalCollision(
	CollisionDirection& desire,
	const RectangleCollider& col,
	const Vector2f& diff) const {

	Vector2f ownerPos = this->getOwner().getPosition();
	Vector2f upperLeft(this->getMinX(), this->getMinY());
	Vector2f upperRight(this->getMaxX(), this->getMinY());
	Vector2f lowerLeft(this->getMinX(), this->getMaxY());
	Vector2f lowerRight(this->getMaxX(), this->getMaxY());

	Vector2f otherPos = col.getOwner().getPosition();
	Vector2f otherUpperLeft(col.getMinX(), col.getMinY());
	Vector2f otherUpperRight(col.getMaxX(), col.getMinY());
	Vector2f otherLowerLeft(col.getMinX(), col.getMaxY());
	Vector2f otherLowerRight(col.getMaxX(), col.getMaxY());

	if (desire == CollisionDirection::Up && diff.x < 0) {
		return this->getRectangleCornerCollisionDirection(desire, upperLeft, otherLowerRight, otherPos, CollisionDirection::Left);
	}
	else if (desire == CollisionDirection::Up && diff.x > 0) {
		return this->getRectangleCornerCollisionDirection(desire, upperRight, otherLowerLeft, otherPos, CollisionDirection::Right);
	}
	else if (desire == CollisionDirection::Down && diff.x < 0) {
		return this->getRectangleCornerCollisionDirection(desire, lowerLeft, otherUpperRight, otherPos, CollisionDirection::Left);
	}
	else if (desire == CollisionDirection::Down && diff.x > 0) {
		return this->getRectangleCornerCollisionDirection(desire, lowerRight, otherUpperLeft, otherPos, CollisionDirection::Right);
	}
	else {
		return desire;
	}
}

CollisionDirection RectangleCollider::correctRectangleCollisionDirection(
	CollisionDirection& desire,
	const RectangleCollider& col,
	const Vector2f& diff
	) const {

	if ((desire == CollisionDirection::Left || desire == CollisionDirection::Right)
		&& col.getWidth() / col.getHeight() > 1) {
		desire = this->correctRectangleHorizontalCollision(desire, col, diff);
	} else if ((desire == CollisionDirection::Up || desire == CollisionDirection::Down)
		&& col.getHeight() / col.getWidth() > 1) {
		desire = this->correctRectangleVerticalCollision(desire, col, diff);
	}

	return desire;
}

CollisionDirection RectangleCollider::getCollisionDirection(
	const Collider& col,
	const Vector2f& diff) const {

	Vector2f compass[4] = { 
		Vector2f(0.0f, -1.0f), 
		Vector2f(1.0f, 0.0f), 
		Vector2f(0.0f, 1.0f), 
		Vector2f(-1.0f, 0.0f)
	};

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
		
		return this->correctRectangleCollisionDirection(desire, 
			dynamic_cast<const RectangleCollider&>(col), 
			diff);
	}
	else {
		return desire;
	}
}

float RectangleCollider::getMinX() const {
	return this->getOwner().getPosition().x - this->m_Width / 2;
}

float RectangleCollider::getMinY() const {
	return this->getOwner().getPosition().y - this->m_Height / 2;
}

float RectangleCollider::getMaxX() const {
	return this->getOwner().getPosition().x + this->m_Width / 2;
}

float RectangleCollider::getMaxY() const {
	return this->getOwner().getPosition().y + this->m_Height / 2;
}

void RectangleCollider::update(float dtAsSeconds) {

}