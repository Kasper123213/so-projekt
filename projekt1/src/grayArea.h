#ifndef GRAYAREA_H
#define GRAYAREA_H

#include <vector>

using namespace std;

class GrayArea{
	private:
		double posX, posY, speed;
		vector<double> color;

	public:
		GrayArea(double posX, double posY);
		~GrayArea();

		void move();

		
};

#endif // GRAYAREA_H
