#ifndef BALL_H
#define BALL_H

#include <vector>

class Ball {
private:
    float maxX, maxY, posX, posY, speedX, speedY;
    float* color;
    int nr, radius, bounces = 0, maxBounces = 5; 


public:
    Ball(float maxX, float maxY, float posX, float posY, float speedX, float speedY, float* color, int nr);
    ~Ball();

    bool move();
    void draw();
};

#endif // BALL_H
