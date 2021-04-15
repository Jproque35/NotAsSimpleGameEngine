#ifndef PONGSCENE_H
#define PONGSCENE_H
#pragma once
#include "Scene.h"

class PongBlockManager;
class PongBall;
class PongPaddle;

enum class PongType {
	Paddle,
	Block,
	Ball
};

class PongScene final
	: public Scene {

private:
	PongScene(const PongScene& other) = delete;
	PongScene& operator=(const PongScene& rhs) = delete;

protected:
	void enter(float dtAsSeconds);
	void update(float dtAsSeconds);
	void exit(float dtAsSeconds);

public:
	PongScene();
	~PongScene();

};

#endif

