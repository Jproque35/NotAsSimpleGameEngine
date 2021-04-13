#include "PongBlock.h"
#include "Collider.h"
#include "RectangleGraphic.h"
#include "PongBlockManager.h"

PongBlock::PongBlock() {
	Vector2f shape(80.0f, 32.0f);
	this->m_Rectangle = new RectangleGraphic(*this, shape, Color::Blue);
	this->m_Collider = new Collider(*this, shape, true, true);

	this->addComponent(*this->m_Rectangle);
	this->addComponent(*this->m_Collider);
}

PongBlock::~PongBlock() {}

void PongBlock::init(float x, float y) {
	GameObject::init(x, y);
}

void PongBlock::setNext(PongBlock* block) {
	this->m_Next = block;
}

PongBlock& PongBlock::getNext() {
	return *this->m_Next;
}

void PongBlock::update(float dtAsSeconds) {

}

void PongBlock::destroy() {
	PongBlockManager::getInstance()->addFreeBlock(*this);
}