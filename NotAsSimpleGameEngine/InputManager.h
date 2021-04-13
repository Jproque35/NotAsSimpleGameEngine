#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum class Button {
	Up,
	Down,
	Left,
	Right,
	Fire
};

class InputManager final {
private:
	static InputManager* instance;
	unordered_map<Button, Keyboard::Key> m_Keys;
	unordered_map<Button, bool> m_Pressed;
	unordered_map<Button, bool> m_Released;
	unordered_map<Button, bool> m_Down;
	
	InputManager();
	InputManager(const InputManager& obj) = delete;
	InputManager& operator=(const InputManager& rhs) const = delete;
	~InputManager();

	bool checkPressed(Button b, Keyboard::Key key);
	void initializeKey(Button key, Keyboard::Key value);

public:
	static InputManager* getInstance();
	static void resetInstance();
	bool isKeyPressed(Button key);
	bool isKeyDown(Button key);
	bool isKeyReleased(Button key);
	void update(float dtAsSeconds);
};

#endif

