#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <chrono>
#include <cmath>
#include "grayArea.h"


GrayArea::GrayArea(float posX, float posY, float maxY, int speed){
	this->posX = posX;
	this->posY = posY;
	this->maxY = maxY;
	this->color = {.5, .5, .5};
	this->speed = speed;
}
    	
GrayArea::~GrayArea(){}
    	
void GrayArea::draw() {
	float x = getX();
	float y = getY();
    	glColor3f(color[0], color[1], color[2]); 
	
    	glBegin(GL_QUADS);
    	glVertex2f(x-width,y-height);
    	glVertex2f(x+width,y-height);
    	glVertex2f(x+width,y+height);
    	glVertex2f(x-width,y+height);
    	glEnd();
    	
    	
}

void GrayArea::move() {
	setY(getY() + step);
	
	int y = getY();
	
	if(y-height<0){
		step *= -1;
		setRandomSpeed();
		setY(height);
	}else if(y+height>maxY){
		step *= -1;
		setRandomSpeed();
		setY(maxY-height);
	}
}


thread GrayArea::movingThread(){
	return thread(&GrayArea::movement, this);
}


void GrayArea::movement(){
	while(isAlive()){
		move();
		this_thread::sleep_for(chrono::milliseconds(getSpeed()));
	}
}

void GrayArea::setX(float value){posX = value;}


float GrayArea::getX(){return posX;}

	
void GrayArea::setY(float value){posY = value;}


float GrayArea::getY(){return posY;}


void GrayArea::setSpeed(int value){speed = value;}	


void GrayArea::setRandomSpeed(){
	int randomValue = int(float(random()) /RAND_MAX * (minSpeed - maxSpeed) + maxSpeed);
	
	setSpeed(randomValue);
}


int GrayArea::getSpeed(){return speed;}


bool GrayArea::isAlive(){return alive;}

void GrayArea::kill(){alive = false;}

int GrayArea::getHeight(){return height;}
