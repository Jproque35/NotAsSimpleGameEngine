#pragma once
#include "Entity.h"

class RectangleGraphic;

class Box 
	: public Entity {

private:
	RectangleGraphic* m_Graphic;

	Box() = delete;
	Box(const Box& other) = delete;
	Box& operator=(const Box& rhs) = delete;

protected:
	void update(float dtAsSeconds);

public:
	Box(float x, float y);
	~Box();
};

