#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(GameObject& obj) {
	this->m_Owner = &obj;
}

GameObjectComponent::~GameObjectComponent() {
	cout << "Destroying GameObjectComponent..." << endl;
}

int GameObjectComponent::getId() const {
	return this->m_Id;
}

GameObject& GameObjectComponent::getOwner() const {
	return *this->m_Owner;
}