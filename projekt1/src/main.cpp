#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "ball.h"
#include "grayArea.h"

using namespace std;

int width = 1370;
int height = 768;

float minSpeed = -3;
float maxSpeed = 3;
int maxBallsNumber = 4;

GrayArea *grayArea = new GrayArea(150, height/2, height, 1.5);
thread grayAreaThread = grayArea->movingThread();

std::vector<Ball*> balls;
std::vector<thread> ballThreads;
float fps = 10; //ms
float newBallProbability = .0000005; //%


void removeBall(int index){
	balls.at(index)->kill();
	
	ballThreads[index].join();
	
	auto threadsIt = ballThreads.begin() + index;
	ballThreads.erase(threadsIt);
	
	auto ballsIt = balls.begin() + index;
	delete balls.at(index);
	balls.erase(ballsIt);
}


void addBall(){
	vector<float> color;
	
	for(int i =0; i<3;i++){
		color.push_back(float(random()) /RAND_MAX);
	}
	
	
	float speedX = float(random()) /RAND_MAX * (maxSpeed - minSpeed) + minSpeed;
	float speedY = float(random()) /RAND_MAX * (maxSpeed - minSpeed) + minSpeed;	//zmienic
	
	
	float posX = width / 2;
	float posY = 1;
	
	Ball* ball = new Ball(width, height, posX, posY, speedX, speedY, color, balls.size());
	balls.push_back(ball);
	
	ballThreads.push_back(balls[balls.size() - 1]->movingThread());
	
}


void update(int value) {
	if (maxBallsNumber > 0){
		if (rand()%100 <= newBallProbability){
			addBall();
			maxBallsNumber--;
		}
	}
	
    	for(int i = 0; i<balls.size(); i++){
    		if(not balls[i]->isAlive()){
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
    		balls[i]->draw();
    	}
    	
    	grayArea->draw();
    	
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
		balls.front()->kill();
		balls.erase(balls.begin());
		
	}
	
	for(int i = 0; i<ballThreads.size(); i++){
		ballThreads[i].join();
	}
	
	delete grayArea;
	grayArea->kill();
	grayAreaThread.join();
	
	exit(0);
}

void keyUp(unsigned char key, int x, int y){
	if (key == ' '){
		close();
	}
	if (key == 'i'){
		
		cout<<grayArea->getX()<<" "<<grayArea->getY()<<" "<<grayArea->getSpeed()<<endl;
	}
	if (key == 'a'){
		addBall();
	}
	if (key == 'r'){
		removeBall(balls.size()-1);
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
