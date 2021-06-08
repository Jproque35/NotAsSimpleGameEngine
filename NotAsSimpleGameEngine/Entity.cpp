#include "Entity.h"
#include "SimpleCollisionManager.h"

Entity::Entity() 
	: GameObject(),
	m_CurrDir(Direction::Up),
	m_Type(EntityType::Generic)
	{}

Entity::~Entity() {
	cout << this << ": Deleting Entity..." << endl;
}

void Entity::Move(const Vector2f& direction) {
	//this->m_Position.x += direction.x;
	//this->m_Position.y += direction.y;
	this->setPosition( Vector2f(this->getPosition().x + direction.x, this->getPosition().y + direction.y) );
}