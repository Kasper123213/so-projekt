
#include "ball.h"


Ball::Ball(float maxX, float maxY, float posX, float posY, float stepX, float stepY, vector<float> color, int nr, int speed, mutex* mtx) {
    	this->maxX = maxX;
	this->maxY = maxY;
    	this->posX = posX;
    	this->posY = posY;
    	this->stepX = stepX;
    	this->stepY = stepY;
    	this->nr = nr;
    	this->speed = speed;
    	this->mtx = mtx;
    	radius = 15;
    	alive = true;
    	frozen = false;
    	
    	for(float f: color){
    		this->color.push_back(f);
    	}
    	
}

Ball::~Ball() {
}

void Ball::move() {
	//if(frozen) cout<<"Dupa1"<<endl;
	std::unique_lock<mutex> lock(*mtx);
	cv.wait(lock, [this]{return !frozen;});
	
	setX(getX() + stepX);
	
    	if(getX()>maxX) {
    		stepX = -stepX;
    		setX(maxX);
    		bounces++;
    		return;
    	}
    	
    	if(getX()<0) {
    		stepX *= -1;
    		bounces++;
    		setX(0);
    		return;
    	}
    
    
    	setY(getY() + stepY);
   
    	if(getY()>maxY){
    		stepY = -stepY;
    		setY(maxY);
    		bounces++;
    		return;
    	}
    	
    	if(getY()<0){
    		stepY *= -1;
    		setY(0);
    		bounces++;
    	}
    	
}

void Ball::freez(){
	frozen = true;
	cv.notify_all();
}

void Ball::unfreez(){
	frozen = false;
	cv.notify_all();
}

bool Ball::isFrozen(){ return frozen;}	


void Ball::kill(){
	std::unique_lock<mutex> lock(*mtx);
	alive = false;
}

void Ball::draw() {
    	glColor3f(color[0], color[1], color[2]); 
	glTranslatef(getX(), getY(), 0.0);
    	gluDisk(gluNewQuadric(), 0, radius, 50, 1);
    	glTranslatef(-getX(), -getY(), 0.0);
    	
    	glColor3f(0, 0, 0); 
	std::string text = to_string(getNr());
	float textX = getX() - radius * 0.5; // Ustaw poziomą pozycję tekstu
	float textY = getY() - radius * 0.5; // Ustaw pionową pozycję tekstu
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



thread Ball::movingThread(){
	return thread(&Ball::movement, this);
}


void Ball::movement(){
	while(isAlive()){
		if(bounces >= maxBounces){
			kill();
			break;
		}
		move();
		this_thread::sleep_for(chrono::milliseconds(speed));
	}
}

bool Ball::isAlive(){
	return alive;
}

float Ball::getX(){
	return posX;
}

void Ball::setX(float value){
	posX = value;
}

float Ball::getY(){
	return posY;
}

void Ball::setY(float value){
	posY = value;
}

int Ball::getNr(){
	return nr;
}

