#ifndef GRAYAREA_H
#define GRAYAREA_H

#include <vector>
#include <thread>

using namespace std;

class GrayArea{
	private:
		float posX, posY, maxY, step = 2;
		int speed, maxSpeed = 1, minSpeed = 50, width = 20, height = 150;
		vector<float> color;
		bool alive = true;
		
		void movement();

	public:
		GrayArea(float posX, float posY, float maxY, int speed);
		~GrayArea();

		void move();
		void draw();
		
		void setX(float value);
		float getX();
		
		void setY(float value);
		float getY();
		
		void setRandomSpeed();
		void setSpeed(int value);
		int getSpeed();
		
		void kill();
		bool isAlive();
		
		int getHeight();
		
		thread movingThread();

		
};

#endif // GRAYAREA_H
