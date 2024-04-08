#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include "ball.h"

using namespace std;

float translateX = 0.0;
float translateY = 0.0;
float translationSpeed = 1.0;

int width = 1370;
int height = 768;

float maxSpeed = 5;

std::vector<Ball> balls;
std::vector<std::thread> ballThreads;
float fps = 100/60; //100/1ms
float newBallProbability = .01; //%


void removeBall(int index){
	auto it = balls.begin() + index;
	balls.erase(it);
}


void addBall(){
	float color[3];
	
	for(int i =0; i<3;i++){
		color[i] = float(random()) /RAND_MAX;
	}
	
	float speedX = float(random()) /RAND_MAX * maxSpeed;
	float speedY = float(random()) /RAND_MAX * maxSpeed;
	
	float posX = float(random()) /RAND_MAX * width;
	float posY = float(random()) /RAND_MAX * height;
	
	Ball ball(width, height, posX, posY, speedX, speedY, color, 1);
	balls.push_back(ball);
	
	
    	//cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<endl;
	
}


void update(int value) {
	if (rand()%100 <= newBallProbability) addBall();
	
    	for(int i = 0; i<balls.size(); i++){
    		bool survived = balls[i].move();
    		if(not survived){
    			removeBall(i);
		}
    	}
    	glutPostRedisplay();	//wywołanie display
    	glutTimerFunc(fps, update, 0);
}

void display() {
    	glClear(GL_COLOR_BUFFER_BIT);

    	// Rysujemy okrąg o promieniu 200, z 50 segmentami
    	glPushMatrix();
    	for(int i = 0; i<balls.size(); i++){
    		balls[i].draw();
    	}
    	
    	glPopMatrix();
    
    	glFlush();
}


void myInit() {
    	glClearColor(0.0, 0.0, 0.0, 1.0);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluOrtho2D(0, 1400, 0, 800);
    	
    	srand(time(nullptr));
}

void keyUp(unsigned char key, int x, int y){
	if (key == ' ') exit(0);
}


int main(int argc, char** argv) {
	srand(time(NULL));
	
	float color[] = {1.f,0.f,0.f};
	
	Ball ball(width, height, 500, 300, .1, .6, color, 1);
	balls.push_back(ball);
	
	
	float color1[] = {1.0f,0.9f,0.9f};
	
	Ball ball1(width, height, 50, 50, -.3, .2, color1, 2);
	balls.push_back(ball1);
	
	
    	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    	glutInitWindowSize(width, height);
    	glutInitWindowPosition(0, 0);
    	glutCreateWindow("Circle Drawing");
    	glutKeyboardFunc(keyUp);
    
    	myInit();
    	glutDisplayFunc(display);
    	glutTimerFunc(0, update, 0); // Rozpoczęcie cyklicznej aktualizacji
    	glutMainLoop();	//wywołanie update()
    
    	return 0;
}
