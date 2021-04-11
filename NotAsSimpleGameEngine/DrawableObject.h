#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H
#pragma once
#include "GameObjectComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject;

class DrawableObject :
    public GameObjectComponent {

private:
    static int m_CurrFreeId;

    DrawableObject() = delete;
    DrawableObject(const DrawableObject& obj) = delete; 
    DrawableObject& operator=(const DrawableObject& rhs) = delete;

public:
    DrawableObject(GameObject& owner);
    virtual ~DrawableObject();

    virtual Drawable& getGraphic() = 0;
    void destroy() const;
};

#endif
