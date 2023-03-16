#include "ghost.h"
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

Ghost::Ghost() {
    /* initialize random seed: */
    srand (time(0));
}

Ghost::~Ghost() {

}

void Ghost::setActive(bool active) {
    this->active = active;
}

bool Ghost::isActive() {
    return this->active;
}

void Ghost::draw() {
    
    float AmbDiff[5][4] = {       // 6 ambient diffuse colors of the spheres
            {0.5, 0.0, 0.0, 1.0},         // Red
            {0.0, 0.5, 0.0, 1.0},         // Green
            {0.0, 0.5, 0.5, 1.0},         // Cyan
            {0.5, 0.0, 0.5, 1.0},         // Magenta
            {0.0, 0.0, 0.8, 1.0}          // Blue
    };
    glPushMatrix();
    glTranslatef(this->m_Pos.x, this->m_Pos.y, this->m_Pos.z);
    float Specular[4] = {1, 1, 1, 1.0};

    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80); 
    float emit[4] = {0,0,0,1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
    if(this->isActive()) {
        glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[this->id%4]);
    }
    else {
        glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[4]);
    }
    if(m_Direction.x == 0 && m_Direction.y == 1)
    {
        glRotatef(-90, 0,1,0);
    }
    else if(m_Direction.x == 0 && m_Direction.y == -1)
    {
        glRotatef(90, 0,1,0);
    }
    else if(m_Direction.x == -1 && m_Direction.y == 0)
    {
        glRotatef(180, 0,1,0);
    }
    glRotatef(180,1,0,0);
    glutSolidTeapot(radius);
    glPopMatrix();
}

void Ghost::update(float deltaTime)
{
    m_Pos.x += m_Direction.x * deltaTime * m_Speed;
    m_Pos.z += m_Direction.y * deltaTime * m_Speed;
    lastDeltaTime = deltaTime;
}

bool Ghost::collide(Vec3 pos, float thresh) {
    bool collisionX = pos.x <= this->m_Pos.x + thresh + (this->m_Scale.x/2) && pos.x >= this->m_Pos.x - thresh - (this->m_Scale.x/2);
	bool collisionZ = pos.z <= this->m_Pos.z + thresh + (this->m_Scale.z/2) && pos.z >= this->m_Pos.z - thresh - (this->m_Scale.z/2);
	bool collisionY = pos.y <= this->m_Pos.y + thresh + (this->m_Scale.y/2) && pos.y >= this->m_Pos.y - thresh - (this->m_Scale.y/2);

	//bool collisionX = pos.x + thresh >= this->m_Pos.x && this->m_Pos.x + this->m_Scale.x >= pos.x;
	//bool collisionZ = pos.z + thresh >= this->m_Pos.z && this->m_Pos.z + this->m_Scale.z >= pos.z;
    return collisionX && collisionZ && collisionY;
}

void Ghost::setPos(float x, float y, float z)
{
    this->m_Pos = {x,y,z};
}

void Ghost::setPos(Vec3 pos)
{
	this->m_Pos = pos;
}

void Ghost::setInitialPos(Vec3 pos) {
    this->m_initialPos = pos;
}

Vec3 Ghost::getIniciatPos() {
    return this->m_initialPos;
}

int Ghost::getId()
{
    return this->id;
}

void Ghost::setId(int id)
{
    this->id = id;
}

void Ghost::updatePos(Vec3 pos){
	this->m_Pos = {this->m_Pos.x+pos.x, this->m_Pos.y+pos.y, this->m_Pos.z+pos.z};
	std::cout<<"UPDATE: " << this->m_Pos.x << " " << this->m_Pos.y << " " << this->m_Pos.z <<"\n";
}

Vec3 Ghost::getPos()
{
    return this->m_Pos;
}

Vec3 Ghost::getScale()
{
    return this->m_Scale;
}

float Ghost::getRadius()
{
    return this->radius;
}


void Ghost::paredCollision(Vec3 pos)
{
    
    m_Pos.x -= m_Direction.x * lastDeltaTime * m_Speed;
    m_Pos.z -= m_Direction.y * lastDeltaTime * m_Speed;
    Vec2 newDir = m_Direction;
    while((newDir.x == m_Direction.x && newDir.y == m_Direction.y )||(newDir.x == -m_LastDir.x && newDir.y == -m_LastDir.y ))
    {
        int random;
        random = rand() % 4;

        switch(random)
        {
            case 0:
                newDir = {0,1}; 
                break;
            case 1:
                newDir = {0,-1};
                break;
            case 2:
                newDir = {-1,0};
                break;
            case 3:
                newDir = {1,0};
                break;
            default:
                break;
        }
    }
    m_LastDir = m_Direction;
    m_Direction = newDir;
}