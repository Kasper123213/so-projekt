#include <vector>

using namespace std;

class Ball{
	private:
		double posX, posY, speedX, speedY;
		vector<double> color;
	public:
		Ball(double posX, double posY, double speed);		~Ball();

		move();
}
