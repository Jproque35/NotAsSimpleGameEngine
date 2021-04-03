#include "Scene.h"
#include <iostream>

Scene::Scene(float x, float y)
	: width(x),
	height(y) {
	this->m_Stage = SceneStage::Enter;
}

Scene::~Scene() {
	std::cout << "Destroying Scene..." << std::endl;
}

float Scene::getWidth() const {
	return this->width;
}

float Scene::getHeight() const {
	return this->height;
}

void Scene::enter(float dtAsSeconds) {
	this->m_Stage = SceneStage::Update;
	std::cout << "Entering Scene" << std::endl;
}

void Scene::update(float dtAsSeconds) {
	this->m_Stage = SceneStage::Update;
}

void Scene::exit(float dtAsSeconds) {
	this->m_Stage = SceneStage::Exit;
	std::cout << "Exiting Scene" << std::endl;
}

void Scene::process(float dtAsSeconds) {
	if (this->m_Stage == SceneStage::Enter) {
		this->enter(dtAsSeconds);
	}
	else if (this->m_Stage == SceneStage::Update) {
		this->update(dtAsSeconds);
	}
	else if (this->m_Stage == SceneStage::Exit) {
		this->exit(dtAsSeconds);
	}
}

void Scene::setStage(SceneStage state) {
	this->m_Stage = state;
}

SceneStage Scene::getStage() const {
	return this->m_Stage;
}

