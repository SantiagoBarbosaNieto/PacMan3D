#include "coin.h"
#include <iostream>
#include <GL/glut.h>


Coin::Coin() {

}

Coin::~Coin() {

}

void Coin::setActive(bool active) {
    this->active = active;
}

bool Coin::isActive() {
    return this->active;
}

void Coin::draw() {

    float yellow[4] = {0.5,0.5,0,1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
    float Specular[4] = {1, 1, 1, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80);
    float noemit[4] = {0,0,0,1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, noemit);
    glPushMatrix();
    
    glTranslatef(this->m_Pos.x, this->m_Pos.y, this->m_Pos.z);
    glColor3f(255, 255, 0);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

bool Coin::collide(Vec3 pos, float thresh) {
    bool collisionX = pos.x <= this->m_Pos.x + thresh + (this->m_Scale.x/2) && pos.x >= this->m_Pos.x - thresh - (this->m_Scale.x/2);
	bool collisionZ = pos.z <= this->m_Pos.z + thresh + (this->m_Scale.z/2) && pos.z >= this->m_Pos.z - thresh - (this->m_Scale.z/2);
	bool collisionY = pos.y <= this->m_Pos.y + thresh + (this->m_Scale.y/2) && pos.y >= this->m_Pos.y - thresh - (this->m_Scale.y/2);

	//bool collisionX = pos.x + thresh >= this->m_Pos.x && this->m_Pos.x + this->m_Scale.x >= pos.x;
	//bool collisionZ = pos.z + thresh >= this->m_Pos.z && this->m_Pos.z + this->m_Scale.z >= pos.z;
    return collisionX && collisionZ && collisionY;
}

void Coin::setPos(float x, float y, float z)
{
    this->m_Pos = {x,y,z};
}

void Coin::setPos(Vec3 pos)
{
	this->m_Pos = pos;
}

void Coin::updatePos(Vec3 pos){
	this->m_Pos = {this->m_Pos.x+pos.x, this->m_Pos.y+pos.y, this->m_Pos.z+pos.z};
	std::cout<<"UPDATE: " << this->m_Pos.x << " " << this->m_Pos.y << " " << this->m_Pos.z <<"\n";
}

Vec3 Coin::getPos()
{
    return this->m_Pos;
}

Vec3 Coin::getScale()
{
    return this->m_Scale;
}
