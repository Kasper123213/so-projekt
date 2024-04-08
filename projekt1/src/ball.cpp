#include <iostream>
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
    	
    	//cout<<this->color[0]<<" "<<this->color[1]<<" "<<this->color[2]<<endl;
}

Ball::~Ball() {}

bool Ball::move() {
	bool bounced = false;
	
	posX += speedX;
    	if(posX>=maxX or posX<=0) {
    		speedX *= -1;
    		bounced = true;
    	}
    
    	posY += speedY;
    	if(posY>=maxY or posY<=0){
    		speedY *= -1;
    		bounced = true;
    	}
    	if(bounced){
    		bounces++;
    		if (bounces>=maxBounces) return false;
    	}
    	return true;
}

void Ball::draw() {
	
    	cout<<this->color[0]<<" "<<this->color[1]<<" "<<this->color[2]<<endl;
    	glColor3f(color[0], color[1], color[2]); 
	glTranslatef(posX, posY, 0.0);
    	gluDisk(gluNewQuadric(), 0, radius, 50, 1);
    	glTranslatef(-posX, -posY, 0.0);
}
