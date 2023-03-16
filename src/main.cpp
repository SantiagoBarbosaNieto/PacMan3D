#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <chrono>

#include "block.h"
#include "coin.h"
#include "juego.h"
#include "pacman.h"

bool autoRotate = true;
GLfloat xRotated, yRotated, zRotated;

const int num_Textures = 6;
GLuint texture[num_Textures]; // Storage For One Texture ( NEW )

GLfloat qaWhiteAM[] = {
		1.0, 1.0, 1.0, 1.0}; // White Ambient Material Color
GLfloat qaWhiteDF[] = {
		1.0, 1.0, 1.0, 1.0}; // White Diffuse Material Color
GLfloat qaWhite[] = {
		1.0, 1.0, 1.0, 1.0}; // White Color

GLfloat NormalX = 0;
GLfloat NormalY = 0;
GLfloat NormalZ = 0; 

// Set lighting intensity and color
GLfloat qaAmbientLight[] = {
		1, .8, .8, 1.0};// Red Ambient Light
GLfloat qaDiffuseLight[] = {
		.8, 1, .8, 1.0}; // Green Diffuse Light
GLfloat qaSpecularLight[] = {
		.8, .8, 1, 1.0}; // Blue Specular Light

// Light source position
GLfloat qaLightPosition[] = {0, 30, 0, 1};

std::chrono::steady_clock::time_point lastFrameTime;
std::chrono::steady_clock::time_point thisFrameTime;

class RenderState {
 public:  
   float mouseX,mouseY,cameraX,cameraY;
   bool mouseLeftDown, mouseRightDown;
   RenderState () {    
     this->mouseX = 0;
     this->mouseY = 0;
     this->mouseLeftDown = false;
     this->mouseRightDown = false;
     this->cameraX = 0.0f;
     this->cameraY = 0.0f;  
   }
 
};

RenderState rs;
Juego* juego;

void init(void) {
	juego = new Juego();
	juego->setPos({0.0f,0.5f,0.0f});

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	RenderState* rsp = new RenderState();
	rs = *rsp;
	lastFrameTime = std::chrono::steady_clock::now();
}

void initLighting() {

	// Enable lighting
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT0);

	// Set lighting intensity and color
	glLightfv (GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv (GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	glLightfv (GL_LIGHT0, GL_POSITION, qaLightPosition);

}

void drawCoordinates(){

    // draw some lines
    glColor3f(1.0,0.0,0.0); // red x
    glBegin(GL_LINES);
    // x aix
 
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
    glEnd();
 
    // y 
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -4.0f, 0.0f);
    glVertex3f(0.0, 4.0f, 0.0f);
    glEnd();
 
    // z 
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-4.0f );
    glVertex3f(0.0, 0.0f ,4.0f );
 
    glEnd();
	glColor3f(1.0f,1.0f,1.0f);
}

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {
  char *c;
  glRasterPos3f(x,y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

/*
* Draw the texture in the OpenGL graphics window
*/
void drawScene(void) {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, qaWhiteAM);
	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhiteDF);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 50);


	glLoadIdentity ();
	Vec3 pacPos = juego->getPacman()->getPos();
	glTranslatef(-pacPos.z, pacPos.x, pacPos.y -20);
	
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 0, 0, 1);



    //AQUI VA LO QUE QUERAMOS DRAW
	
	thisFrameTime = std::chrono::steady_clock::now();

	float deltaTime = ((float)std::chrono::duration_cast<std::chrono::microseconds>(thisFrameTime - lastFrameTime).count())/1000000;
	lastFrameTime = thisFrameTime;
	//std::cout <<"Delta time (s): " << (float)deltaTime  <<"\n";
	char coinsCount[15];

	sprintf(coinsCount, "Score: %d", juego->getCoinCount());
	glPushMatrix();
	glPopMatrix();
	glPushMatrix();
	drawCoordinates();
	glPopMatrix();
	glPushMatrix();
	juego->update(deltaTime);
	glPopMatrix();
	glPushMatrix();
	juego->draw();
	glTranslatef(-8,0,10);
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, qaWhite);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, qaSpecularLight);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80); 
	float emit[4] = {0,0,0,1};
	glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emit);
	renderBitmapString(pacPos.x+0.0f, pacPos.y-1.5f, pacPos.z+0.0f, (void *)GLUT_BITMAP_TIMES_ROMAN_24, coinsCount);
	glPopMatrix();

	glFlush (); //  forces execution of OpenGL functions before continuing
	glDisable (GL_TEXTURE_2D); // 
	glutSwapBuffers(); // Needed if 2 buffers  (GLUT_DOUBLE), not needed if GLUT_SINGLE used
}

