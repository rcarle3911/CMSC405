// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

#define M_PI 3.14
#define PI 3.14
#define F0 1
#define TS 0.03125
#define AMP 200
#define WIDTH 800
#define HEIGHT 600
#define SLEEPMS 10 // sleep in miliseconds

using namespace std;

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = WIDTH, winHeight = HEIGHT;
GLfloat plRot = 0.0f, pltx = 0.0f, plty = 0.0f, plsx = 1.0f, plsy = 1.0f,
		sbtx = -150.0f, sbty = -150.0f,
		texttx = -90.0f, textty = 285.0f,
		atRot = 0.0f, attx = -400.0f, atty = 0.0f, atsx = 3.0f, atsy = 3.0f,
		btx = 0.0f, bty = 0.0f, bts = 0.0f,
		stRot = 0.0f;
float plSize = 30.0f;
const int stCnt = 150;
int sbDir = 1.0f, plRotDif = 1.0f, textDirX = 1.0f, textDirY = 1.0f;
int strArr[stCnt][2] = {};

void spinStars(void) {
	Sleep(SLEEPMS);

	stRot += 1.0f;

	glutPostRedisplay();
}

void moveBug(void);

void shoot(void) {
	Sleep(SLEEPMS / 10);

	if (bty > HEIGHT / 2) {
		bts = 0.0f;
		glutIdleFunc(moveBug);
	}

	bty += 1.0f;
	glutPostRedisplay();
}

void moveBug(void) {
	Sleep(SLEEPMS);
	if (sbtx > (WIDTH / 2 - 24)) {
		sbDir = -1.0f;
	}

	if (sbtx < -(WIDTH / 2)) {
		sbDir = 1.0f;
	}

	if(rand() % 50 == 0) {
		btx = sbtx + 12;
		bty = sbty + 54;
		bts = 1.0f;
		glutIdleFunc(shoot);
	}
	sbtx += sbDir;

	glutPostRedisplay();
}

void wobblePlanet(void) {
	Sleep(SLEEPMS);
	
	if (plRot > 15) {
		plRotDif = -1.0f;
	}

	if (plRot < -15) {
		plRotDif = 1.0f;
	}

	plRot += plRotDif;

	glutPostRedisplay();
}

void shootAsteroid(void);

void movePlanet(void) {
	Sleep(SLEEPMS);

	pltx += 1.0f;
	plRot -= 0.1f;

	if (pltx >= 370) {
		pltx = 0.0f;
		plRot = 0.0f;
		atRot = 0.0f;
		attx = -400.0f;
		glutIdleFunc(shootAsteroid);
	}

	glutPostRedisplay();
}

void shootAsteroid(void) {
	Sleep(SLEEPMS);
	
	attx += 1.0f;
	atRot += 0.5f;

	if (attx >= -30) {
		glutIdleFunc(movePlanet);
	}

	glutPostRedisplay();
}

void bounceText(void) {
	Sleep(SLEEPMS);

	if (texttx > WIDTH / 2 - 160) {
		textDirX = -1.0f;
	} else if (texttx < -(WIDTH / 2)) {
		textDirX = 1.0f;
	}

	if (textty > HEIGHT / 2 - 13) {
		textDirY = -1.0f;
	}
	else if (textty < -(HEIGHT / 2)) {
		textDirY = 1.0f;
	}

	texttx += textDirX;
	textty += textDirY;

	glutPostRedisplay();
}

// Initialize method
void init(void)
{
	//Generate star positions
	strArr[stCnt][2] = {};
	for (int i = 0; i < stCnt; i++) {
		strArr[i][0] = rand() % winWidth - winWidth / 2;
		strArr[i][1] = rand() % winWidth - winWidth / 2;
	}
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// Black color window
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// Projection on World Coordinates 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}
void otherCode()
{
	// Your other code here
}

// Left mouse starts the animation
// Right mouse stops the animation
void mouseFcn(GLint button, GLint action, GLint x, GLint y)
{

	switch (button) {
	case GLUT_LEFT_BUTTON:           //  Start the animation.
		if (action == GLUT_DOWN)
			glutIdleFunc(shootAsteroid);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (action == GLUT_DOWN)
			glutIdleFunc(spinStars);
		break;
	case GLUT_RIGHT_BUTTON:            //  Stop the animation.
		if (action == GLUT_DOWN)
			glutIdleFunc(bounceText);
		break;
	default:
		break;
	}
}
// Clicking ‘1’ starts the animation
// Clicking ‘2’ stops the animation
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '0':	/*  0 key starts planet wobble */
		glutIdleFunc(wobblePlanet);
		break;
	case '1':   /*  1 key starts the animation  */
		glutIdleFunc(moveBug);
		break;
	case '2': /*  2 key stops the animation  */
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void drawStar(int x, int y) {
	glRecti(x - 1, y - 1, x + 2, y + 2);
	glBegin(GL_LINES);
	glVertex2i(x + 1, y - 2);
	glVertex2i(x + 1, y + 3);
	glVertex2i(x - 2, y + 1);
	glVertex2i(x + 3, y + 1);
	glEnd();
}

// Write text to screen
void write(char* s, int size) {	
	for (int i = 0; i < size; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *s);
		s++;
	}
}

