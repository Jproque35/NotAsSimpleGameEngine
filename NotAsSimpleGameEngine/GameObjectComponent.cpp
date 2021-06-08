#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(GameObject& obj, int id) :
	m_Owner(&obj),
	m_Id(id) {}

GameObjectComponent::~GameObjectComponent() {
	cout << "Destroying GameObjectComponent..." << endl;
}

const float GameObjectComponent::getX() const {
	return this->m_Owner->getPosition().x;
}

const float GameObjectComponent::getY() const {
	return this->m_Owner->getPosition().y;
}