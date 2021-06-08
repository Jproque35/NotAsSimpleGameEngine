#include "PongBlock.h"
#include "RectangleGraphic.h"
#include "PongBlockManager.h"
#include "CollisionManager.h"

PongBlock::PongBlock() {
	this->m_Tag = GameObjectTag::Obstacle;

	Vector2f shape(80.0f, 32.0f);
	this->m_Rectangle = new RectangleGraphic(*this, shape, Color::Blue);
	//this->m_Collider = new RectangleCollider(*this, shape, true, true);

	this->m_Collider = CollisionManager::getInstance()->createRectangleCollider(*this, shape, true, true);

	this->addComponent(*this->m_Rectangle);
	this->addComponent(*this->m_Collider);

	cout << "PongBlock: Block with id " << this->getId() << " created." << endl;
}

PongBlock::~PongBlock() {}

void PongBlock::init(float x, float y) {
	GameObject::init(x, y);
	cout << "PongBlock: Block initialized at position " << this->getPosition().x << ", " << this->getPosition().y << endl;
}

void PongBlock::setNext(PongBlock* block) {
	this->m_Next = block;
}

PongBlock& PongBlock::getNext() {
	return *this->m_Next;
}

void PongBlock::update(float dtAsSeconds) {
	vector<Collider*> colList = this->m_Collider->getCollisionList();

	for (int i = 0; i < colList.size(); ++i) {
		cout << "Collision detected at time " << dtAsSeconds << endl;
		if (colList[i]->getOwner().m_Tag == GameObjectTag::Enemy
			&& this->isActive()) {
			this->destroy();
		}
	}

}

void PongBlock::destroy() {
	cout << "PongBlock: Destroyed object " << this->getId() << endl;
	PongBlockManager::getInstance()->addFreeBlock(*this);
}