#include "Collider.h"
#include "GameObject.h"
#include "CircleCollider.h"
#include "CollisionManager.h"
#include "SceneManager.h"

int Collider::currFreeId = 0;

Collider::Collider(GameObject& owner, ColliderType type, bool solid, bool stationary) :
	GameObjectComponent(owner),
	m_Type(type),
	m_Solid(solid),
	m_Stationary(stationary) {
	this->m_Id = currFreeId++;
	//SSCollisionManager::getInstance()->add(*this);
	//cout << "Collider: Sent collider with id " << this->m_Id << " to collision manager" << endl;
}

Collider::~Collider() {
	cout << "Collider: Destroying Collider..." << endl;
}

bool Collider::intersects(const Collider& col) const {
	if (col.m_Type == ColliderType::CIRCLE) {
		return this->intersectsCircle(dynamic_cast<const CircleCollider&>(col));
	}
	else if (col.m_Type == ColliderType::RECTANGLE) {
		return this->intersectsRectangle(dynamic_cast<const RectangleCollider&>(col));
	}

	return false;
}

Collision Collider::getCollisionData(const Collider& col) const {
	bool collided = this->intersects(col) && col.m_Owner->isActive();
	Vector2f diff(col.m_Owner->getPosition().x - this->m_Owner->getPosition().x,
		col.m_Owner->getPosition().y - this->m_Owner->getPosition().y);
	CollisionDirection colDir = this->getCollisionDirection(col, diff);

	return std::make_tuple(collided, colDir, diff);
}

void Collider::repositionAfterObjectCollision(const Collider& col) {
	if (col.m_Type == ColliderType::RECTANGLE) {
		this->repositionAfterRectangleCollision(dynamic_cast<const RectangleCollider&>(col));
	}
	else if (col.m_Type == ColliderType::CIRCLE) {
		this->repositionAfterCircleCollision(dynamic_cast<const CircleCollider&>(col));
	}
}

void Collider::repositionAfterBoundaryCollision() {

}

vector<CollisionDirection> Collider::getBoundaryCollisionData() const {
	vector<CollisionDirection> desire;

	if (this->getMinX() < 0) {
		desire.push_back(CollisionDirection::Left);
	}

	if (this->getMinY() < 0) {
		desire.push_back(CollisionDirection::Up);
	}

	if (this->getMaxX()
	> SceneManager::getInstance()->getCurrentScene().getWidth()) {
		desire.push_back(CollisionDirection::Right);
	}

	if (this->getMaxY()
	> SceneManager::getInstance()->getCurrentScene().getHeight()) {
		desire.push_back(CollisionDirection::Down);
	}

	return desire;
}

vector<Collider*> Collider::getCollisionList() const {
	//return vector<Collider*>();
	return CollisionManager::getInstance()->getCollisionList(*this);
}

void Collider::destroy() const {

}