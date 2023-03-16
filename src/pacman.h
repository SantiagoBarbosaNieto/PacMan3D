#pragma once

#include "utils.h"

class  Pacman {
public:
	Pacman();
    ~Pacman();

    void draw();
    void update(float deltaTime);
    void Collision(int type);

    float getRadius();
    Vec3 getPos();
    float getSpeed();
    Vec2 getDirection();
    bool getBlocked(int direction);
    Vec2 getBlockPos();

    void setRadius(float radius);
    void setPos(Vec3 pos);
    void setPos(float x, float y, float z);
    void setSpeed(float speed);
    void setDirection(Vec2 dir);
    void setBlocked(int direction, bool value);
    void paredCollision(Vec3 pos);


private:
    Vec3 m_Pos = {0.0f,0.0f,0.0f};
    Vec3 m_CollisionPoints[4];
    float m_Radius = 0.5;
    float m_Speed = 1.0f;
    float m_LastDeltaTime = 0;
    Vec2 m_DirectionV = {1,0};
    //Direction representa la dirección de movimiento en un plano 2D: 0: x+ 1:x- 2:z+ 3:z-
    int m_Direction = 0; 

    float animBaseScale = 1;
    bool animStateRedu = true;
    float animSpeed = 4;
    //Blocked representa si esta bloqueado en movimiento para cada una de las 4 direcciones
    bool m_Blocked[4] = {false,false,false,false};




};