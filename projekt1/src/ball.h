#ifndef BALL_H
#define BALL_H

#include <vector>
#include <string>
#include <thread>
#include <unistd.h>


using namespace std;

class Ball {
private:
	float maxX, maxY, stepX, stepY, posX, posY;
	vector<float> color;
	int nr, speed, radius, bounces = 0, maxBounces = 5; 
	bool alive;
	

	void drawText(const std::string& text, float x, float y);
	void movement();
	

public:
	Ball(float maxX, float maxY, float posX, float posY, float stepX, float stepY, vector<float> color, int nr, int speed);
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

    
    	thread movingThread();
    
};

#endif // BALL_H
