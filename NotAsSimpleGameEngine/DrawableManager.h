#ifndef DRAWABLEMANAGER_H
#define DRAWABLEMANAGER_H
#pragma once
#include "DrawableObject.h"
#include "Container.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace sf;
using namespace std;

class DrawableManager final {
private:
	static DrawableManager* instance;
	Container<DrawableObject>* m_Storage;
	vector<int> m_Ids;

	DrawableManager();
	~DrawableManager();
	DrawableManager(const DrawableManager& obj) = delete;
	DrawableManager& operator=(const DrawableManager & rhs) = delete;

public:
	static DrawableManager* getInstance();
	static void resetInstance();

	void add(DrawableObject& obj);
	DrawableObject& get(int id) const;
	vector<int> getIdList() const;
	int size() const;
	void cleanUp();
};

#endif

