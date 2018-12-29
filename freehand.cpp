//Jamie Wyatt
//9-27-2018
//Homework 1, Question 3, Freehand

//glLineWidth does not work on my machine, but its used below because
//of compatibility with older versions of OpenGL.

#include <GL/glut.h>
#include <gl/freeglut.h>
#include <gl/GLU.h>
#include <vector>

std::vector< int > points;

//Line Width Global
float linewidth = 1.0;

void arrows(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		linewidth += 1.0; //increase width if user presses up
		break;
	case GLUT_KEY_DOWN:
		if (linewidth - 1.0 <= 0) break; //decrease width if user presses down
		else linewidth -= 1.0;
		break;
	}

}

void Mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		points.clear();

	if (button == GLUT_LEFT_BUTTON) //left click to draw
	{
		points.push_back(x);
		points.push_back(y);
		
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		
		glClear(GL_COLOR_BUFFER_BIT); //right click to erase
		points.clear();
		glFlush();
	}
}

void motion(int x, int y)
{
	points.push_back(x); //Follow mouse movement
	points.push_back(y);
	
}


void draw() {

	//ON MOUSE CLICK
	glBegin(GL_LINE_STRIP);
	glLineWidth(linewidth);
	glColor3f(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f);
	
	for (int i = 0; i < points.size(); i += 2)
	{
		glVertex2i(points[i], points[i + 1]);
	}
	glEnd();
	
}

void display()
{
	glClearColor(1, 1, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double window_width = glutGet(GLUT_WINDOW_WIDTH);
	double window_height = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, window_width, window_height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	draw();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB| GLUT_SINGLE);
	glutCreateWindow("Freehand");
	glutMouseFunc(Mymouse);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutSpecialFunc(arrows);
	glutMainLoop();
	return 0;
}

