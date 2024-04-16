#ifndef BALL_H
#define BALL_H

#include <vector>
#include <string>
#include <unistd.h>


using namespace std;

class Ball {
private:
	float maxX, maxY, posX, posY, speedX, speedY;
	vector<float> color;
	int radius, bounces = 0, maxBounces = 3; 
	

	void drawText(const std::string& text, float x, float y);

public:
	Ball(float maxX, float maxY, float posX, float posY, float speedX, float speedY, vector<float> color, int nr);
	~Ball();
	
	int nr;
	bool alive;

	bool move();
	void draw();
	void kill();
	
	void sayHI();
    
    
};

#endif // BALL_H
