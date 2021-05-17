#include "Collider.h"
#include "GameObject.h"
#include "CircleCollider.h"

Collider::Collider(GameObject& owner, ColliderType type, bool solid, bool stationary) :
	GameObjectComponent(owner),
	m_Type(type),
	m_Solid(solid),
	m_Stationary(stationary)
	{}

Collider::~Collider() {
	cout << "Collider: Destroying Collider..." << endl;
}

bool Collider::intersects(const Collider& col) const {
	if (col.m_Type == ColliderType::CIRCLE) {
		return this->intersectsCircle(dynamic_cast<const CircleCollider&>(col));
	}
	else if (col.m_Type == ColliderType::RECTANGLE) {
		return this->intersectsRectangle();
	}

	return false;
}

vector<Collider*> Collider::getCollisionList() const {
	return vector<Collider*>();
}