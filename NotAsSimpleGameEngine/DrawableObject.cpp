#include "DrawableObject.h"
#include "DrawableManager.h"

DrawableObject::DrawableObject(GameObject& owner)
	: GameObjectComponent(owner) {
	//this->m_Id = DrawableManager::getInstance()->add(*this);
	DrawableManager::getInstance()->add(*this);
}

DrawableObject::~DrawableObject() {
	cout << "Destroying DrawableObject..." << endl;
}

void DrawableObject::destroy() const {

}