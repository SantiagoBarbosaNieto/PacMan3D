#pragma once

#include <math.h>
#include <string>
#include <GL/glut.h>

#include "RgbImage.h"


struct Vec3
{
    float x, y, z;
};

struct Vec2
{
    float x, y;
};



Vec3 static CalcNormal(Vec3 point1, Vec3 point2, Vec3 point3)
{
    // Calculate vectors
	float value1_x = point2.x - point1.x;
	float value1_y = point2.y - point1.y;
	float value1_z = point2.z - point1.z;

	float value2_x = point3.x - point1.x;
	float value2_y = point3.y - point1.y;
	float value2_z = point3.z - point1.z;

	// Get cross product of vectors
	// See https://i.ytimg.com/vi/0wSDKkRrNFA/maxresdefault.jpg
	float x = (value1_y * value2_z) - (value2_y * value1_z);
	float y = (value1_z * value2_x) - (value2_z * value1_x);
	float z = (value1_x * value2_y) - (value2_x * value1_y);

	// Normalise final vector
	float vLen = sqrt((x * x) + (y * y) + (z * z));

    Vec3 resp = {( float ) x / vLen, ( float ) y / vLen, ( float ) z / vLen};
    return resp;
}

GLuint static loadTextureFromFile(std::string filename) {
    GLuint id;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable (GL_DEPTH_TEST);
	RgbImage theTexMap (filename.c_str ());
	glGenTextures (1, &id);                                         // Create The Texture
	glBindTexture (GL_TEXTURE_2D, id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // GL_NEAREST , GL_LINEAR are different interpolation methods for the textures
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);   // GL_NEAREST , GL_LINEAR are different interpolation methods for the textures

	// Typical Texture Generation Using Data From The Bitmap (( 8 bits red + 8 Bits green + 8 bits blue ) x N pixels in image )
	glTexImage2D (GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols (), theTexMap.GetNumRows (), 1, GL_RGB, GL_UNSIGNED_BYTE,
	              theTexMap.ImageData ());

    return id;
}