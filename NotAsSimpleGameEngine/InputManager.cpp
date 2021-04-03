#include "InputManager.h"

InputManager* InputManager::instance = NULL;

InputManager::InputManager() {
	this->initializeKey(Button::Up, Keyboard::W);
	this->initializeKey(Button::Down, Keyboard::S);
	this->initializeKey(Button::Left, Keyboard::A);
	this->initializeKey(Button::Right, Keyboard::D);
}

void InputManager::initializeKey(Button key, Keyboard::Key value) {
	this->m_Keys[key] = value;
	this->m_Pressed[key] = false;
	this->m_Released[key] = false;
	this->m_Down[key] = false;
}

InputManager::~InputManager() {
	std::cout << "***InputManager:: Deleting InputManager..." << std::endl;
}

InputManager* InputManager::getInstance() {
	if (!instance) {
		instance = new InputManager();
	}

	return instance;
}

void InputManager::resetInstance() {
	if (instance) {
		delete(instance);
	}

	instance = NULL;
}

bool InputManager::isKeyPressed(Button key) {
	return this->m_Pressed[key];
}

bool InputManager::isKeyDown(Button key) {
	return this->m_Down[key];
}

bool InputManager::isKeyReleased(Button key) {
	return this->m_Released[key];
}

bool InputManager::checkPressed(Button b, Keyboard::Key key) {

	if (Keyboard::isKeyPressed(key) && !this->m_Pressed[b]) {
		//this->m_Pressed[b] = true;
		//cout << "InputManager: key '" << itr->first << "' has been pressed." << endl;
		return true;
	}
	else if (!Keyboard::isKeyPressed(key)) {
		//this->m_Pressed[b] = false;
	}

	return false;
}

void InputManager::update(float dtAsSeconds) {
	unordered_map<Button, Keyboard::Key>::iterator itr;
	for (itr = this->m_Keys.begin(); itr != this->m_Keys.end(); ++itr) {
		bool initPressed = this->m_Pressed[itr->first];

		this->m_Pressed[itr->first] = checkPressed(itr->first, itr->second);

		if (initPressed && !this->m_Pressed[itr->first]) {
			this->m_Released[itr->first] = true;
			//cout << "InputManager: key '" << itr->first << "' has been released." << endl;
		}
		else if (!initPressed && this->m_Pressed[itr->first]) {
			this->m_Down[itr->first] = true;
		}
		else {
			this->m_Released[itr->first] = false;
			this->m_Down[itr->first] = false;
		}
	}
}