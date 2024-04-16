#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <chrono>
#include "ball.h"


Ball::Ball(float maxX, float maxY, float posX, float posY, float speedX, float speedY, vector<float> color, int nr) {
    	this->maxX = maxX;
	this->maxY = maxY;
    	this->posX = posX;
    	this->posY = posY;
    	this->speedX = speedX;
    	this->speedY = speedY;
    	this->nr = nr;
    	radius = 15;
    	alive = true;
    	
    	for(float f: color){
    		this->color.push_back(f);
    	}
    	
}

Ball::~Ball() {
}

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
    		if (bounces>=maxBounces) {
    			alive = false;
    			return false;
    		}
    	}
    	return true;
}


void Ball::kill(){
	alive = false;
}

void Ball::draw() {
	
    	glColor3f(color[0], color[1], color[2]); 
	glTranslatef(posX, posY, 0.0);
    	gluDisk(gluNewQuadric(), 0, radius, 50, 1);
    	glTranslatef(-posX, -posY, 0.0);
    	
    	glColor3f(0, 0, 0); 
	std::string text = to_string(nr);
	float textX = posX - radius * 0.5; // Ustaw poziomą pozycję tekstu
	float textY = posY - radius * 0.5; // Ustaw pionową pozycję tekstu
	drawText(text, textX, textY);
}


void Ball::drawText(const std::string& text, float x, float y) {
    // Ustaw pozycję tekstu
    glRasterPos2f(x, y);
    
    // Narysuj każdy znak osobno
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}



void Ball::sayHI(){
	cout<<"Hi "<<nr<<endl;
}


