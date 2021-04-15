#ifndef PONGBALL_H
#define PONGBALL_H
#pragma once
#include "Entity.h"

class RectangleGraphic;

class PongBall final :
	public Entity {
private:
    Vector2f m_InitPosition;
    float m_Speed;
    Vector2f m_TravelDirection;
    RectangleGraphic* m_Graphic;
    string m_BounceSoundFile;
    Sound m_BounceSound;

    PongBall(const PongBall& other) = delete;
    PongBall& operator=(const PongBall& rhs) = delete;

    void changeDirectionAfterObjectCollision(float dtAsSeconds);
    void handleBoundaryCollision(vector<CollisionDirection> directionList);

protected:
    void update(float dtAsSeconds);

public:
    PongBall();
    ~PongBall();

    void init(float x, float y) final;
};

#endif

