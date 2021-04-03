#ifndef TESTSCENE_H
#define TESTSCENE_H
#pragma once
#include "Scene.h"

class BasicPlayer;
class Box;
class Mover;

class TestScene : public Scene
{

private:
	float m_Seconds;
	BasicPlayer* testPlayer;
	Box* testBox;
	Mover* testMover;

public:
	TestScene();

protected:
	void enter(float dtAsSeconds);
	void update(float dtAsSeconds);
	void exit(float dtAsSeconds);
};

#endif

