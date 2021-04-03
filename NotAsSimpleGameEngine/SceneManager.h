#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#pragma once
#include <vector>
#include "Scene.h"

using namespace std;

class SceneManager {
private:
	static SceneManager* instance;
	vector<Scene*> m_Scenes;
	int m_CurrScene;
	SceneManager();
	~SceneManager();

public:
	static SceneManager* getInstance();
	static void resetInstance();
	void add(Scene& obj);
	void setCurrentScene(int i);
	Scene& getCurrentScene() const;
	bool sceneExists(int i) const;
};

#endif
