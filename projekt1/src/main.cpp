#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <unistd.h> 
#include "ball.h"

using namespace std;

int width = 1370;
int height = 768;

float maxSpeed = 1;
int maxBallsNumber = 10;

std::vector<Ball> balls;
std::vector<pthread_t> ballThreads;
float fps = 10; //ms
float newBallProbability = .000001; //%


void removeBall(int index){
	auto it = balls.begin() + index;
	balls.erase(it);
}


void* threadFunction(void* arg){
	int ballIndex = *reinterpret_cast<int*>(arg);
	Ball* ball = &balls[ballIndex];
	
	while(true){
		ball->sayHI();
		// Zatrzymaj wątek na 5 sekund
	    	sleep(10);
	}
	
	delete ball;
	return nullptr;
}


void addBall(){
	if(balls.size()>=maxBallsNumber) return;

	vector<float> color;
	
	for(int i =0; i<3;i++){
		color.push_back(float(random()) /RAND_MAX);
	}
	
	
	float speedX = float(random()) /RAND_MAX * maxSpeed * 2 - maxSpeed;
	float speedY = float(random()) /RAND_MAX * maxSpeed * 2 - maxSpeed;
	
	float posX = float(random()) /RAND_MAX * width;
	float posY = float(random()) /RAND_MAX * height;
	
	Ball ball(width, height, posX, posY, speedX, speedY, color, balls.size());
	//Ball ball(width, height, posX, posY, speedX, speedY, color, 1);
	balls.push_back(ball);
	
	int ballSize = balls.size() - 1;
	
	pthread_t thread;
	if(pthread_create(&thread, nullptr, threadFunction, reinterpret_cast<void*>(&ballSize)) != 0){
		cerr<<"Blad w dodawaniu watku "<<endl;
	}
	
	ballThreads.push_back(thread);
    	
	
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

void close(){
	while(balls.size()>0){
		balls.front().kill();
		balls.erase(balls.begin());
		
	}
	
	
	exit(0);
}

void keyUp(unsigned char key, int x, int y){
	if (key == ' '){
	close();
	}
}


int main(int argc, char** argv) {
	srand(time(NULL));
	
	
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