// Generate the Graphics
void displayFcn()
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);
	// Set  graphic objects color to Red or change for your choice
	glColor3f(1.0, 1.0, 1.0);
	// Your graphics code here
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glPushMatrix();
	glRotatef(stRot, 0.0f, 0.0f, 1.0f);
	//Draw the star background	
	for (int i = 0; i < stCnt; i++) {
		drawStar(strArr[i][0], strArr[i][1]);
	}
	glPopMatrix();
	//Draw space bug
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(sbtx, sbty, 0.0f);
	GLubyte bitBug[159] = {
		0x00, 0xFF, 0x00,
		0x01, 0xFF, 0x80,
		0x03, 0xFF, 0xC0,
		0x07, 0xFF, 0xE0,
		0x0F, 0xFF, 0xF0,
		0x9E, 0x18, 0x79,
		0x9E, 0x18, 0x79,
		0x9E, 0x18, 0x79,
		0xDE, 0x3C, 0x7B,
		0xBE, 0x00, 0x7D,
		0x1E, 0x00, 0x78,
		0x0F, 0x00, 0xF0,
		0x07, 0x81, 0xE0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x00,
		0x00, 0x7E, 0x00,
		0x1F, 0xFF, 0xF8,
		0x1F, 0xFF, 0xF8,
		0x1F, 0xFF, 0xF8,
		0x9F, 0xFF, 0xF9,
		0xFE, 0x00, 0x7F,
		0x9F, 0x00, 0xF9,
		0x0F, 0xFF, 0xF0,
		0x07, 0xFF, 0xE0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0xFF, 0xFF, 0xFF,
		0xFF, 0x5A, 0xFF,
		0xFF, 0x5A, 0xFF,
		0xFF, 0x5A, 0xFF,
		0xF3, 0x42, 0xCF,
		0xFF, 0x24, 0xFF,
		0xE1, 0x99, 0x87,
		0xE1, 0xC3, 0x87,
		0xFF, 0xFF, 0xFF,
		0xF3, 0xFF, 0xCF,
		0xFF, 0xFF, 0xFF,
		0x00, 0x70, 0x00,
		0x00, 0x20, 0x00,
		0x00, 0x20, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x62, 0x00,
		0x00, 0x50, 0x00,
		0x00, 0x48, 0x00,
		0x00, 0x40, 0x00,
		0x00, 0x60, 0x00
	};
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, 0);
	glBitmap(24.0, 53.0, 0.0, 0.0, 0.0, 0.0, bitBug);
	glPopMatrix();

	//Draw Planet
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(pltx, plty, 0.0f);
	glScalef(plsx, plsy, 1.0f);
	GLuint regHex;
	GLdouble theta;
	GLint x, y, k;

	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (k = 0; k < plSize; k++) {
		theta = 2 * PI * k / plSize;
		x = plSize * cos(theta);
		y = plSize * sin(theta);
		glVertex2i(x, y);
	}
	glEnd();
	glEndList();
	glCallList(regHex);

	// Draw Planet Rings
	int ring = plSize / 6;
	glColor3f(1.0, 1.0, 0.0);	
	glRotatef(plRot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2i(-plSize, ring);
	glVertex2i(-plSize, -ring);
	glVertex2i(-(plSize * (4.0/3.0)), 0);
	glVertex2i(plSize, ring);
	glVertex2i(plSize, -ring);
	glVertex2i(plSize * (4.0/3.0), 0);
	glEnd();
	glRecti(-plSize, ring, plSize, -ring);
	glPopMatrix();

	// Add Text Elements	
	string text = "The Final Frontier";
	glPushMatrix();
	glTranslatef(texttx, textty, 0.0f);
	glRasterPos2i(0, 0);
	write("The Final Frontier", text.length());
	glPopMatrix();

	// Add Asteriod
	glColor3f(.8, .5, .8);
	glPushMatrix();
	glTranslatef(attx, atty, 0.0f);
	glScalef(atsx, atsy, 1.0f);
	glRotatef(atRot, 0, 0, 1);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glBegin(GL_POLYGON);
		glVertex2i(7,3);
		glVertex2i(7,4);
		glVertex2i(8,5);
		glVertex2i(6,6);
		glVertex2i(6,7);
		glVertex2i(4,5);
		glVertex2i(2,7);
		glVertex2i(0,5);
		glVertex2i(2,5);
		glVertex2i(0,3);
		glVertex2i(1,1);
		glVertex2i(2,3);
		glVertex2i(3,3);
		glVertex2i(2,1);
		glVertex2i(3,0);
		glVertex2i(4,1);
		glVertex2i(4,2);
		glVertex2i(6,2);
		glVertex2i(4,0);
		glVertex2i(6,0);
		glVertex2i(7,1);
		glVertex2i(8,1);
		glVertex2i(8,2);
		glVertex2i(9,3);
	glEnd();
	glEndList();
	glCallList(regHex);
	glPopMatrix();

	// Bullet
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(btx, bty, 0.0f);
	glScalef(bts, bts, 1.0f);
	glRecti(-1, 2, 1, -2);
	glPopMatrix();

	// Execute OpenGL functions
	glFlush();
}
// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)newWidth / 2, (GLdouble)newWidth / 2, -(GLdouble)newHeight / 2, (GLdouble)newHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Main function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set initial Window position
	glutInitWindowPosition(100, 100);
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);
	// Set Window Title
	glutCreateWindow("Robert Carle - Homework 2");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);

	glutMouseFunc(mouseFcn);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

}
