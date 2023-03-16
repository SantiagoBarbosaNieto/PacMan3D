#pragma once
#include <stdio.h>
#include <vector>

#include "utils.h"


class Ghost {

public:
    Ghost();
    ~Ghost();
    void setPos(Vec3 pos);
    void setPos(float x, float y, float z);
    void setInitialPos(Vec3 pos);
    void updatePos(Vec3 pos);
    void setActive(bool active);

    void draw();
    void update(float deltaTime);

    bool collide(Vec3 pos, float thresh);
    bool isActive();

    Vec3 getPos();
    Vec3 getIniciatPos();
    Vec3 getScale();
    

    int getId();
    void setId(int id);
    float getRadius();

    void paredCollision(Vec3 pos);
private:
    int id; //Util para tener ghosts de diferentes colores
    bool blink = false;
    bool active = true;
    Vec3 m_initialPos = {0.0f,0.0f,0.0f};

    Vec3 m_Pos = {0.0f,0.0f,0.0f};
    Vec3 m_Scale = {1.0f,1.0f,1.0f};
    float radius = 0.4;
    float m_Speed = 3.5;
    float lastDeltaTime = 0;

    Vec2 m_Direction = {0,1};
    Vec2 m_LastDir = {0,1};
};