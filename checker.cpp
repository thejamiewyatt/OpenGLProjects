//Jamie Wyatt
//9-26-18
//HOMEWORK 1, QUESTION 1, CHECKER.CPP


#include <gl/freeglut.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void display() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(0, 640, 0, 640);

	srand(time(0));

	float Colors1[] = { rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0 };
	float Colors2[] = { rand() % 100 / 100.0 ,rand() % 100 / 100.0 ,rand() % 100 / 100.0 };

	GLfloat size = 10;

	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 64; ++j) {
			if ((i + j) % 2 == 0) 
				glColor3f(Colors1[0], Colors1[1], Colors1[2]);
			else
				glColor3f(Colors2[0], Colors2[1], Colors2[2]);
			glRecti(i*size, j*size, (i + 1)*size, (j + 1)*size);    
		}
	}
		glFlush(); 
}


int main(int argc, char** argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(20, 20);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Checker");

	

	glutDisplayFunc(display);


	glutMainLoop();
}

