#include "block.h"
#include <iostream>
#include <GL/glut.h>

Block::Block()
{

}

Block::~Block()
{

}

void Block::draw()
{
    float AmbDiff[6][4] = {       // 6 ambient diffuse colors of the spheres
            {0.5, 0.0, 0.0, 1.0},         // Red
            {0.5, 0.5, 0.0, 1.0},         // Yellow
            {0.0, 0.5, 0.0, 1.0},         // Green
            {0.0, 0.5, 0.5, 1.0},         // Cyan
            {0.0, 0.0, 0.5, 1.0},         // Blue
            {0.5, 0.0, 0.5, 1.0}          // Magenta
    };
    float Specular[4] = {1, 1, 1, 1.0};
	float emit[4] = {0,0,0, 1.0f};

	if(!faceCull[0])
	{
			glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[3]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 0 ]);
		glBegin (GL_QUADS);
		{
			// Right Face
			Vec3 normal = CalcNormal ({-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f});
			glNormal3f (normal.x, normal.y, normal.z);
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));

		}
		glEnd ();
	}
	

	if(!faceCull[1])
	{

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[3]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 1 ]);
		glBegin (GL_QUADS);
		{
			// Left Face
			Vec3 normal = CalcNormal ({-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, -1.0f});
			glNormal3f (normal.x, normal.y, normal.z);

			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
		}
		glEnd ();
	}


	if(!faceCull[2])
	{

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[0]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 2 ]);
		glBegin (GL_QUADS);
		{
			// Bottom Face
			Vec3 normal = CalcNormal ({-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f});
			glNormal3f (normal.x, normal.y, normal.z);
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));

		}
		glEnd ();
	}

	if(!faceCull[3])
	{

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[4]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 3 ]);
		glBegin (GL_QUADS);
		{

			// Top Face
			Vec3 normal = CalcNormal ({-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f},{ -1.0f, -1.0f, 1.0f});
			glNormal3f (normal.x, normal.y, normal.z);
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
		}
		glEnd ();
	}

	if(!faceCull[4])
	{

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[3]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 4 ]);
		glBegin (GL_QUADS);
		{

			// Front face
			Vec3 normal = CalcNormal ({1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, 1.0f});
			glNormal3f (normal.x, normal.y, normal.z);
			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
		}
		glEnd ();
	}

	if(!faceCull[5])
	{

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, AmbDiff[3]);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 30);
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
		//glBindTexture (GL_TEXTURE_2D, 0);
		//glBindTexture (GL_TEXTURE_2D, m_Texturas[ 0 ]);
		glBegin (GL_QUADS);
		{

			// Back Face
			Vec3 normal = CalcNormal ({-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f});
			glNormal3f (normal.x, normal.y, normal.z);
			//glTexCoord2f (0.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 0.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (-0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (1.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (0.5f*m_Scale.z));
			//glTexCoord2f (0.0f, 1.0f);
			glVertex3f (m_Pos.x + (-0.5f*m_Scale.x), m_Pos.y+ (0.5f*m_Scale.y), m_Pos.z + (-0.5f*m_Scale.z));
		}
		glEnd ();
	}
}

void Block::setTextures(GLuint text[], int numText)
{
    
    for(int i = 0; i < numText; i++)
    {
        m_Texturas[i] = text[i];
    }

    if(numText < 6)
    {
        for(int i = 6-numText; i < 6; i++)
        {
            m_Texturas[i] = text[0];
        }
    }
}

void Block::setTextures(std::vector<GLint> text)
{
    
    for(int i = 0; i < text.size(); i++)
    {
        m_Texturas[i] = text[i];
    }

    if(text.size() < 6)
    {
        for(int i = 6-text.size(); i < 6; i++)
        {
            m_Texturas[i] = text[0];
        }
    }
}

bool Block::collide(Vec3 pos, float thresh)
{
	bool collisionX = pos.x <= this->m_Pos.x + thresh + (this->m_Scale.x/2) && pos.x >= this->m_Pos.x - thresh - (this->m_Scale.x/2);
	bool collisionZ = pos.z <= this->m_Pos.z + thresh + (this->m_Scale.z/2) && pos.z >= this->m_Pos.z - thresh - (this->m_Scale.z/2);
	bool collisionY = pos.y <= this->m_Pos.y + thresh + (this->m_Scale.y/2) && pos.y >= this->m_Pos.y - thresh - (this->m_Scale.y/2);

	//bool collisionX = pos.x + thresh >= this->m_Pos.x && this->m_Pos.x + this->m_Scale.x >= pos.x;
	//bool collisionZ = pos.z + thresh >= this->m_Pos.z && this->m_Pos.z + this->m_Scale.z >= pos.z;
    return collisionX && collisionZ && collisionY;
}

void Block::setPos(float x, float y, float z)
{
    this->m_Pos = {x,y,z};
}

void Block::setPos(Vec3 pos)
{
	this->m_Pos = pos;
}

void Block::updatePos(Vec3 pos){
	this->m_Pos = {this->m_Pos.x+pos.x, this->m_Pos.y+pos.y, this->m_Pos.z+pos.z};
	//std::cout<<"UPDATE: " << this->m_Pos.x << " " << this->m_Pos.y << " " << this->m_Pos.z <<"\n";
}

void Block::setScale(float x, float y, float z)
{
    this->m_Scale = {x,y,z};
}

Vec3 Block::getPos()
{
    return this->m_Pos;
}

Vec3 Block::getScale()
{
    return this->m_Scale;
}


void Block::setFaceCull(bool right, bool left, bool bottom, bool top, bool front, bool back)
{
	this->faceCull[0] = right;
	this->faceCull[1] = left;
	this->faceCull[2] = bottom;
	this->faceCull[3] = top;
	this->faceCull[4] = front;
	this->faceCull[5] = back;
}

