#include "Main.hpp"

#include <iostream>

#include "GL/freeglut.h"
#include "GL/gl.h"

int main()
{
	Main m;
	m.start();
}

void renderFunction()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();
}

Main::Main()
{}

void Main::start()
{
	int argc = 1;
	char *argv[1] = {(char*)""};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL - First window :D");
	glutDisplayFunc(renderFunction);
	glutMainLoop();
}
