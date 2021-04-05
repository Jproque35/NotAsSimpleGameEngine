#ifndef ENGINE_H
#define ENGINE_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class EngineState {
	Enter,
	Update,
	Exit
};

class Engine {
private:
	static Engine* instance;
	RenderWindow m_Window;

	Engine();
	~Engine();

	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	Vector2f resolution;
	static Engine* getInstance();
	static void resetInstance();
	void start();
};

#endif