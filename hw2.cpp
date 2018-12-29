//Jamie Wyatt
//10-18-2018
//Homework 2
//INTRO TO GRAPHICS

#include <GL/glut.h>
#include <gl/freeglut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define min3(x, y, z) ((x) < (y))? (((x) < (z))? (x) : (z)) : (((y) < (z))? (y) : (z))
#define max3(x, y, z) ((x) > (y))? (((x) > (z))? (x) : (z)) : (((y) > (z))? (y) : (z))

////////////////////////GLOBALS
void spinner(int);
float posz[15];
float posx[15];
float posy[15];
float r[15];
float g[15];
float b[15];
float xAngle[15];
float yAngle[15];
float h = 0;
float s = 1;
float v = 1;
bool a_key_down = false;
bool firstrun = true;

//////////////////////////////////////KEYBOARD FUNCTION
void keyboard(unsigned char key, int x, int y) { //see if user pressed q
	if (key == 'q') a_key_down = true;
}
//////////////////////////////////////IDLE FUNCTION
void idle() {
	if (a_key_down == true) exit(0); //if user pressed q, wait for idle function to handle it
}

/////////////////////////////////////DRAW A TEAPOT WITH A SPECIFIC LOCATION AND COLOR [CALLED IN FLYINGTEAPOT() FOR EACH TEAPOT] 
void moveTeapot(float posX, float posY, float screenProximity, float r, float g, float b,int j) {
	
	GLfloat mat_diffuse[] = {r, g, b }; 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glPushMatrix();
	glTranslatef(posX, posY, screenProximity);
	glRotated(xAngle[j], 1.0, 0.0, 0.0); // x-roll
	glRotated(yAngle[j], 0.0, 1.0, 0.0); // y-roll
	glTranslatef(0, 0, 0);
	glutSolidTeapot(2);
	glPopMatrix();
}

void Walls();

//////////////////////////////////////////////////////////////////////////FLYING TEAPOT FUNCTION
void FlyingTeaPot() {	
	if (firstrun) //SETUP ORIGINAL POSITIONS AND COLORS FOR EACH INDEX
	{
		for (int j = 0; j < 15; j++) 
		{
			r[j] = rand() % 100 / 100.0;
			g[j] = rand() % 100 / 100.0;	//RANDOM COLORS
			b[j] = rand() % 100 / 100.0;
			posz[j] = rand() % 300;
			posx[j] = rand() % 40 + -20;	//RANDOM LOCATIONS
			posy[j] = rand() % 40 + -20;
		}

		firstrun = false;	//SO THIS DOESNT RUN BESIDES THE FIRST TIME (GLOBAL VAR)
	}
	//CLEAR THE SCREEN
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DRAW THE TEACUPS, CHANGE THE Z VALUE TO DECREASE TOWARDS THE SCREEN, USE GLOBALS TO SAVE
	//VALUES SO THE MAIN LOOP IS CONTINUOUS
	for(int j = 0; j < 15; j++){
			moveTeapot(posx[j], posy[j], posz[j] -= .2, r[j],g[j],b[j], j);
			
			//IF IT TOUCHES TH NEAR PLANE (Z=0), RESET THE TEACUP IN QUESTION
			if (posz[j] < 0) {
					posz[j] = rand() % 300;
					posx[j] = rand() % 40 + -20;
					posy[j] = rand() % 40 + -20;
					r[j] = rand() % 5 / 4.0;
					g[j] = rand() % 5 / 4.0;
					b[j] = rand() % 5 / 4.0;
				}

			//SPIN THE SPECIFIC TEACUP
			spinner(j);
			}
		//DRAW THE WALLS
		Walls();

		glutPostRedisplay();
		glutSwapBuffers();
}
///////////////////////////////////////////DRAW THE WALLS FUNCTION
void Walls() {

		//GRAY WALL COLOR DIFFUSE
		GLfloat mat_diffuse[] = { .3, .3, .3 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glPushMatrix();
		glBegin(GL_QUADS);
		/* Floor */
		glNormal3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-100, -100, -100);
		glVertex3f(-100, -100, 300);
		glVertex3f(100, -100, 300);
		glVertex3f(100, -100, -100);

		/* Ceiling */
		glNormal3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-100, 100, -100);
		glVertex3f(-100, 100, 300);
		glVertex3f(100, 100, 300);
		glVertex3f(100, 100, -100);    
		
		/* Walls */
		glNormal3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-100, -100, -300);
		glVertex3f(-100, -100, 300);	//LEFT
		glVertex3f(-100, 100, 300);
		glVertex3f(-100, 100, -300);

		glNormal3f(0.0f, 1.0f, 1.0f);
		glVertex3f(100, -100, -300);
		glVertex3f(100, -100, 300);		//RIGHT
		glVertex3f(100, 100, 300);
		glVertex3f(100, 100, -300);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(100, 100, 290);
		glVertex3f(-100, 100, 290);		//BACKWALL(FARPLANE)
		glVertex3f(-100, -100, 290);
		glVertex3f(100, -100, 290);

		glEnd();
		glPopMatrix();
}
////////////////////////////////////DISPLAY FUNCTION
void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluPerspective(60.0, 640.0 / 480, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	GLfloat lightIntensity[] = { 1.0, 1.0f, 1.0f, 0.0f };
	GLfloat light_position[] = { 0.0f, 20.0f, 30.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	FlyingTeaPot();
	}
//////////////////////////////////////SPINNER FUNCTION, USES 'J' WHICH REFERS TO EACH TEAPOT INDEX
void spinner(int j) { 
float xSpeed = 2.0/(j+1);
float ySpeed = 1.0/(j+1);
xAngle[j] += xSpeed;
yAngle[j] += ySpeed; h += 1;
if (h > 360) h -= 360;
glutPostRedisplay(); }

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Flying Teapots");
	glutInitWindowPosition(10, 10);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); // hidden surface removal
	glEnable(GL_NORMALIZE); // normalize vectors for proper shading
	srand(time(0));
	glutMainLoop();
