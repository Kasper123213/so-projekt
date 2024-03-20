#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include "ball.h"

float translateX = 0.0;
float translateY = 0.0;
float translationSpeed = 1.0;

std::vector<Ball> balls;
std::vector<std::thread> ballThreads;
float fps = 100/60; //100/1ms
float newBallProbability = 0.01;

void update(int value) {
	//if (rand() <= newBallProbability) addBall();
	
    	glutPostRedisplay();
    	glutTimerFunc(fps, update, 0);
}

void display() {
    	glClear(GL_COLOR_BUFFER_BIT);

    	// Rysujemy okrąg o promieniu 200, z 50 segmentami
    	glPushMatrix();
    	
    	for(Ball ball: balls){
    		ball.draw();
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

void addBall(){
	
}

int main(int argc, char** argv) {
	int width = 1366;
	int height = 768;
	float color[] = {1.2f,0.2f,0.2f};
	
	Ball ball(width, height, 10, 10, 0, 0, color, 5);
	balls.push_back(ball);
	
	
	float color1[] = {1.0f,0.9f,0.9f};
	
	Ball ball1(width, height, 50, 50, 0, 0, color1, 5);
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
    	glutMainLoop();
    
    	return 0;
}
