#include "Collider.h"
#include "MathLib.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "SimpleCollisionManager.h"

int Collider::m_CurrFreeId = 0;

Collider::Collider(GameObject& owner, const Vector2f& dimensions, bool solid, bool stationary)
	: GameObjectComponent(owner),
	m_Solid(solid),
	m_Stationary(stationary),
	m_Height(dimensions.y),
	m_Width(dimensions.x) {
	this->m_Id = m_CurrFreeId++;
	cout << "Collider: Id set to " << this->m_Id << endl;
	//SimpleCollisionManager::getInstance()->add(*this);
	CollisionManager::getInstance()->add(*this);
}

Collider::~Collider() {
	cout << "Collider: Destroying Collider..." << endl;
}

bool Collider::isSolid() const {
	return this->m_Solid;
}

bool Collider::isStationary() const {
	return this->m_Stationary;
}

float Collider::getTop() const {
	return this->m_Owner->getPosition().y - this->m_Height / 2;
}

float Collider::getLeft() const {
	return this->m_Owner->getPosition().x - this->m_Width / 2;
}

float Collider::getWidth() const {
	return this->m_Width;
}

float Collider::getHeight() const {
	return this->m_Height;
}

bool Collider::horizontalCollision(const Collider& other) const {
	return this->getLeft() < other.getLeft() + other.m_Width
		&& other.getLeft() < this->getLeft() + this->m_Width;
}

bool Collider::verticalCollision(const Collider& other) const {
	return this->getTop() < other.getTop() + other.m_Height
		&& other.getTop() < this->getTop() + this->m_Height;
}

bool Collider::intersects(const Collider& other) const {
	return this->horizontalCollision(other) && this->verticalCollision(other);
}

vector<Collider*> Collider::getCollisionList() const {
	return CollisionManager::getInstance()->getCollisionList(*this);
}

CollisionDirection Collider::getRelativeDirection(const Collider& other, Vector2f diff) const {
	Vector2f compass[] = {
		Vector2f(0.0f, 1.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, -1.0f),
		Vector2f(-1.0f, 0.0f)
	};

	float max = 0;
	//unsigned int desire = 0;
	CollisionDirection desire = CollisionDirection::Up;
	for (int i = 0; i < 4; ++i) {
		float dot = MathLib::dot(compass[i], MathLib::normalize(diff));

		if (dot > max) {
			max = dot;
			desire = (CollisionDirection)i;
		}
	}

	
	if (desire == CollisionDirection::Left || desire == CollisionDirection::Right) {
		cout << "Side Check" << endl;
		if (other.getHeight() / other.getWidth() < 1
			&& abs(diff.y) > other.getHeight() / 2) {
			//cout << "Calculating..." << endl;
			cout << diff.y << endl;
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
		cout << "Verical Check" << endl;
		if (other.getHeight() / other.getWidth() > 1
				&& abs(diff.x) > other.getWidth() / 2) {
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

Collision Collider::getObjectCollisionData(const Collider& other) const {
	bool collided = this->intersects(other) && other.m_Owner->isActive();
	Vector2f diff(other.m_Owner->getPosition().x - this->m_Owner->getPosition().x, 
		other.m_Owner->getPosition().y - this->m_Owner->getPosition().y);
	CollisionDirection colDir = this->getRelativeDirection(other, diff);

	return std::make_tuple(collided, colDir, diff);
}

vector<CollisionDirection> Collider::getBoundaryCollisionData() const {
	vector<CollisionDirection> desire;

	if(this->getLeft() < 0) {
		desire.push_back(CollisionDirection::Left);
	}

	if(this->getTop() < 0) {
		desire.push_back(CollisionDirection::Up);
	}

	if(this->getLeft() + this->m_Width
		> SceneManager::getInstance()->getCurrentScene().getWidth()) {
		desire.push_back(CollisionDirection::Right);
	}

	if(this->getTop() + this->m_Height
		> SceneManager::getInstance()->getCurrentScene().getHeight()) {
		desire.push_back(CollisionDirection::Down);
	}

	return desire;
}

void Collider::repositionAfterObjectCollision(const Collider& other) {
	Collision col = this->getObjectCollisionData(other);

	if (std::get<0>(col)) {
		CollisionDirection colDir = std::get<1>(col);
		Vector2f colVector = std::get<2>(col);
		Vector2f ownerPos = this->m_Owner->getPosition(); 
		float xPos = ownerPos.x;
		float yPos = ownerPos.y;

		if (colDir == CollisionDirection::Down) {
			yPos -= this->getTop() + this->getHeight() - other.getTop();
		}
		else if (colDir == CollisionDirection::Right) {
			xPos -= abs(this->getLeft() + this->getWidth() - other.getLeft());
		}
		else if (colDir == CollisionDirection::Up) {
			yPos += other.getTop() + other.getHeight() - this->getTop();
		}
		else if (colDir == CollisionDirection::Left) {
			xPos += other.getLeft() + other.getWidth() - this->getLeft();
		}

		this->m_Owner->setPosition(Vector2f(xPos, yPos));
	}
}

void Collider::update(float dtAsSeconds) {
}

void Collider::destroy() const {
	//SimpleCollisionManager::getInstance()->erase(this->m_Id);
}
