#include "Collider.h"
#include "MathLib.h"
#include "GameObject.h"
#include "SimpleCollisionManager.h"

Collider::Collider(GameObject& owner, const Vector2f& pos, const Vector2f& size)
	: GameObjectComponent(owner),
	m_RectCol(pos, size) {
	this->m_Id = SimpleCollisionManager::getInstance()->add(*this);
}

Collider::~Collider() {
	cout << this << ": Destroying Collider..." << endl;
}

float Collider::getX() const {
	return this->m_RectCol.left;
}

float Collider::getY() const {
	return this->m_RectCol.top;
}

void Collider::setWidth(float width) {
	this->m_RectCol.width = width;
}

float Collider::getWidth() const {
	return this->m_RectCol.width;
}

void Collider::setHeight(float height) {
	this->m_RectCol.height = height;
}

float Collider::getHeight() const {
	return this->m_RectCol.height;
}

void Collider::setPosition(float x, float y) {
	this->m_RectCol.top = y;
	this->m_RectCol.left = x;
}

bool Collider::intersects(const Collider& other) const {
	return this->m_RectCol.intersects(other.m_RectCol);
}

void Collider::printCollider() const {
	std::cout << "Collider Position: " << this->m_RectCol.left << " " << this->m_RectCol.top << std::endl;
}

CollisionDirection Collider::getCollisionDirection(const FloatRect& other) const {
	Vector2f compass[] = {
		Vector2f(0.0f, 1.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, -1.0f),
		Vector2f(-1.0f, 0.0f)
	};

	Vector2f diff(other.left - this->m_RectCol.left, other.top - this->m_RectCol.top);

	float max = 0;
	unsigned int desire = 0;
	for (int i = 0; i < 4; ++i) {
		float dot = MathLib::dot(compass[i], MathLib::normalize(diff));

		if (dot > max) {
			max = dot;
			desire = i;
		}
	}

	return (CollisionDirection)desire;
}

Collision Collider::getCollisionData(const Collider& other) const {
	if (this->m_RectCol.intersects(other.m_RectCol) && other.m_Owner->isActive()) {
		Vector2f diff(other.m_RectCol.left - this->m_RectCol.left, other.m_RectCol.top - this->m_RectCol.top);

		return std::make_tuple( true,getCollisionDirection(other.m_RectCol), diff);
	}

	return std::make_tuple(false, CollisionDirection::Up, Vector2f(0.0f, 0.0f));
}

vector<Collider*> Collider::getCollisionList() const {
	return SimpleCollisionManager::getInstance()->getCollisionList(this->m_Id);
}

void Collider::update(float dtAsSeconds) {
	this->m_RectCol.left = this->m_Owner->getPosition().x;
	this->m_RectCol.top = this->m_Owner->getPosition().y;
}

void Collider::destroy() const {
	SimpleCollisionManager::getInstance()->erase(this->m_Id);
}
