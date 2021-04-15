#ifndef PONGPADDLE_H
#define PONGPADDLE_H
#include "Entity.h"

class RectangleGraphic;

class PongPaddle final :
	public Entity {
private:
	float m_Speed;
	RectangleGraphic* m_Graphic;

	PongPaddle(const PongPaddle& other) = delete;
	PongPaddle& operator=(const PongPaddle& rhs) = delete;

	Vector2f inputToVector();

protected:
	void update(float dtAsSeconds);

public:
	PongPaddle();
	~PongPaddle();

	void init(float x, float y);

};

#endif

