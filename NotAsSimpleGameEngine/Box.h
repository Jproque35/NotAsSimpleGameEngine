#pragma once
#include "Entity.h"

class RectangleGraphic;

class Box 
	: public Entity {

private:
	RectangleGraphic* m_Graphic;

	Box(const Box& other) = delete;
	Box& operator=(const Box& rhs) = delete;

protected:
	void update(float dtAsSeconds);

public:
	Box();
	~Box();

	void init(float x, float y) final;
};

