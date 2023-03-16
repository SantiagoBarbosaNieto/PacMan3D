#include "powerUp.h"
#include <iostream>
#include <GL/glut.h>

PowerUp::PowerUp() {

}

PowerUp::~PowerUp() {

}

void PowerUp::setActive(bool active) {
    this->active = active;
}

bool PowerUp::isActive() {
    return this->active;
}

float PowerUp::getRadius() {
    return this->radius;
}

void PowerUp::draw() {

    float white[4] = {1, 1, 1, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    float Specular[4] = {1, 1, 1, 1.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80);
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, white);
    glPushMatrix();
    glTranslatef(this->m_Pos.x, this->m_Pos.y, this->m_Pos.z);
    glColor3f(255, 255, 255);
    glutSolidSphere(this->radius, 10, 10);
    glPopMatrix();
}

bool PowerUp::collide(Vec3 pos, float thresh) {
    bool collisionX = pos.x <= this->m_Pos.x + thresh + (this->m_Scale.x/2) && pos.x >= this->m_Pos.x - thresh - (this->m_Scale.x/2);
	bool collisionZ = pos.z <= this->m_Pos.z + thresh + (this->m_Scale.z/2) && pos.z >= this->m_Pos.z - thresh - (this->m_Scale.z/2);
	bool collisionY = pos.y <= this->m_Pos.y + thresh + (this->m_Scale.y/2) && pos.y >= this->m_Pos.y - thresh - (this->m_Scale.y/2);

	//bool collisionX = pos.x + thresh >= this->m_Pos.x && this->m_Pos.x + this->m_Scale.x >= pos.x;
	//bool collisionZ = pos.z + thresh >= this->m_Pos.z && this->m_Pos.z + this->m_Scale.z >= pos.z;
    return collisionX && collisionZ && collisionY;
}

void PowerUp::setPos(float x, float y, float z)
{
    this->m_Pos = {x,y,z};
}

void PowerUp::setPos(Vec3 pos)
{
	this->m_Pos = pos;
}

void PowerUp::updatePos(Vec3 pos){
	this->m_Pos = {this->m_Pos.x+pos.x, this->m_Pos.y+pos.y, this->m_Pos.z+pos.z};
	std::cout<<"UPDATE: " << this->m_Pos.x << " " << this->m_Pos.y << " " << this->m_Pos.z <<"\n";
}

Vec3 PowerUp::getPos()
{
    return this->m_Pos;
}

Vec3 PowerUp::getScale()
{
    return this->m_Scale;
}
