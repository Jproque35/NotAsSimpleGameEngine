#include "RectangleGraphic.h"
#include "GameObject.h"

RectangleGraphic::RectangleGraphic(GameObject& owner, Vector2f size, Color color)
	: DrawableObject(owner),
	m_Rectangle(size) {
	this->m_Rectangle.setFillColor(color);
}

RectangleGraphic::~RectangleGraphic() {
	cout << "Deleting Rectangle Graphic..." << endl;
}

Drawable& RectangleGraphic::getGraphic() {
	return this->m_Rectangle;
}

void RectangleGraphic::update(float dtAsSeconds) {
	this->m_Rectangle.setPosition(this->m_Owner->getPosition());
}