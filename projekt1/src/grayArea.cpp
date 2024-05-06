#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <chrono>
#include <cmath>
#include "grayArea.h"


GrayArea::GrayArea(float posX, float posY, float maxY, float speed){
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
    	glVertex2f(x-size,y-size);
    	glVertex2f(x+size,y-size);
    	glVertex2f(x+size,y+size);
    	glVertex2f(x-size,y+size);
    	glEnd();
    	
    	
}

void GrayArea::move() {
	setY(getY() + getSpeed());
	
	int y = getY();
	
	if(y-size<0){
		setRandomSpeed();
		setSpeed(getSpeed() * (-1));
		setY(size);
	}else if(y+size>maxY){
		setRandomSpeed();
		setSpeed(getSpeed() * (-1));
		setY(maxY-size);
	}
}


thread GrayArea::movingThread(){
	return thread(&GrayArea::movement, this);
}


void GrayArea::movement(){
	while(isAlive()){
		move();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void GrayArea::setX(float value){posX = value;}


float GrayArea::getX(){return posX;}

	
void GrayArea::setY(float value){posY = value;}


float GrayArea::getY(){return posY;}


void GrayArea::setSpeed(float value){speed = value;}	


void GrayArea::setRandomSpeed(){
	float randomValue = float(random()) /RAND_MAX * (maxSpeed - minSpeed) + minSpeed;
	if (getSpeed()<0) randomValue *= -1;
	
	setSpeed(randomValue);
}


float GrayArea::getSpeed(){return speed;}


bool GrayArea::isAlive(){return alive;}

void GrayArea::kill(){alive = false;}
