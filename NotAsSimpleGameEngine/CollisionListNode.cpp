#include "CollisionListNode.h"

CollisionListNode::CollisionListNode(Collider& owner, CollisionListNodeType type) :
	m_Owner(&owner),
	m_Type(type),
	m_Value(0.0f),
	m_Next(NULL),
	m_Prev(NULL) {}

CollisionListNode::~CollisionListNode() {
	cout << "CollisionListNode: Deleting node..." << endl;
}

Collider& CollisionListNode::getOwner() {
	return *this->m_Owner;
}

CollisionListNodeType CollisionListNode::getType() const {
	return this->m_Type;
}

void CollisionListNode::setValue(float value) {
	this->m_Value = value;
}

float CollisionListNode::getValue() const {
	return this->m_Value;
}

void CollisionListNode::setNext(CollisionListNode* next) {
	this->m_Next = next;
}

CollisionListNode* CollisionListNode::getNext() {
	return this->m_Next;
}

void CollisionListNode::setPrev(CollisionListNode* prev) {
	this->m_Prev = prev;
}

CollisionListNode* CollisionListNode::getPrev() {
	return this->m_Prev;
}