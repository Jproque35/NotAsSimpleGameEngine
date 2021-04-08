#include "GameObject.h"
#include "GameObjectComponent.h"
#include "GameObjectManager.h"

int GameObject::m_CurrId = 0;

GameObject::GameObject() :
	m_Active(false),
	m_Position(0.0f, 0.0f),
	m_Id( m_CurrId++ ) {
	std::cout << "GameObject created at position " << this->m_Position.x << " " << this->m_Position.y << std::endl;
	this->input = InputManager::getInstance();
	GameObjectManager::getInstance()->add(*this);
}

GameObject::~GameObject() {
	std::cout << "GameObject: Destroying GameObject..." << std::endl;

	for (int i = 0; i < this->m_Components.size(); ++i) {
		GameObjectComponent* currComponent = this->m_Components[i];

		if (currComponent) {
			//currComponent->destroy();
		}

		currComponent = NULL;
	}
}

void GameObject::init(float x, float y) {
	this->m_Position.x = x;
	this->m_Position.y = y;
	this->m_Active = true;
}

int GameObject::getId() const {
	return this->m_Id;
}

bool GameObject::isActive() const {
	return this->m_Active;
}

void GameObject::setActive(bool isActive) {
	this->m_Active = isActive;
}

const Vector2f& GameObject::getPosition()  const {
	return this->m_Position;
}

void GameObject::setPosition(float x, float y) {
	this->m_Position.x = x;
	this->m_Position.y = y;
}

void GameObject::addComponent(GameObjectComponent& component) {
	this->m_Components.push_back(&component);
}

void GameObject::process(float dtAsSeconds) {
	this->update(dtAsSeconds);

	for (int i = 0; i < this->m_Components.size(); ++i) {
		this->m_Components[i]->update(dtAsSeconds);
	}
}
