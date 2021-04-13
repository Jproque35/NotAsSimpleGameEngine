#ifndef PONGBLOCK_H
#define PONGBLOCK_H
#pragma once
#include "Entity.h"

class Collider;
class RectangleGraphic;

class PongBlock final :
    public Entity {
private:
    Collider* m_Collider;
    RectangleGraphic* m_Rectangle;
    PongBlock* m_Next;

    PongBlock(const PongBlock& other) = delete;
    PongBlock& operator=(const PongBlock& rhs) = delete;
    void destroy();

protected:
    void update(float dtAsSeconds) final;

public:
    PongBlock();
    ~PongBlock();

    void setNext(PongBlock* block);
    PongBlock& getNext();
    void init(float x, float y) final;
};

#endif

