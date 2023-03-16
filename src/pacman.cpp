#include "pacman.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

Pacman::Pacman() {
		this -> m_Radius = 0.4;
        this -> m_Pos = {0.99, 0, 0.99};
		this -> m_Speed = 3; //(bloques por segundo)
        this -> m_DirectionV = {0,1};
        this -> m_Blocked[0] = false;
        this -> m_Blocked[1] = false;
        this -> m_Blocked[2] = false;
        this -> m_Blocked[3] = false;
	}

Pacman::~Pacman(){}

void Pacman::draw()
{
    glPushMatrix();
    float yellow[4] = {1, 1, 0, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
    float Specular[4] = {1, 1, 1, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80); 
    float emit[4] = {0.5,0.5,0,1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
	glTranslatef(m_Pos.x,m_Pos.y,m_Pos.z);

    if(m_DirectionV.x == 1 && m_DirectionV.y == 0)
    {
        glRotatef(90, 0,1,0);
    }
    else if(m_DirectionV.x == 0 && m_DirectionV.y == -1)
    {
        glRotatef(180, 0,1,0);
    }
    else if(m_DirectionV.x == -1 && m_DirectionV.y == 0)
    {
        glRotatef(-90, 0,1,0);
    }
    glutSolidSphere(m_Radius, 10,10);
    float black[4] = {0, 0, 0, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100); 
    glTranslatef(0,-m_Radius,m_Radius);
    glRotatef(180, 0,1,0);
    if(animBaseScale > 0)
        glutSolidCone((m_Radius+0.1)*animBaseScale/2, m_Radius, 10,10);
    glPopMatrix();
    glutPostRedisplay();
}

void Pacman::update(float deltaTime)
{
    m_LastDeltaTime = deltaTime;
    this->m_Pos.x += this->m_DirectionV.x * m_Speed*deltaTime;
    this->m_Pos.z += this->m_DirectionV.y * m_Speed*deltaTime;
    
    //Animation
    if(animStateRedu)
    {
        animBaseScale -= animSpeed*deltaTime;
        if(animBaseScale <= 0)
        {
            animBaseScale = 0;
            animStateRedu = false;
        }
    }
    else
    {
        animBaseScale += animSpeed*deltaTime;
        if(animBaseScale >= 1)
        {
            animBaseScale = 1;
            animStateRedu = true;
        }
    }
}


void Pacman::paredCollision(Vec3 pos)
{
    
}


float Pacman::getRadius()
{
    return this->m_Radius;
}

Vec3 Pacman::getPos()
{
    return this->m_Pos;
}

float Pacman::getSpeed()
{
    return this->m_Speed;
}


Vec2 Pacman::getDirection()
{
    return this->m_DirectionV;
}

bool Pacman::getBlocked(int direction)
{
    return this->m_Blocked[direction];
}

Vec2 Pacman::getBlockPos()
{
    if(((int)m_DirectionV.x == 1 && (int)m_DirectionV.y == 0 )||((int)m_DirectionV.x  == 0 && (int)m_DirectionV.y == 1 ) )
    {
        return{ floor(m_Pos.x+0.05f),floor(m_Pos.z+0.05f)};
    }
    return { ceil(m_Pos.x),ceil(m_Pos.z)}; //dont question it :,v sirve
}

void Pacman::setRadius(float radius)
{
    this->m_Radius = radius;
}

void Pacman::setPos(Vec3 pos)
{
    this->m_Pos = pos;
}

void Pacman::setPos(float x, float y, float z)
{
    this->m_Pos = {x,y,z};
}

void Pacman::setSpeed(float speed)
{
    this->m_Speed = speed;
}

void Pacman::setDirection(Vec2 dir)
{
    this->m_DirectionV = dir;
}

void Pacman::setBlocked(int direction, bool value)
{
    this->m_Blocked[direction] = value;
}    
