#include "RectangleGraphic.h"
#include "GameObject.h"
#include "SceneManager.h"

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
	float xPos = this->getX() - this->m_Rectangle.getSize().x / 2;
	float yPos = this->getY() - this->m_Rectangle.getSize().y / 2;

	//yPos = SceneManager::getInstance()->getCurrentScene().getHeight() - yPos;

	this->m_Rectangle.setPosition(Vector2f(xPos, yPos));
}