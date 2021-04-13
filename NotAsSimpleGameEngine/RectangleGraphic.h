#ifndef RECTANGLEGRAPHIC_H
#define RECTANGLEGRAPHIC_H
#pragma once
#include "DrawableObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class RectangleGraphic final :
    public DrawableObject {

private:
    RectangleShape m_Rectangle;

    RectangleGraphic() = delete;
    RectangleGraphic(const RectangleGraphic& obj) = delete;
    RectangleGraphic& operator=(const RectangleGraphic& rhs) = delete;

public:
    RectangleGraphic(GameObject& owner, Vector2f size, Color color);
    ~RectangleGraphic();

    Drawable& getGraphic();
    void update(float dtAsSeconds);
};

#endif

