#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(GameObject& obj) :
	m_Owner(&obj) {}

GameObjectComponent::~GameObjectComponent() {
	cout << "Destroying GameObjectComponent..." << endl;
}

float GameObjectComponent::getX() const {
	return this->m_Owner->getPosition().x;
}

float GameObjectComponent::getY() const {
	return this->m_Owner->getPosition().y;
}