#include "GameObjectComponent.h"
#include "GameObject.h"

int GameObjectComponent::m_CurrId = 0;

GameObjectComponent::GameObjectComponent(GameObject& obj) {
	this->m_Owner = &obj;
	this->m_Id = m_CurrId++;
}

GameObjectComponent::~GameObjectComponent() {
	cout << "Destroying GameObjectComponent..." << endl;
}

float GameObjectComponent::getX() const {
	return this->m_Owner->getPosition().x;
}

float GameObjectComponent::getY() const {
	return this->m_Owner->getPosition().y;
}

int GameObjectComponent::getId() const {
	return this->m_Id;
}

GameObject& GameObjectComponent::getOwner() const {
	return *this->m_Owner;
}