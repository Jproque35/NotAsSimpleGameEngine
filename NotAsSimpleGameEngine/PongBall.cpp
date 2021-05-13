#include "PongBall.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"
#include "SoundFileManager.h"
#include "PongGameManager.h"

PongBall::PongBall()
	: Entity(),
	m_Speed(300.0f),
	m_TravelDirection(0.0f, 0.0f),
	m_BounceSoundFile("boom1.wav"),
	m_InitPosition(0.0f, 0.0f) {

	this->m_Tag = GameObjectTag::Enemy;

	SoundFileManager::getInstance()->loadFile(this->m_BounceSoundFile);
	this->m_BounceSound.setBuffer(SoundFileManager::getInstance()->get(this->m_BounceSoundFile));

	Vector2f rectSize(24.0f, 24.0f);
	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Red);
	this->m_Collider = new RectangleCollider(*this, rectSize, true, false);
	this->m_TravelDirection.x = this->m_Speed;
	this->m_TravelDirection.y = this->m_Speed;

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

PongBall::~PongBall() {
	std::cout << "Destroying Mover..." << std::endl;
}

void PongBall::init(float x, float y) {
	GameObject::init(x, y);
	this->m_InitPosition = Vector2f(x, y);
	this->m_TravelDirection.x = -this->m_Speed;
	this->m_TravelDirection.y = -this->m_Speed;

	int randomChance = rand() % 2;

	if (randomChance == 0) {
		this->m_TravelDirection.x *= -1;
	}

	cout << "Mover: Initialized at position " << x << ", " << y << endl;
}

void PongBall::changeDirectionAfterObjectCollision(float dtAsSeconds) {
	vector<RectangleCollider*> collisionList = this->m_Collider->getCollisionList();

	if (collisionList.size() > 0) {

		for (int i = 0; i < collisionList.size(); ++i) {
			Collision currCollision = this->m_Collider->getObjectCollisionData(*collisionList[i]);

			CollisionDirection colDir = std::get<1>(currCollision);

			this->m_BounceSound.play();
			if (colDir == CollisionDirection::Up && this->m_TravelDirection.y < 0.0f) {
				this->m_TravelDirection.y = -1 * this->m_TravelDirection.y;
				//cout << "Ball: Up Collision" << endl;
			}
			else if (colDir == CollisionDirection::Down && this->m_TravelDirection.y > 0.0f) {
				this->m_TravelDirection.y = -1 * this->m_TravelDirection.y;
				//cout << "Ball: Down Collision" << endl;
			}
			else if (colDir == CollisionDirection::Left && this->m_TravelDirection.x < 0.0f) {
				this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
				//cout << "Ball: Left Collision" << endl;
			}
			else if (colDir == CollisionDirection::Right && this->m_TravelDirection.x > 0.0f) {
				this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
				//cout << "Ball: Right Collision" << endl;
			}
		}

	}

}

void PongBall::handleBoundaryCollision(vector<CollisionDirection> directionList) {
	for (int i = 0; i < directionList.size(); ++i) {
		CollisionDirection colDir = directionList[i];

		if (colDir == CollisionDirection::Up && this->m_TravelDirection.y < 0.0f) {
			this->m_TravelDirection.y = -1 * this->m_TravelDirection.y;
		}
		else if (colDir == CollisionDirection::Left && this->m_TravelDirection.x < 0.0f) {
			this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
		}
		else if (colDir == CollisionDirection::Right && this->m_TravelDirection.x > 0.0f) {
			this->m_TravelDirection.x = -1 * this->m_TravelDirection.x;
		}
		else if (colDir == CollisionDirection::Down && this->m_TravelDirection.y > 0.0f) {
			//this->init(this->m_InitPosition.x, this->m_InitPosition.y);
			PongGameManager::getInstance()->restStartCount();
			PongGameManager::getInstance()->resetPaddleAndBall();
			PongGameManager::getInstance()->decrementLives();
		}
	}
}

void PongBall::update(float dtAsSeconds) {

	if (PongGameManager::getInstance()->getStartCount() <= 0.0f) {
		this->Move(this->m_TravelDirection * dtAsSeconds);
		this->changeDirectionAfterObjectCollision(dtAsSeconds);

		vector<CollisionDirection> screenCollisions = this->m_Collider->getBoundaryCollisionData();
		if (screenCollisions.size() > 0) {
			this->m_BounceSound.play();
			this->handleBoundaryCollision(screenCollisions);
		}
	}
}