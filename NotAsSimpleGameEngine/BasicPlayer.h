#ifndef BASICPLAYER_H
#define BASICPLAYER_H
#pragma once
#include "Entity.h"

class RectangleGraphic;

class BasicPlayer :
    public Entity {
private:
    float m_Speed;
    RectangleGraphic* m_Graphic;

    BasicPlayer(const BasicPlayer& obj) = delete;
    BasicPlayer& operator=(const BasicPlayer& rhs) = delete;

    Vector2f inputToVector();

protected:
    void update(float dtAsSeconds) final;

public:
    BasicPlayer();
    ~BasicPlayer();

    void init(float x, float y) final;
};

#endif