void mouseCallback(int button, int state, int x, int y)
{
    rs.mouseX = x;
    rs.mouseY = y;
 
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            rs.mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            rs.mouseLeftDown = false;
    }
}
 
void mouseMotionCallback(int x, int y)
{
    if(rs.mouseLeftDown)
    {
        rs.cameraY += (x - rs.mouseX);
        rs.cameraX += (y - rs.mouseY);
        rs.mouseX = x;
        rs.mouseY = y;
    }
}
 
 
void idleCallback()
{
    glutPostRedisplay();
}

void resizeWindow(int x, int y) {
	if ( y == 0 || x == 0 ) return;  //Nothing is visible then, so return

	//Set a new projection matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective (50.0, //Angle of view:50 degrees
					( GLdouble ) x / ( GLdouble ) y, // Aspect ratio
					0.1,  //Near clipping plane distance: 0.5
					150.0);//Far clipping plane distance: 20.0
	glMatrixMode (GL_MODELVIEW);
	glViewport (0, 0, x, y);  //Use the whole window for rendering
}

void keyboard(unsigned char key, int x, int y) {
	switch ( key ) {
		case 27:
			exit (0);
			break;
		case '+':
			autoRotate = !autoRotate; 			// Disable automatic rotation
		default:
			break;
	}
}


void specialKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		std::cout <<"KEY_RIGHT Pressed\n";
		juego->arrowsInput(0);
		break;
	case GLUT_KEY_LEFT:
		std::cout <<"KEY_LEFT Pressed\n";
		juego->arrowsInput(1);
		break;
	case GLUT_KEY_UP:
		std::cout <<"KEY_UP Pressed\n";
		juego->arrowsInput(2);
		break;
	case GLUT_KEY_DOWN:
		std::cout <<"KEY_DOWN Pressed\n";
		juego->arrowsInput(3);
		break;
	}
	
	glutPostRedisplay();
	
}

void idleFunc(void) {
	if ( autoRotate ) {
		xRotated += 0.01;
		yRotated += 0.01;
		zRotated -= 0.01;
	}
	drawScene ();
}



int main(int argc, char **argv) {

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1200, 800);
	glutInitWindowPosition (950, 200);
	glutCreateWindow (argv[ 0 ]);
	init();
	initLighting ();
	glutDisplayFunc (drawScene);
	glutReshapeFunc (resizeWindow);
	glutKeyboardFunc (keyboard);
	glutIdleFunc (idleFunc);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotionCallback);
	glutSpecialFunc(specialKey);

/*
	std::string filename[num_Textures] = {"../assets/t1.bmp", "../assets/t2.bmp", "../assets/t3.bmp", "../assets/t4.bmp", "../assets/t5.bmp", "../assets/t5.bmp"}; // 2 texturas nuevas agregadas
	for ( int i = 0; i < num_Textures; i++ )
		texture[i] = loadTextureFromFile (filename[ i ]);
	
	b = new Block();
	b->setTextures(texture, num_Textures);
	b->setScale(1.0,2.0,4.0);
	b->setPos(5.0f,1.0f,0.0f);
*/
	glViewport (0, 0, (GLsizei) 500, (GLsizei) 500);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);

	glutMainLoop ();
	return 0;
}