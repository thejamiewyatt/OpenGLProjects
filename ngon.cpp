//Jamie Wyatt
//9-27-2018
//HOMEWORK 1, QUESTION 2, NGON PROGRAM


#include <gl/freeglut.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159


void drawNgon(GLfloat x, GLfloat y, GLfloat radius, GLint sides) {
	
	GLfloat twicePi = 2.0f * PI;	//Circle Drawing routine, with limited sides
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0);
	glVertex2f(x, y);
	for (int i = 0; i <= sides; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / sides)),
			y + (radius * sin(i * twicePi / sides))
		);
	}
	glEnd();
	glFlush();
}


void display() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glClearColor(0, 0, 0, 0);
	gluOrtho2D(0, 640, 0, 640);
	glMatrixMode(GL_PROJECTION);
	srand(time(0));
	int num_polys = rand() % 10 + 4;
	for (int i = 0; i < num_polys; i++) {
		drawNgon(rand() % 640, rand() % 640, rand() % 100 + 100, rand() % 7 + 3);
	}

}


int main(int argc, char** argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(20, 20);
	glutInitWindowSize(640, 640);
	glutCreateWindow("N-Gon");

	glutDisplayFunc(display);


	glutMainLoop();
}

