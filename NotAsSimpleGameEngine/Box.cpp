#include "Box.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"

Box::Box()
	: Entity() {
	Vector2f rectSize(32.0f, 32.0f);
	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Blue);
	this->m_Collider = new Collider(*this, rectSize, true);

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

Box::~Box() {
	std::cout << "Destroying Box..." << std::endl;
}

void Box::init(float x, float y) {
	GameObject::init(x, y);
	cout << "Box: Initialized at position " << x << ", " << y << endl;
}

void Box::update(float dtAsSeconds) {
	if (this->m_Collider->getCollisionList().size() > 0) {
		cout << "Box: Collision Ocurring..." << endl;
	}
}