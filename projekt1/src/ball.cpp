#include <GL/glut.h>
#include "ball.h"

using namespace std;

Ball::Ball(float maxX, float maxY, float posX, float posY, float speedX, float speedY, float* color, int nr) {
    	this->maxX = maxX;
	this->maxY = maxY;
    	this->posX = posX;
    	this->posY = posY;
    	this->speedX = speedX;
    	this->speedY = speedY;
    	this->color = color;
    	this->nr = nr;
    	radius = 10;
}

Ball::~Ball() {}

void Ball::move() {
	posX += speedX;
    	if(posX>=maxX or posX<=0) speedX *= -1;
    
    	posY += speedY;
    	if(posY>=maxY or posY<=0) speedY *= -1;
}

void Ball::draw() {
    	glColor3f(0.5, 1.0, 0.0); 
	glTranslatef(posX, posY, 0.0);
    	gluDisk(gluNewQuadric(), 0, radius, 50, 1);
    	// Rysujemy napis "1" na kole
    
    	glColor3f(0.5, 0.0, 0.0); 
    	glRasterPos2f(0.0 , 0.0 );
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 5);
    	//glTranslatef(-translateX, -translateY, 0.0);
}
