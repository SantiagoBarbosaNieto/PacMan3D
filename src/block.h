#pragma once
#include <stdio.h>
#include <vector>

#include "utils.h"

class Block
{
public:
    Block();
    ~Block();

    void setPos(Vec3 pos);
    void setPos(float x, float y, float z);
    void updatePos(Vec3 pos);

    void setScale(float x, float y, float z);
    void setTextures(GLuint text[], int numText);
    void setTextures(std::vector<GLint> text);

    void draw();

    bool collide(Vec3 pos, float thresh);
    void setFaceCull(bool right, bool left, bool bottom, bool top, bool front, bool back);

    Vec3 getPos();
    Vec3 getScale();
private:

    Vec3 m_Pos = {0.0f,0.0f,0.0f};
    Vec3 m_Scale = {1.0f,1.0f,1.0f};

    GLuint m_Texturas[6];
    int type = 0;
    bool faceCull[6] = {true,true,true,true,true,true}; //

};