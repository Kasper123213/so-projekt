#ifndef BALL_H
#define BALL_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <iostream>
#include <GL/glut.h>
#include <chrono>


using namespace std;

class Ball {
private:
	float maxX, maxY, stepX, stepY, posX, posY;
	vector<float> color;
	int nr, speed, radius, bounces = 0, maxBounces = 5; 
	bool alive, frozen;
	

	void drawText(const std::string& text, float x, float y);
	void movement();
	mutex* mtx;
	condition_variable cv;
	

public:
	Ball(float maxX, float maxY, float posX, float posY, float stepX, float stepY, vector<float> color, int nr, int speed, mutex* mtx);
	~Ball();
	
	int getNr();
	
	float getX();
	float getY();
	void setX(float value);
	void setY(float value);
	bool isAlive();
	
	void move();
	void draw();
	void kill();
	void freez();
	void unfreez();
	bool isFrozen();

    
    	thread movingThread();
    
};

#endif // BALL_H
