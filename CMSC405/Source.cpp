// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>
#include <string>
#define PI (3.141592653589793)

using namespace std;

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 800, winHeight = 600;

// Initialize method
void init(void)
{
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
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);
	// Set  graphic objects color to Red or change for your choice
	glColor3f(1.0, 1.0, 1.0);
	// Your graphics code here
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	//Draw the star background	
	for (int i = 0; i < 150; i++) {
		drawStar((rand() % width) - (width / 2), (rand() % height) - (height / 2));
	}

	//Draw space bug
	glColor3f(1.0, 0.0, 0.0);
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
	glRasterPos2i(-150, -150);
	glBitmap(24.0, 53.0, 0.0, 0.0, 0.0, 0.0, bitBug);

	//Draw Planet
	glColor3f(0.0, 1.0, 1.0);
	GLuint regHex;
	GLdouble theta;
	GLint x, y, k;

	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (k = 0; k < 50; k++) {
		theta = 2 * PI * k / 50.0;
		x = 200 + 30 * cos(theta);
		y = 150 + 30 * sin(theta);
		glVertex2i(x, y);
	}
	glEnd();
	glEndList();
	glCallList(regHex);

	// Draw Triangle Object
	glColor3f(10.0, 10.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(170, 155);
	glVertex2i(170, 145);
	glVertex2i(160, 150);
	glVertex2i(230, 155);
	glVertex2i(230, 145);
	glVertex2i(240, 150);
	glEnd();
	glRecti(170, 155, 230, 145);

	// Add Text Elements	
	string text = "The Final Frontier";
	glRasterPos2i(-9 * (text.length() / 2), 285);
	write("The Final Frontier", text.length());

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

// Refreshes the display and passes itself to be called 150ms later.
void refresh(int x) {
	glutPostRedisplay();
	glutTimerFunc(150, refresh, x);
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

	// Refreshes the display every 150ms
	glutTimerFunc(150, refresh, 1);

	glutMainLoop();
}
