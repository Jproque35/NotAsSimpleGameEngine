#include "Entity.h"
#include "SimpleCollisionManager.h"

Entity::Entity(float x, float y) 
	: GameObject(x, y),
	m_CurrDir(Direction::Up),
	m_Type(EntityType::Generic) {
}

Entity::~Entity() {
	cout << this << ": Deleting Entity..." << endl;
}

void Entity::Move(float x, float y) {
	this->m_Position.x += x;
	this->m_Position.y += y;
}