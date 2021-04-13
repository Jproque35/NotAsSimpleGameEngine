#ifndef SCENE_H
#define SCENE_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum class SceneStage {
	Enter,
	Update,
	Exit
};

class Scene {

private:
	float width;
	float height;

public:
	SceneStage m_Stage;

	Scene(float x, float y);
	Scene(const Scene& obj) = delete;
	Scene& operator=(const Scene& obj) = delete;
	virtual ~Scene();

	float getWidth() const;
	float getHeight() const;
	void process(float dtAsSeconds);
	void setStage(SceneStage state);
	SceneStage getStage() const;

protected:
	virtual void enter(float dtAsSeconds);
	virtual void update(float dtAsSeconds);
	virtual void exit(float dtAsSeconds);

};

#endif