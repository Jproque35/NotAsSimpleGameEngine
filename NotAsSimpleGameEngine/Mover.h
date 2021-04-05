#pragma once
#include "Entity.h"

class RectangleGraphic;

class Mover :
    public Entity {
private:
    float m_Speed;
    Vector2f m_TravelDirection;
    RectangleGraphic* m_Graphic;

    void changeDirectionAfterObjectCollision(float dtAsSeconds);
    void changeDirectionAfterBoundaryCollision(vector<CollisionDirection> directionList);

protected:
    void update(float dtAsSeconds);

public:
    Mover(float x, float y);
    ~Mover();

};

