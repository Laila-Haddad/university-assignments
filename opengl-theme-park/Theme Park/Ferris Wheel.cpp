#include <GL/glut.h>
#include <math.h>
#include <iostream>

float pitch = 0, yaw = 0;
int asd = 1;

double ph = 0.1, th = 0, up = 0;
double EX = 0, EY = 0, EZ = 0, CX = 0, CY = 0, CZ = 0;

int wheel = 0;
double wheel_compartment = 0;

float swing_ride_seats = 1;
float swing_ride = 0;
float i = 0;

int ship_angle = 75;
int ship_direction = 2;

double train = 0;

GLUquadricObj* a = gluNewQuadric();

void timer(int) {
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();

	//ferris wheel
	wheel++;
	wheel_compartment += 0.0174533;


	//swing ride
	swing_ride_seats = swing_ride_seats + 0.5;
	if (i > 0 && i < 400) {
		swing_ride = swing_ride + 0.1;
	}
	if (i >= 400 && i < 440) {
		swing_ride = swing_ride - 1;
	}
	if (i == 440) {
		i = 0;
	}  i++;

	if (ship_angle == 75 || ship_angle == -75)
		ship_direction *= -1;
	ship_angle += ship_direction;

	train += 1;


}
//keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: /* Escape key */
		exit(0);
		break;

	case 'w':
		EX = EX + cos(th - 3.14 / 2);
		EZ = EZ + sin(th - 3.14 / 2);
		break;
	case 's':
		EX = EX - cos(th - 3.14 / 2);
		EZ = EZ - sin(th-3.14 / 2);
		break;
	case 'a':
		EX = EX - cos(th);
		EZ = EZ - sin(th );
		break;
	case 'd':
		EX = EX + cos(th );
		EZ = EZ + sin(th );
		break;

	case ' ':
		EY = EY + .5;
		break;
	case 'c':
		EY = EY - .5;
		break;


		//disabling lighting
	case 'j':
		asd = 1;
		break;

	case 'k':
		asd = -1;
		break;

	default:
		break;
	}
}

void specialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		th += 0.1;
		break;
	case GLUT_KEY_LEFT:
		th -= 0.1;
		break;
	case GLUT_KEY_UP:
		ph -= 0.3;
		break;
	case GLUT_KEY_DOWN:
		ph += 0.3;
		break;
	default:
		break;
	}
}
void passive_motion(int x, int y)
{
	int dev_x, dev_y;
	dev_x = (640 / 2) - x;
	dev_y = (640 / 2) - y;

	yaw += (float)dev_x / 1000.0;
	pitch += (float)dev_y / 10;
}

void ring(GLUquadric* a, float innerRadius, float outerRadius, float height) {
	//to make ring shape heh 
	glPushMatrix();
	gluCylinder(a, innerRadius, innerRadius, height, 50, 50);
	gluCylinder(a, outerRadius, outerRadius, height, 50, 50);
	gluDisk(a, innerRadius, outerRadius, 50, 50);
	glTranslatef(0, 0, height);
	gluDisk(a, innerRadius, outerRadius, 50, 50);
	glPopMatrix();
}

