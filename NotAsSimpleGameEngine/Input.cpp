#include "Engine.h"
#include "InputManager.h"

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		this->m_Window.close();
	}

	InputManager* im = InputManager::getInstance();

	im->update(0);

	/*
	if (im->isKeyDown(Button::Up)) {
		cout << "Engine Input: Key 'up' pressed" << endl;
	}

	if (im->isKeyPressed(Button::Up)) {
		cout << "Engine Input: Key 'up' active" << endl;
	}

	if (im->isKeyReleased(Button::Up)) {
		cout << "Engine Input: Key 'up' released" << endl;
	}*/
}