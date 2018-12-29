//Jamie Wyatt
//9-27-2018
//Homework 1, Question 4, HexAnim


//KEYBOARD 'q' for QUIT WORKS, May be delayed reaction based on Machine running the program

#include <GL/glut.h>
#include <gl/freeglut.h>
#include <math.h>

#define PI 3.14159

bool a_key_down = false;

void keyboard(unsigned char key, int x, int y) { //see if user pressed q
	if (key == 'q') a_key_down = true;
}

void idle() {

	if (a_key_down == true) exit(0); //if user pressed q, wait for idle function to handle it
}


void setWindow(float left, float right, float bottom, float top)
{
glMatrixMode(GL_PROJECTION); //from the text book
glLoadIdentity(); 
gluOrtho2D(left, right, bottom, top); 
}

void setViewport(float left, float right, float bottom, float top)
{
	glViewport(left, bottom, right - left, top - bottom); //from the text book
}

void drawHex(GLfloat x, GLfloat y, GLfloat radius) {
	int sides = 6;
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_LINE_STRIP);
	glLineWidth(1.0);
	glColor3f(0,0,1);
	for (int i = 0; i <= sides; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / sides)),
			y + (radius * sin(i * twicePi / sides))
		);
	}
	
	glEnd();
	
}

void hexSwirl() {
	float radius = 100;
	float angle = 0;
	for (int i = 0; i < 50; i++) {
	glPushMatrix();
	glTranslatef(200, 200, 0);
	glRotatef(angle, 0.0, 0, 1); //translate to origin, rotate, translate back
		drawHex(0, 0, radius);
		radius -= 2;
		angle += 3;
		glPopMatrix();
	}
	glutPostRedisplay();
}


void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double window_width = glutGet(GLUT_WINDOW_WIDTH);
	double window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, window_width, window_height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1, 1, 1, 0);

	//ZOOM IN FUNCTION
	for (float i = 0; i < 200; i+=.1) {
		glClear(GL_COLOR_BUFFER_BIT);
		setWindow(200 - i, 200 + i, 200 - i, 200 + i); // the portion of the swirl to draw 
		hexSwirl();
		glutPostRedisplay();
		glutSwapBuffers();
	}

	//ZOOM OUT FUNCTION
	for (float i = 200; i > 0; i-=.1) {
		glClear(GL_COLOR_BUFFER_BIT);
		setWindow(200 - i, 200 + i, 200 - i, 200 + i); // the portion of the swirl to draw 
		hexSwirl();
		glutPostRedisplay();
		glutSwapBuffers();
	}
	
}

int main(int argc, char** argv)
{glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Hex Animation");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