void Ferris_wheel(float scale, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, 22 + y, z); glScalef(scale, scale, scale);  glPushMatrix();

	//stand
	glTranslatef(0, 0, -13); glColor3ub(150, 150, 180);
	ring(a, 0, 4, 28);

	glTranslatef(0, 0, 1);
	glCallList(3);
	glTranslatef(0, 0, 26);
	glCallList(3);
	glPopMatrix();

	glPushMatrix(); glColor3ub(0, 150, 180); glTranslatef(0, 0, -14);
	ring(a, 0, 2, 30);
	glPopMatrix();

	glPushMatrix();

	glRotatef(wheel, 0, 0, 1);
	glPushMatrix();
	//center part
	glTranslatef(0, 0, -10); glColor3ub(0, 150, 180);
	ring(a, 0, 3, 20);
	glColor3ub(150, 0, 250);
	ring(a, 0, 6, 2.5);
	glTranslatef(0, 0, 20);
	ring(a, 0, 6, 2.5);
	glPopMatrix();

	//beams
	glPushMatrix(); glTranslatef(0, 0, 11); glRotatef(90, -1, 0, 0); glColor3ub(29, 60, 125);
	for (int j = 0; j < 8; j++) {
		glRotatef(45, 0, 1, 0);
		glCallList(1);
	}
	glPopMatrix();

	//rings
	glPushMatrix();
	glTranslatef(0, 0, 10.5); glColor3ub(29, 60, 125);
	ring(a, 22, 24, 1);
	ring(a, 33, 35, 1);
	glTranslatef(0, 0, -20);
	ring(a, 22, 24, 1);
	ring(a, 33, 35, 1);

	//beams connecting the rings
	for (int i = 0; i < 8; i++) {
		glRotatef(45, 0, 0, 1);
		glCallList(2);
	}
	glPopMatrix();
	glPopMatrix();

	//compartments
	glPushMatrix();
	int color[8][3] = {
		77, 227, 175,
		240, 117, 162,
		227, 182, 77,
		114, 83, 230,
		77, 227, 175,
		240, 117, 162,
		227, 182, 77,
		114, 83, 230 };
	glTranslatef(1, 0, 1);
	for (double i = 0; i < 6.28 - 0.78; i += 0.78) {
		glPushMatrix(); glColor3ub(color[int(i / 0.78)][0], color[int(i / 0.78)][1], color[int(i / 0.78)][2]);
		glRotatef(90, 1, 0, 0);
		glTranslatef(34 * cos(i - wheel_compartment), 0, 34 * sin(i - wheel_compartment));
		glCallList(4);
		glPopMatrix();

	}
	glPopMatrix();

	//base	
	int r = 70;
	for (double i = 0; i < 1.5 * 3; i += 1.5) {
		glPushMatrix();
		glTranslatef(0, -47 - i, 1); glScalef(1, 1.5 / r, 0.6); glColor3d(i / 6, 0, 00.25);
		glutSolidCube(r);
		glPopMatrix();
		r += 3;
	}

	//fence
	glPushMatrix();
	glTranslatef(0, -41.25, 20); glColor3ub(90, 100, 100);
	int ee[] = { 8,11, 18, 11, 8 };
	int e = 0;
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < ee[e]; i++) {
			glTranslatef(3.5, 0, 0);
			glCallList(5);
		}
		e++;
		glTranslatef(3.5, 0, 3.5); glRotatef(90, 0, 1, 0);
	}
	glTranslatef(3.5, 0, 0); glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glPopMatrix();
	glPopMatrix();


}
void Ferris_wheel_Lists(void) {
	int list[] = { 1,2,3,4 };

	//beams
	glNewList(list[0], GL_COMPILE);
	glPushMatrix();
	gluCylinder(a, .7, .7, 35, 100, 100);
	glTranslatef(0, 20, 0);
	gluCylinder(a, .7, .7, 35, 100, 100);
	glPopMatrix();
	glEndList();

	//beams connecting the rings
	glNewList(list[1], GL_COMPILE);
	glPushMatrix();
	glTranslatef(34, 0, 0);
	gluCylinder(a, .7, .7, 20, 100, 100);
	glPopMatrix();
	glEndList();

	//legs
	glNewList(list[2], GL_COMPILE);
	glPushMatrix();
	glRotatef(20, 0, 0, 1); glRotatef(90, 1, 0, 0);
	gluCylinder(a, 1.5, 1.5, 55, 4, 100);
	glRotatef(-37, 0, 1, 0);
	gluCylinder(a, 1.5, 1.5, 55, 4, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -22, 0);  glRotatef(45, 0, 0, 1); glRotatef(90, 0.5, 0.5, 0);
	gluCylinder(a, 1.5, 1.5, 13, 4, 100);
	glTranslatef(-8, -8, -5);
	gluCylinder(a, 1.5, 1.5, 24, 4, 100);
	glPopMatrix();
	glEndList();

	//compartment
	glNewList(list[3], GL_COMPILE);
	glPushMatrix();
	ring(a, 0, 6, 10);
	glPopMatrix();
	glEndList();

	//fence
	glNewList(5, GL_COMPILE);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glTranslatef(-0.35, 0, 0); glRotatef(90, 0, 1, 0);
	gluCylinder(a, .35, .35, 4, 100, 100);
	glPopMatrix();
	glEndList();
}

