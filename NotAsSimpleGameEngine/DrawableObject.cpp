#include "DrawableObject.h"
#include "DrawableManager.h"

int DrawableObject::m_CurrFreeId = 0;

DrawableObject::DrawableObject(GameObject& owner)
	: GameObjectComponent(owner) {
	this->m_Id = m_CurrFreeId++;
	cout << "DrawableObject: Id set to " << this->m_Id << endl;
	DrawableManager::getInstance()->add(*this);
}

DrawableObject::~DrawableObject() {
	cout << "Destroying DrawableObject..." << endl;
}

void DrawableObject::destroy() const {

}