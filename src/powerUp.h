#pragma once
#include <stdio.h>
#include <vector>

#include "utils.h"


class PowerUp {

public:
    PowerUp();
    ~PowerUp();
    void setPos(Vec3 pos);
    void setPos(float x, float y, float z);
    void updatePos(Vec3 pos);
    void setActive(bool active);

    void draw();

    bool collide(Vec3 pos, float thresh);
    bool isActive();

    Vec3 getPos();
    Vec3 getScale();

    float getRadius();
private:
    bool active = true;
    float radius = 0.2;
    Vec3 m_Pos = {0.0f,0.0f,0.0f};
    Vec3 m_Scale = {1.0f,1.0f,1.0f};
};