#pragma once
#include <GL/glut.h>
#include <math.h>
#include <cmath>
int wheel = 0;
double wheel_compartment = 0;


float swing_ride_seats = 1;
float swing_ride = 0;
float i = 0;

GLUquadricObj* a = gluNewQuadric();



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

	glTranslatef(x, y, z); glScalef(scale, scale, scale);  glPushMatrix();

	//stand
	glTranslatef(0, 0, -13); glColor3ub(100, 150, 180);
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
	glPushMatrix(); glTranslatef(0, 0, 11); glRotatef(90, -1, 0, 0); glColor3ub(120, 0, 120);
	for (int i = 0; i < 8; i++) {
		glRotatef(45, 0, 1, 0); glCallList(1);
	}
	glPopMatrix();

	//rings
	glPushMatrix();
	glTranslatef(0, 0, 10.5); glColor3ub(0, 100, 60);
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
	glTranslatef(1, 0, 1); glColor3ub(150, 0, 250);
	for (double i = 0.78; i < 6.28; i += 0.78) {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);	glTranslatef(34 * cos(i - wheel_compartment), 0, 34 * sin(i - wheel_compartment));
		glCallList(4);
		glPopMatrix();
	}
	glPopMatrix();

	//base	
	int r = 70;
	for (double i = 0; i < 1.5 * 4; i += 1.5) {
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

}
void Ferris_wheel_Lists(void) {
	int list[] = { 1,2,3,4 };

	//beams
	glNewList(list[0], GL_COMPILE);
	glPushMatrix();
	gluCylinder(a, .5, .5, 35, 100, 100);
	glTranslatef(0, 20, 0);
	gluCylinder(a, .5, .5, 35, 100, 100);
	glPopMatrix();
	glEndList();

	//beams connecting the rings
	glNewList(list[1], GL_COMPILE);
	glPushMatrix();
	glTranslatef(34, 0, 0);
	gluCylinder(a, .5, .5, 20, 100, 100);
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
}

void Swing_Ride(float scale, float x, float y, float z) {
	//mamo's code
	glTranslatef(x, y, z); glScalef(scale, scale, scale); glPushMatrix();

	///base 
	glPushMatrix();
	glColor3ub(200, 40, 20);
	glRotated(90, 1, 0, 0);
	ring(a, 0, 50, 10);
	glPopMatrix();


	///middle
	glPushMatrix();
	glColor3ub(220, 40, 0);	glTranslatef(0, 50, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 10, 10, 50, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 40, 0); glTranslatef(0, 50, 0);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, 0, 0 - swing_ride);
	gluCylinder(a, 10, 10, 50, 100, 100);
	glPopMatrix();

	///top
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glRotated(90, -1, 0, 0);
	glTranslatef(0, 0, 50 + swing_ride);
	gluCylinder(a, 10, 50, 30, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(20, 200, 220);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, 0, -110 - swing_ride);
	gluCylinder(a, 10, 50, 30, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(0, 255, 0);
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
		glCallList(1);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

}
void Swing_Ride_Lists(void) {
	//seat
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glColor3ub(20, 200, 220);
	glTranslatef(0, -5, 3);
	glScaled(3, 1, 4);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(220, 120, 255);
	glRotated(90, 1, 0, 0);
	glScaled(3, 1, 4);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(20, 120, 255);
	glRotated(90, -1, 0, 0);
	glTranslatef(2, 0, 0);
	gluCylinder(a, 0.5, 0.5, 50, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, -1, 0, 0);
	glTranslatef(-2, 0, 0);
	gluCylinder(a, 0.5, 0.5, 50, 100, 100);
	glPopMatrix();
	glEndList();

}