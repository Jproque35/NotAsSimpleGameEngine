#include "Box.h"
#include "DrawableManager.h"
#include "RectangleGraphic.h"

Box::Box(float x, float y)
	: Entity(x, y) {
	Vector2f rectSize(50.0f, 50.0f);
	this->m_Graphic = new RectangleGraphic(*this, rectSize, Color::Blue);
	this->m_Collider = new Collider(*this, rectSize, true);

	this->addComponent(*this->m_Graphic);
	this->addComponent(*this->m_Collider);
}

Box::~Box() {
	std::cout << "Destroying Box..." << std::endl;
}

void Box::update(float dtAsSeconds) {
	if (this->m_Collider->getCollisionList().size() > 0) {
		cout << "Box: Collision Ocurring..." << endl;
	}
}