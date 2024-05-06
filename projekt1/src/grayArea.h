#ifndef GRAYAREA_H
#define GRAYAREA_H

#include <vector>
#include <thread>

using namespace std;

class GrayArea{
	private:
		float posX, posY, maxY, speed, size = 100, maxSpeed = 4, minSpeed = 1;
		vector<float> color;
		bool alive = true;
		
		void movement();

	public:
		GrayArea(float posX, float posY, float maxY, float speed);
		~GrayArea();

		void move();
		void draw();
		
		void setX(float value);
		float getX();
		
		void setY(float value);
		float getY();
		
		void setRandomSpeed();
		void setSpeed(float value);
		float getSpeed();
		
		void kill();
		bool isAlive();
		
		thread movingThread();

		
};

#endif // GRAYAREA_H