void Swing_Ride(float scale, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z); glScalef(scale, scale, scale); glPushMatrix();

	///base 
	glPushMatrix();
	glTranslatef(0, 0, -25);

	glColor3ub(60, 60, 70);
	glTranslatef(0, 0, 20);
	glRotated(90, 1, 0, 0);
	ring(a, 0, 50, 5);
	glTranslatef(0, 0, 4);
	ring(a, 0, 55, 5);
	glPopMatrix();


	///middle
	glPushMatrix();
	glColor3ub(114, 83, 230);	glTranslatef(0, 50, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 10, 10, 50, 100, 100);

	glPopMatrix();

	glPushMatrix();
	glColor3ub(114, 83, 230); glTranslatef(0, 50, 0);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, 0, 0 - swing_ride);
	gluCylinder(a, 10, 10, 50, 100, 100);
	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 10);
	gluCylinder(a, 10.01, 10.01, 10, 100, 100);
	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 20);
	gluCylinder(a, 10.01, 10.01, 10, 100, 100);
	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 20);
	gluCylinder(a, 10.01, 10.01, 10, 100, 100);
	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 20);
	gluCylinder(a, 10.01, 10.01, 10, 100, 100);

	glPopMatrix();

	///top
	glPushMatrix();
	glColor3ub(77, 227, 175);
	glRotated(90, -1, 0, 0);
	glTranslatef(0, 0, 50 + swing_ride);
	gluCylinder(a, 10, 50, 30, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(240, 117, 162);

	glTranslatef(0, 80 + swing_ride, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.4);
	glutSolidTorus(25, 30, 8, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(43, 145, 240);

	glRotated(90, 1, 0, 0);
	glTranslatef(0, 0, -110 - swing_ride);
	gluCylinder(a, 10, 50, 30, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(227, 182, 77);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, 0, -120 - swing_ride);
	gluCylinder(a, 0, 10, 10, 100, 100);
	glPopMatrix();

	//seats
	glPushMatrix();
	for (double i = 0.78; i < 6.28; i += 0.78) {
		glPushMatrix();
		glRotatef(swing_ride_seats, 0, 1, 0);
		glTranslatef(0, 30 + swing_ride, 0);
		glTranslatef(45 * cos(i), 0, 45 * sin(i));
		glRotatef((swing_ride_seats * swing_ride) / 40, 0, 1, 0);
		glRotatef(swing_ride / 15, 1, 1, 0);
		glCallList(15);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
void Swing_Ride_Lists(void) {
	//seat
	glNewList(15, GL_COMPILE);
	glPushMatrix();
	glColor3ub(255, 231, 143);
	glTranslatef(0, -5, 3);
	glScaled(3, 1, 4);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 167, 220);
	glRotated(90, 1, 0, 0);
	glScaled(3, 1, 4);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(45, 45, 130);
	glRotated(90, -1, 0, 0);
	glTranslatef(2, 0, 0);
	gluCylinder(a, 0.3, 0.3, 50, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, -1, 0, 0);
	glTranslatef(-2, 0, 0);
	gluCylinder(a, 0.3, 0.3, 50, 100, 100);
	glPopMatrix();
	glEndList();

}

void Down_Draft(double scale, int x, int y, int z) {
	glPushMatrix();

	glTranslatef(x, y, z); glScalef(scale, scale, scale);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	glPushMatrix();
	//glPushMatrix();


	//center
	glPushMatrix();
	glTranslatef(0, 0, -40);
	glPushMatrix();
	glColor3ub(150, 150, 180);
	glTranslatef(0, 0, -10);
	glScalef(1, 1, 2.5);
	ring(a, 0, 3, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -46);
	glScalef(2, 2, 1);
	glColor3ub(100, 100, 130);
	ring(a, 0, 6, 2.5);
	glPopMatrix();
	glTranslatef(0, 0, 40);

	gluSphere(a, 6, 50, 50);
	glPopMatrix();


	glRotatef(wheel, 0, 0.3, 1);
	glPushMatrix();

	//beams
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glColor3ub(150, 150, 180);
	for (int i = 0; i < 8; i++) {
		glRotatef(45, 0, 1, 0);
		glCallList(30);
	}
	glPopMatrix();

	//ring
	glColor3ub(100, 100, 130);
	ring(a, 33, 35, 1);
	glPopMatrix();
	glPopMatrix();



	//compartments
	glRotatef(wheel, 0, 0.3, 1);

	glPushMatrix();
	glTranslatef(1, 0, 1);
	glRotatef(90, -1, 0, 0);
	glColor3ub(242, 98, 121);
	for (double i = 0; i < 8; i += 1) {
		glRotatef(45, 0, -1, 0);
		glPushMatrix();

		glTranslatef(34, 0, 0);
		glCallList(4);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
	glColor3ub(60, 60, 70);

	//base	
	int r = 70;
	for (double i = 0; i < 1.5 * 4; i += 1.5) {
		glPushMatrix();
		glTranslatef(0, -47 - i, 1);
		glScalef(1, 1.5 / r, 0.6);
		glutSolidCube(r);
		glPopMatrix();
		r += 3;
	}

	//fence
	glPushMatrix();
	glTranslatef(0, -41.25, 20);
	glColor3ub(90, 100, 100);
	int ee[] = { 8,11, 18, 11, 8 };
	int e = 0;
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < ee[e]; i++) {
			glTranslatef(3.5, 0, 0);
			glCallList(5);
		}
		e++;
		glTranslatef(3.5, 0, 3.5);
		glRotatef(90, 0, 1, 0);
	}
	glTranslatef(3.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glPopMatrix();
	glPopMatrix();

}
void Down_Draft_Lists() {

	//beams
	glNewList(30, GL_COMPILE);
	glPushMatrix();
	gluCylinder(a, .7, .7, 35, 100, 100);
	glPopMatrix();
	glEndList();
}

void Round_up(float scale, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z); glScalef(scale, scale, scale);

	//glRotatef(24,1,0,0);
	//16
	glPushMatrix();
	glTranslatef(-9, 15, 0);
	glRotatef(-35, 1, 0, 1);
	//15
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	//14
	glPushMatrix();

	//13
	glPushMatrix();
	glRotatef(wheel, 0, 0, 1);
	//12
	glPushMatrix();


	//beams
	//7
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glColor3ub(255, 202, 58);
	for (int i = 0; i < 12; i++) {
		glRotatef(40, 0, 1, 0);
		glCallList(40);
	}
	glPopMatrix();
	//7
	//rings
	glColor3ub(3, 4, 97);
	ring(a, 33, 35, 1);
	glPopMatrix();
	//12
	glPopMatrix();

	//compartments
	//6
	glPushMatrix();
	glTranslatef(1, 0, 1);
	glColor3ub(80, 160, 255);
	for (double i = 0.4; i < 6.28; i += 0.5) {
		//5
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(34 * cos(i - wheel_compartment), 0, 34 * sin(i - wheel_compartment));
		glCallList(41);
		glPopMatrix();
		//5
	}

	glPopMatrix();
	//6
	glPopMatrix();
	//13
	glPopMatrix();
	//14
	glPopMatrix();
	//15
	glPopMatrix();
	//16
	glColor3ub(60, 60, 70);
	//base	
	int r = 70;
	for (double i = 0; i < 1.5 * 4; i += 1.5) {
		//4
		glPushMatrix();
		glTranslatef(0, -47 - i, 1);
		glScalef(1, 1.5 / r, 0.6);
		glutSolidCube(r);
		glPopMatrix();
		//4
		r += 3;
	}

	//fence
	//3
	glPushMatrix();
	glTranslatef(0, -41.25, 20);
	glColor3ub(90, 100, 100);
	int ee[] = { 8,11, 18, 11, 8 };
	int e = 0;
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < ee[e]; i++) {
			glTranslatef(3.5, 0, 0);
			glCallList(42);
		}
		e++;
		glTranslatef(3.5, 0, 3.5);
		glRotatef(90, 0, 1, 0);
	}
	glTranslatef(3.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glPopMatrix();
	//3

	//center too
	glTranslatef(-20, 0, 0);
	glRotatef(-90, 1, 0, 0);
	//11
	glPushMatrix();
	glTranslatef(0, 0, -40);
	//9
	glPushMatrix();
	glColor3ub(3, 4, 97);
	glTranslatef(0, 0, -10);
	glScalef(1, 1, 2.5);
	ring(a, 0, 3, 20);
	glPopMatrix();
	//9
	glTranslatef(2, -1., 39);
	glColor3ub(255, 202, 58);
	ring(a, 0, 6, 2.5);
	glTranslatef(0, 0, -2);
	glColor3ub(3, 4, 97);
	ring(a, 0, 6, 2.5);
	glTranslatef(0, 0, -2);
	glColor3ub(255, 202, 58);
	ring(a, 0, 6, 2.5);
	glPopMatrix();
	//11
	//2
	glPushMatrix();
	glColor3ub(3, 4, 97);
	glTranslatef(30, 0, -50);
	glScalef(2, 1, 2.5);
	glRotatef(-34.5, 0, 1, 0);
	gluCylinder(a, 4, 0, 25, 50, 50);
	glPopMatrix();
	//2

	//1
	glPushMatrix();
	glColor3ub(3, 4, 97);
	glRotatef(35, 0, 1, 0);
	glTranslatef(1, 0, 15);
	glScalef(1, 1, 5);

	glutSolidSphere(4, 50, 50);
	glPopMatrix();
	//1
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
void Round_up_Lists() {
	//beams
	glNewList(40, GL_COMPILE);
	glPushMatrix();
	gluCylinder(a, .5, .5, 35, 100, 100);
	glPopMatrix();
	glEndList();

	//compartment
	glNewList(41, GL_COMPILE);
	glPushMatrix();
	glScalef(0.4, 1.5, 0.4);
	glutSolidSphere(6, 50, 50);
	glPopMatrix();
	glEndList();

	//fence (inside initGL)
	glNewList(42, GL_COMPILE);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glTranslatef(-0.35, 0, 0); glRotatef(90, 0, 1, 0);
	gluCylinder(a, .35, .35, 4, 100, 100);
	glPopMatrix();
	glEndList();
}


void Ship(float scale, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z); glScalef(scale, scale, scale);

	//base	
	int r = 70;
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5); glColor3ub(50, 50, 50);
	for (double i = 0; i < 1.5 * 3; i += 1.5) {
		glPushMatrix();
		glTranslatef(0, -25 - i, -19); glScalef(1, 1.5 / r, 0.6);
		glutSolidCube(r);
		glPopMatrix();
		r += 3;
	}
	glPopMatrix();


	//fence
	glPushMatrix();
	glTranslatef(0, -10, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3ub(120, 120, 120);
	int ee[] = { 8,11, 18, 11, 8 };
	int e = 0;
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < ee[e]; i++) {
			glTranslatef(3.5, 0, 0);
			glCallList(5);
		}
		e++;
		glTranslatef(3.5, 0, 3.5); glRotatef(90, 0, 1, 0);
	}
	glTranslatef(3.5, 0, 0); glRotatef(90, 1, 0, 0);
	gluCylinder(a, .35, .35, 5, 100, 100);
	glPopMatrix();

	//Front Legs
	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(0, 5, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(30, 0, 1, 0);
	gluCylinder(a, 0.5, 0.5, 20, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(-30, 0, 1, 0);
	gluCylinder(a, 0.5, 0.5, 20, 100, 100);
	glPopMatrix();

	//Bridge
	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(0, 5, -19);
	gluCylinder(a, 0.5, 0.5, 20, 100, 100);
	glPopMatrix();

	//Back Legs
	glPushMatrix();
	glTranslatef(0, 5, -18);
	glRotatef(90, 1, 0, 0);
	glRotatef(30, 0, 1, 0);
	gluCylinder(a, 0.5, 0.5, 20, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, -18);
	glRotatef(90, 1, 0, 0);
	glRotatef(-30, 0, 1, 0);
	gluCylinder(a, 0.5, 0.5, 20, 100, 100);
	glPopMatrix();

	glTranslatef(0, 5, 0);
	glRotatef(ship_angle, 0, 0, 1);

	//Ship body
	glPushMatrix();
	glTranslatef(0, -10, -10);
	glEnable(GL_CLIP_PLANE0);
	double j[] = { 0,-1,0,0 };
	glClipPlane(GL_CLIP_PLANE0, j);
	glScalef(1.5, 1, 0.75);
	glColor3ub(114, 83, 230);
	glutSolidSphere(5, 8, 8);
	glColor3ub(240, 117, 162);
	glScalef(1, 1, 9);
	glutSolidCube(1);
	glTranslatef(-2, 0, 0);
	glutSolidCube(0.5);
	glTranslatef(4, 0, 0);
	glutSolidCube(0.5);
	glTranslatef(-2, 0, 0);
	glScalef(1, 1, 1 / 9);
	glDisable(GL_CLIP_PLANE0);
	glColor3ub(227, 182, 77);
	glTranslatef(0, 10, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.5, 0.5, 14.5, 100, 100);
	glPopMatrix();


	glPopMatrix();

}


void chair() {

	glPushMatrix();
	glColor3ub(0, 0, 60);
	glTranslatef(0, -3, 0);
	glScalef(0.5, 0.05, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(1.25, -4.5, -1.25);
	glScalef(0.05, 0.5, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(1.25, -4.5, 1.25);
	glScalef(0.05, 0.5, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(-1.25, -4.5, -1.25);
	glScalef(0.05, 0.5, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(-1.25, -4.5, 1.25);
	glScalef(0.05, 0.5, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	//Back
	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(-1.25, -1.35, -1.25);
	glScalef(0.05, 0.55, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(1.25, -1.35, -1.25);
	glScalef(0.05, 0.55, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0, 0, -1.25);
	glScalef(0.05, 0.55, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-0.75, 0, -1.25);
	glScalef(0.05, 0.55, 0.05);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-1.5, 0, -1.25);
	glScalef(0.05, 0.55, 0.05);
	glutSolidCube(6);
	glPopMatrix();
	return;
}
void tableAndChairs(float scale) {
	glScalef(scale, scale, scale);
	//Tabletop
	glPushMatrix();
	glColor3ub(250, 205, 82);
	glScalef(1.5, 0.1, 1.5);
	glutSolidCube(6);
	glPopMatrix();

	//Leg
	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(0, -3, 0);
	glScalef(0.1, 1, 0.1);
	glutSolidCube(6);
	glPopMatrix();

	//Base
	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(0, -6, 0);
	glScalef(0.5, 0.05, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	//Chairs
	glPushMatrix();
	glTranslatef(0, 0, -5);
	chair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 5);
	glRotatef(180, 0, 1, 0);
	chair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 0);
	glRotatef(-90, 0, 1, 0);
	chair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glRotatef(90, 0, 1, 0);
	chair();
	glPopMatrix();
}
void cornerBar() {
	GLUquadricObj* b = gluNewQuadric();

	glEnable(GL_CLIP_PLANE1);
	double i[] = { 1,0,0,0 };
	glClipPlane(GL_CLIP_PLANE1, i);

	glEnable(GL_CLIP_PLANE2);
	double j[] = { 0,0,1,0 };
	glClipPlane(GL_CLIP_PLANE2, j);

	glPushMatrix();
	glColor3ub(0, 0, 60);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 0.05);
	glutSolidTorus(1.5, 6, 10, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glRotatef(90, 1, 0, 0);
	gluCylinder(b, 7.5, 7.5, 4, 100, 100);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE2);
	glDisable(GL_CLIP_PLANE1);
}
void cafe(float scale) {
	glScalef(scale, scale, scale);

	glPushMatrix();
	glColor3ub(0, 40, 216);
	glTranslatef(0, -5.4, 6);
	glScalef(5, 0.2, 2.5);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 180, 216);
	glScalef(5, 2.5, 0.2);
	glutSolidCube(5);
	glPopMatrix();

	glColor3ub(0, 180, 255);
	glPushMatrix();
	glTranslatef(-12, 0, 6);
	glScalef(0.2, 2.5, 2.5);
	glutSolidCube(5);
	glPopMatrix();

	glColor3ub(0, 180, 255);
	glPushMatrix();
	glTranslatef(12, 0, 6);
	glScalef(0.2, 2.5, 2.5);
	glutSolidCube(5);
	glPopMatrix();

	glColor3ub(0, 180, 216);
	glPushMatrix();
	glTranslatef(0, 6, 6);
	glScalef(5, 0.2, 2.5);
	glutSolidCube(5);
	glPopMatrix();

	glColor3ub(3, 4, 94);
	glPushMatrix();
	glColor3ub(0, 180, 216);
	glTranslatef(0, -6, 6);
	glScalef(5, 0.2, 2.5);
	glutSolidCube(5);
	glPopMatrix();

	//Front Wall
	glPushMatrix();
	glColor3ub(0, 180, 216);
	glTranslatef(3.5, 0, 12);
	glScalef(3.5, 2.5, 0.2);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(3, 4, 94);
	glTranslatef(0, 3, 12);
	glScalef(5, 1.25, 0.2);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0, 0);
	glScalef(1.2, 0.8, 1.2);
	glTranslatef(0, -3.5, 0);
	cornerBar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3, 4);
	tableAndChairs(0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5, -3, 4);
	tableAndChairs(0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -3, 9);
	tableAndChairs(0.4);
	glPopMatrix();

}


void Lamppost() {
	glNewList(21, GL_COMPILE);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glPushMatrix();

	glColor3ub(20, 20, 100);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 1.5, 1.5, 6, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(0, 0, 60);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 2, 2, 4, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(0, 0, 60);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 1, 1, 10, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(20, 20, 100);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 0.5, 0.5, 31, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(20, 20, 100);
	glRotated(90, 0, -1, 0);
	glTranslatef(0, 30, -8);
	gluCylinder(a, 0.5, 0.5, 16, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(20, 20, 100);
	glTranslatef(-7, 24, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 0.5, 0.5, 6, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(20, 20, 100);
	glTranslatef(7, 24, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(a, 0.5, 0.5, 6, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(255, 255, 103);
	glTranslatef(-7, 24, 0);
	glutSolidSphere(2.8, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(255, 255, 103);
	glTranslatef(7, 24, 0);
	glutSolidSphere(2.8, 100, 100);


	glPopMatrix();
	glPopMatrix();


	glEndList();

}
void Bench() {
	glNewList(17, GL_COMPILE);	glPushMatrix();


	glTranslatef(0, -1, 0);
	glScalef(0.03, 0.09, 0.09);

	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(30, 5, 71);
	glScaled(0.5, 2, 0.4);
	glutSolidCube(6);
	glTranslatef(-120, 0, 0);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(0, 8, 71);
	glScaled(13, 0.3, 0.2);
	glutSolidCube(6);
	glTranslatef(0, -11, 0);
	glColor3ub(136, 99, 72);
	glutSolidCube(6);
	glTranslatef(0, -11, 0);
	glColor3ub(250, 205, 82);
	glutSolidCube(6);
	glPopMatrix();


	glPushMatrix();
	glColor3ub(136, 99, 72);
	glTranslatef(0, -2, 78);
	glRotated(90, 1, 0, 0);
	glScaled(12, 2.5, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(34, -8, 84);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(-34, -8, 84);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(34, -8, 72);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(250, 205, 82);
	glTranslatef(-34, -8, 72);
	glScaled(0.5, 1.5, 0.5);
	glutSolidCube(6);
	glPopMatrix();
	glPopMatrix();

	glEndList();

}
void Ticket_Booth() {
	glNewList(90, GL_COMPILE);

	glPushMatrix();
	glColor3ub(77, 227, 175);
	glTranslatef(0, 0, 70);
	glScaled(12, 8, 0.5);
	glutSolidCube(6);


	glPopMatrix();
	glPushMatrix();

	glColor3ub(114, 83, 230);
	glTranslatef(0, 25, 95);
	glRotated(90, -1, 0, 0);
	glScaled(12, 9, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(0, -22, 92);
	glRotated(90, -1, 0, 0);
	glScaled(12, 7, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(36, 0, 92);
	glRotated(90, 0, 1, 0);
	glScaled(8, 8, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(-36, 0, 92);
	glRotated(90, 0, 1, 0);
	glScaled(8, 8, 0.5);
	glutSolidCube(6);

	glPopMatrix();
	glPushMatrix();
	glColor3ub(254, 185, 129);

	glTranslatef(0, -12, 115);
	glScaled(4, 4, 0.5);
	glutSolidCube(6);
	glColor3ub(251, 230, 132);

	glTranslatef(6, 0, 0);
	glutSolidCube(6);
	glTranslatef(-12, 0, 0);
	glutSolidCube(6);

	glPopMatrix();

	glPushMatrix();
	glColor3ub(240, 117, 162);
	glTranslatef(0, 0, 115);
	glRotated(90, -1, 0, 0);
	glScaled(12, 2, 0.5);
	glutSolidCube(6);
	glPopMatrix();
	glEndList();

}



void Tree() {
	int list[] = { 6,7,8,9 };
	//array to change list numbers more easily 
	//to call tree model 1 use glCallList(third element);
	//to call tree model 2 use glCallList(last element);

	//branch
	glNewList(list[0], GL_COMPILE);
	glPushMatrix();
	glColor3ub(70, 50, 0);
	gluCylinder(a, .8, .8, 6, 100, 100);
	glColor3ub(0, 110, 20); glTranslatef(-1, 0, 12); glScalef(8, 10, 8);
	glutSolidIcosahedron();
	glPopMatrix();
	glEndList();

	//main branch
	glNewList(list[1], GL_COMPILE);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);  glColor3ub(70, 50, 0);
	gluCylinder(a, .8, 1.5, 40, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glScalef(12, 10, 10); glColor3ub(0, 110, 20);
	glutSolidIcosahedron();
	glPopMatrix();
	glEndList();

	//tree1
	glNewList(list[2], GL_COMPILE);
	glCallList(list[1]);
	glPushMatrix();
	glTranslatef(0, -15, 0); glRotatef(90, 1, 1, 0); glRotatef(120, 0, 1, 0);
	glCallList(list[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -19, 0); glRotatef(90, 1, 0, 0); glRotatef(-120, 0, 1, 0);
	glCallList(list[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -20, 0); glRotatef(90, 1, 0, 0); glRotatef(150, 0, 1, 0);
	glCallList(list[0]);
	glPopMatrix();
	glEndList();

	//tree2
	glNewList(list[3], GL_COMPILE);
	glCallList(list[1]);
	glPushMatrix();
	glTranslatef(0, -15, 0); glRotatef(90, 1, 1, 0); glRotatef(120, 0, 1, 0);
	glCallList(list[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -19, 0); glRotatef(90, 1, 0, 0); glRotatef(120, 0, 1, 0);
	glCallList(list[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -21, 0); glRotatef(180, 1, 1, 0); glRotatef(150, 0, 1, 0); glScalef(1, 1, 1);
	glCallList(list[0]);
	glPopMatrix();
	glEndList();
}

void Train_Lists(void) {
	////train 
	glNewList(10, GL_COMPILE);
	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslatef(-25, -10, 60);
	gluDisk(a, 0, 3.7, 100, 100);
	glPopMatrix();///// for one of the weel

	glPushMatrix();/////
	glColor3ub(50, 50, 50);
	glTranslatef(-25, -10, 60);
	gluCylinder(a, 3, 3, 9, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslatef(25, -10, 60);
	gluDisk(a, 0, 3.7, 100, 100);
	glPopMatrix();/// for one of weel

	glPushMatrix();///
	glColor3ub(50, 50, 50);
	glTranslatef(25, -10, 60);
	gluCylinder(a, 3, 3, 9, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslatef(-25, -10, 124);
	gluDisk(a, 0, 3.7, 100, 100);
	glPopMatrix();/// for one of weel

	glPushMatrix();///
	glColor3ub(50, 50, 50);
	glTranslatef(-25, -10, 115);
	gluCylinder(a, 3, 3, 9, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 220, 220);
	glTranslatef(25, -10, 124);
	gluDisk(a, 0, 3.7, 100, 100);
	glPopMatrix();/// for one of weel

	glPushMatrix();///
	glColor3ub(50, 50, 50);
	glTranslatef(25, -10, 115);
	gluCylinder(a, 3, 3, 9, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 68);
	glScaled(12, 4, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(227, 182, 77);
	glTranslatef(0, -10, 92);
	glRotated(90, -1, 0, 0);
	glScaled(12, 8, 0.5);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(227, 182, 77);
	glTranslatef(36, 0, 92);
	glRotated(90, 0, 1, 0);
	glScaled(8, 4, 0.5);
	glutSolidCube(6);


	glPopMatrix();
	glPushMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3ub(240, 117, 162);
	glTranslatef(30, 5, 92);
	glRotated(90, 0, 1, 0);
	glRotated(20, 1, 0, 0);
	glScaled(7, 6, 1);
	glutSolidCube(6);


	glPopMatrix();
	glPushMatrix();

	glColor3ub(77, 227, 175);
	glTranslatef(0, 5, 92);
	glRotated(90, 0, 1, 0);
	glRotated(20, 1, 0, 0);
	glScaled(7, 6, 1);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(20, 20, 180);
	glTranslatef(-36, 0, 92);
	glRotated(90, 0, 1, 0);
	glScaled(8, 4, 0.5);
	glutSolidCube(6);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(43, 145, 240);
	glTranslatef(0, 0, 115);
	glScaled(12, 4, 0.5);
	glutSolidCube(6);//////////


	glPopMatrix();
	glPushMatrix();

	glTranslatef(-25, -10, 122);/// first weel
	glColor3ub(50, 50, 50);
	glutSolidTorus(3, 6, 100, 100);


	glPopMatrix();
	glPushMatrix();

	glTranslatef(25, -10, 122);/// 2 wheel
	glColor3ub(50, 50, 50);
	glutSolidTorus(3, 6, 100, 100);


	glPopMatrix();
	glPushMatrix();

	glTranslatef(-25, -10, 62);/// 3 weel
	glColor3ub(50, 50, 50);
	glutSolidTorus(3, 6, 100, 100);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(25, -10, 62);/// 4 weel
	glColor3ub(50, 50, 50);
	glutSolidTorus(3, 6, 100, 100);

	glPopMatrix();

	glEndList();
	////////////////////////////////////////////////////////////////////
	glNewList(12, GL_COMPILE);
	glPushMatrix();

	glScalef(0.1, 0.1, 0.1);


	glPushMatrix();

	glCallList(10);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(50, 50, 50);
	glTranslatef(-65, -8, 92);
	glRotated(90, 0, 1, 0);
	gluCylinder(a, 3, 3, 30, 100, 100);


	glPopMatrix();
	glPushMatrix();

	glTranslatef(-95, 0, 0);
	glCallList(10);

	glPopMatrix();
	glPushMatrix();

	glColor3ub(50, 50, 50);
	glTranslatef(-160, -8, 92);
	glRotated(90, 0, 1, 0);
	gluCylinder(a, 3, 3, 30, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-190, 0, 0);
	glCallList(10);
	glPopMatrix();	glPopMatrix();
	glEndList();

}
void Train(float scale, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z); glScalef(scale, scale, scale); glPushMatrix();

	glRotatef(90, 1, 0, 0); glColor3ub(55, 55, 55);
	glTranslatef(0, 0, -0.3);

	ring(a, 59.8, 60, 1);
	ring(a, 56.8, 57, 1);

	glPopMatrix();
	glPopMatrix();
	glRotatef(train, 0, -1, 0);
	glPushMatrix();
	glTranslatef(10, 2, 48);
	glCallList(12);
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();


}

void globeStatue(float scale) {
	GLUquadricObj* a = gluNewQuadric();
	glPushMatrix();
	glScalef(scale, scale, scale);

	glPushMatrix();
	glLineWidth(2);
	glRotatef(90, 1, 0, 0);
	glRotatef(train, 0, 0, 1);
	glColor3ub(43, 145, 240);
	glutWireSphere(10, 40, 10);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glColor3ub(250, 205, 82);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.25, 0.25, 22, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -12, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 2, 2, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -12, 0);
	glScalef(1, 0, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();
	glPopMatrix();

}


void InitGL(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.4f, 0.8f, 0.9f, 1.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glutSetCursor(GLUT_CURSOR_NONE);
}
void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 0.4,0.4,0.4,1 }; //
	GLfloat s[] = { 1,0,0,1 }; // 
	GLfloat aa[] = { 0.2,0.2,0.2,1 }; // 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	glLightfv(GL_LIGHT0, GL_AMBIENT, aa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);

	if (pitch >= 150)
		pitch = 150;
	if (pitch <= -150)
		pitch = -150;
	//gluLookAt(EX, EY, EZ, EX + cos(-yaw), EY + pitch / 100, EZ + sin(-yaw), 0, 1, 0);


	CX = EX + cos(th-3.14/2);
	CZ = EZ + sin(th-3.14 / 2);
	CY = EY - ph+0.2;
	gluLookAt(EX, EY, EZ, CX, CY, CZ, 0, 1, 0);
	glTranslatef(0, -5, -60);
	glRotatef(180, 0, 1, 0);

	if (asd == 1) {
		glDisable(GL_LIGHTING);

	}

	//glRotatef(90, 0, 0, 1);
	//glTranslatef(0, -200, 40);

	glPushMatrix();
	GLfloat p1[] = { train,300 + train,-train,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, p1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPopMatrix();
	//tree

	glPushMatrix();
	glTranslatef(18, 13, 18);
	glScalef(0.3, 0.3, 0.3);
	glCallList(8);
	glTranslatef(0, -15, -75);
	glScalef(0.7, 0.7, 0.7);
	glCallList(9);
	glTranslatef(-33, -0, -130);
	glCallList(8);
	glTranslatef(-5, -0, -35);
	glCallList(9);
	glTranslatef(-95, -0, -0);
	glCallList(9);
	glTranslatef(0, -0, 30);
	glCallList(8);
	glTranslatef(-49, -0, 95);

	glCallList(9);

	glPopMatrix();


	//train
	glPushMatrix();
	Train(1, 0, 0, 0);
	glPopMatrix();


	//ticket booth
	glPushMatrix();
	glTranslatef(15, 2, 20);
	glScaled(0.1, 0.1, -0.1);
	glRotated(-40, 0, 1, 0);
	glCallList(90);
	glPopMatrix();


	//statue
	glPushMatrix();
	glTranslatef(0, 2.9, 0);
	globeStatue(0.2);
	glPopMatrix();


	//benches
	glPushMatrix();
	glTranslatef(17, 2, 12);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1, -1);
	glCallList(17);
	glTranslatef(23, 0, 2);
	glCallList(17);
	glTranslatef(22, 0, 5);
	glCallList(17);
	glTranslatef(0, 0, 20);
	glScalef(1, 1, -1);
	glCallList(17);

	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, -1, 0);
	glTranslatef(21, 2, -10);
	glCallList(17);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-21, 2, -10);
	glCallList(17);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 2, 15);
	glRotatef(90, 0, 1, 0);
	glTranslatef(23, 0, 0);
	glTranslatef(23, 0, -5);
	glTranslatef(0, 0, -15);
	glTranslatef(-33, 0, -9);
	glCallList(17);
	glTranslatef(-20, 0, 5);
	glRotatef(50, 0, 1, 0);
	glCallList(17);
	glPopMatrix();

	//ground
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3ub(81, 176, 95);
	ring(a, 0, 200, 2);
	glPopMatrix();

	//road
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslatef(0, 0.15, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.5, 0.5, 1);

	glBegin(GL_POLYGON);
	glVertex3d(10, -60, 0); glVertex3d(10, -80, 0); glVertex3d(-10, -80, 0); glVertex3d(-10, -60, 0); glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-10, -60, 0); glVertex3d(10, -60, 0); glVertex3d(20, -40, 0); glVertex3d(-30, -20, 0); glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-20, -30, 0); glVertex3d(-30, -20, 0); glVertex3d(-30, 0, 0); glVertex3d(-30, 10, 0);
	glVertex3d(-30, 30, 0); glVertex3d(-10, 40, 0);	glVertex3d(10, 40, 0); glVertex3d(20, 30, 0);
	glVertex3d(20, -10, 0); glVertex3d(20, -20, 0);	glVertex3d(20, -40, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-20, -30, 0); glVertex3d(-60, -10, 0); glVertex3d(-60, 10, 0); glVertex3d(-30, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-30, 10, 0); glVertex3d(-40, 20, 0); glVertex3d(-60, 30, 0); glVertex3d(-50, 40, 0);
	glVertex3d(-30, 30, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-10, 40, 0); glVertex3d(-10, 60, 0); glVertex3d(10, 60, 0); glVertex3d(10, 40, 0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3d(20, 30, 0); glVertex3d(30, 20, 0); glVertex3d(30, 0, 0); glVertex3d(20, -10, 0);		glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(30, 20, 0); glVertex3d(50, 10, 0); glVertex3d(60, 10, 0);
	glVertex3d(60, 0, 0); glVertex3d(30, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(20, -20, 0); glVertex3d(40, -30, 0); glVertex3d(40, -40, 0); glVertex3d(20, -40, 0);
	glEnd();

	glPopMatrix();

	//lamps
	glPushMatrix();
	glTranslatef(6, 0, 20);
	glCallList(21);
	glTranslatef(-12, 0, -1);
	glCallList(21);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0, 15);
	glRotatef(90, 0, 1, 0);
	glTranslatef(22, 0, 0);
	glCallList(21);
	glTranslatef(22, 0, -5);
	glCallList(21);
	glTranslatef(0, 0, -15);
	glCallList(21);
	glTranslatef(-33, 0, -8);
	glCallList(21);
	glTranslatef(-15, 0, 2);
	glRotatef(50, 0, 1, 0);
	glPopMatrix();

	//wheel
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	Ferris_wheel(0.5, 0, 3, -35);
	glPopMatrix();

	//swing ride
	glPushMatrix();
	Swing_Ride(0.2, -30, 1, 0);
	glPopMatrix();

	//down draft
	glPushMatrix();
	glTranslatef(20, 13, -20);
	glScalef(1, 1, 1);
	glRotatef(105, 0, 1, 0);
	Down_Draft(0.25, 0, 0, 0);
	glPopMatrix();

	//ship
	glPushMatrix();
	glTranslatef(-15, 10, -30);
	glRotatef(150, 0, 1, 0);
	Ship(0.8, 0, 0, 0);
	glPopMatrix();


	//cafe	
	glPushMatrix();
	glTranslatef(35, 5, 8);
	glScalef(-1, 1, -1);
	glRotatef(100, 0, 1, 0);
	cafe(1);
	glPopMatrix();

	//round up
	glPushMatrix();
	glTranslatef(-30, 10, 20);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(30, 0, -1, 0);
	Round_up(1, 0, 0, 0);
	glPopMatrix();

	glPopMatrix();
	glFlush();
}



void FunctionCalls(void) {
	Ferris_wheel_Lists();
	Swing_Ride_Lists();
	Tree();
	Train_Lists();
	Ticket_Booth();
	Bench();
	Down_Draft_Lists();
	Round_up_Lists();
	Lamppost();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Theme Park");
	InitGL();
	FunctionCalls();
	timer(0);
	glutPassiveMotionFunc(passive_motion);
	glutReshapeFunc(ReSizeGLScene);
	glutDisplayFunc(DrawGLScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMainLoop();
	return 0;
}