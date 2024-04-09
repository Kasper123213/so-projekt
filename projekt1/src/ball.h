#ifndef BALL_H
#define BALL_H

#include <vector>
#include <string>
#include <thread>
#include <unistd.h>


using namespace std;

class Ball {
private:
	float maxX, maxY, posX, posY, speedX, speedY;
	vector<float> color;
	int nr, radius, bounces = 0, maxBounces = 5; 
	

	void drawText(const std::string& text, float x, float y);
	void movment();

public:
	Ball(float maxX, float maxY, float posX, float posY, float speedX, float speedY, vector<float> color, int nr);
	~Ball();
	
	bool alive;

	bool move();
	void draw();
	void kill();
    
    	thread movingThread();
    
};

#endif // BALL_H
