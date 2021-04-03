#ifndef DRAWABLEMANAGER_H
#define DRAWABLEMANAGER_H
#pragma once
#include "DrawableObject.h"
#include "CompactVector.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class DrawableManager {
private:
	static DrawableManager* instance;
	CompactVector<DrawableObject>* m_Storage;
	
	DrawableManager();
	~DrawableManager();
	DrawableManager(const DrawableManager& obj) = delete;
	DrawableManager& operator=(const DrawableManager & rhs) = delete;

public:
	static DrawableManager* getInstance();
	static void resetInstance();

	int add(DrawableObject& obj);
	DrawableObject& get(int id) inline const;
	void erase(int id);
	int size() inline const;
	void cleanUp();
};

#endif

