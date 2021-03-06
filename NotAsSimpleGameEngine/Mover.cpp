#include "Mover.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"
#include "SoundFileManager.h"
#include "CollisionManager.h"

Mover::Mover()
	: Entity(),
	m_Speed(100.0f),
	m_TravelDirection(0.0f, 0.0f),
	m_BounceSoundFile("VUX-Bite.wav"){

	SoundFileManager::getInstance()->loadFile(this->m_BounceSoundFile);
	this->m_BounceSound.setBuffer(SoundFileManager::getInstance()->get(this->m_BounceSoundFile));

	Vector2f rectSize(32.0f, 32.0f);
	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Red);
	this->m_Collider = CollisionManager::getInstance()->createRectangleCollider(*this, rectSize, true, false);
	this->m_TravelDirection.x = this->m_Speed;
	this->m_TravelDirection.y = this->m_Speed;

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

Mover::~Mover() {
	std::cout << "Destroying Mover..." << std::endl;
}

void Mover::init(float x, float y) {
	GameObject::init(x, y);
	cout << "Mover: Initialized at position " << x << ", " << y << endl;
}

void Mover::changeDirectionAfterObjectCollision(float dtAsSeconds) {
	vector<Collider*> collisionList = this->m_Collider->getCollisionList();

	//cout << "Mover: Collision List has size " << collisionList.size() << endl;

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

void Mover::changeDirectionAfterBoundaryCollision(vector<CollisionDirection> directionList) {
	if (directionList.size() > 0) {

		for (int i = 0; i < directionList.size(); ++i) {
			CollisionDirection colDir = directionList[i];

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
	//this->Move(this->m_TravelDirection.x * dtAsSeconds, this->m_TravelDirection.y * dtAsSeconds);
	this->Move(this->m_TravelDirection * dtAsSeconds);
	this->changeDirectionAfterObjectCollision(dtAsSeconds);

	vector<CollisionDirection> screenCollisions = this->m_Collider->getBoundaryCollisionData();
	if (screenCollisions.size() > 0) {
		this->m_BounceSound.play();
		this->changeDirectionAfterBoundaryCollision(screenCollisions);
	}
}