return 0;
}



/*//////////////////////////////////////UNUSED CODE FROM CANVAS///////////////////////////////
inline void RGB2HSV(float r, float g, float b, float& h, float& s, float& v)
// h = [0,360], s = [0,1], v = [0,1]
// r, g, b = [0,1]
{float min, max, delta;
// r,g,b values are from 0 to 1// h = [0,360], s = [0,1], v = [0,1]
// if s == 0, then h = -1 (undefined)
min = min3(r, g, b);max = max3(r, g, b);v = max;                     // v
delta = max - min;
if (max != 0)s = delta / max;       // s
else {
	// r = g = b = 0       // s = 0, v is undefined
	s = 0;
	h = -1;
	return;}

if (r == max) { h = (g - b) / delta; }         // between yellow & magenta
else if (g == max) { h = 2 + (b - r) / delta; }    // between cyan & yellow
else {
	h = 4 + (r - g) / delta;
}     // between magenta & cyan
h *= 60;                    																			// degrees
if (h < 0) { h += 360; }

}

inline void HSV2RGB(float h, float s, float v, float& r, float& g, float& b)// h = [0,360], s = [0,1], v = [0,1]
																			// r, g, b = [0,1]
{int i;float f, p, q, t;
if (s == 0) {
	// achromatic (grey)
	r = g = b = v;
	return;
}
h /= 60;               // sector 0 to 5
i = (int)floor(h);f = h - i;             // factorial part of h
p = v * (1 - s);q = v * (1 - s * f);
t = v * (1 - s * (1 - f));
switch (i) {case 0:r = v;g = t;
b = p;
break;
case 1:r = q;
g = v;b = p;
break;
case 2:r = p;
g = v;
b = t;
break;
case 3:r = p;
g = q;
b = v;
break;
case 4:r = t;
g = p;
b = v;
break;
default:         // case 5:
	r = v;
	g = p;
	b = q;
	break;
}
}
*/

