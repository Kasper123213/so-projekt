#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include "ball.h"
#include "grayArea.h"

using namespace std;

int width = 1370;
int height = 768;

float minStep = -1;
float maxStep = 1;

int maxBallsSpeed = 3;
int minBallsSpeed = 10;

int maxBallsNumber = 10;

GrayArea *grayArea = new GrayArea(150, height/2, height, 10);
thread grayAreaThread = grayArea->movingThread();

std::vector<Ball*> balls;
std::vector<thread> ballThreads;

float refreshingScreenSpeed = 10; //ms
float newBallProbability = .0000005; //%


thread ballsUpdatingThread;
int ballsUpdatingSpeed = 20;

thread ballsCollisionThread;
int ballsCollisionSpeed = 1;

mutex ballsSizeMtx;
mutex ballsMoveMtx;

bool appIsRunning = true;

int frozenBallsNumber = 0;

void removeBall(int index){
	
	balls.at(index)->kill();
	
	ballThreads.at(index).join();
	
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
	
	
	float stepX = float(random()) /RAND_MAX * (maxStep - minStep) + minStep;
	float stepY = float(random()) /RAND_MAX * maxStep;
	
	int speed = int(float(random()) /RAND_MAX * (maxBallsSpeed - minBallsSpeed) + minBallsSpeed);
	
	
	float posX = width / 2;
	float posY = 1;
	
	Ball* ball = new Ball(width, height, posX, posY, stepX, stepY, color, balls.size(), speed, &ballsMoveMtx);
	balls.push_back(ball);
	
	ballThreads.push_back(balls.at(balls.size() - 1)->movingThread());
	
}


void ballUpdating(){
	while(appIsRunning){
		if (maxBallsNumber > 0){
			if (rand()%100 <= newBallProbability){
				addBall();
				maxBallsNumber--;
			}
		}
		ballsSizeMtx.lock();
    		for(int i = 0; i<balls.size(); i++){
    			if(not balls.at(i)->isAlive()){
    				removeBall(i);
			}
    		}
    		ballsSizeMtx.unlock();
    		
    		this_thread::sleep_for(chrono::milliseconds(ballsUpdatingSpeed));
    	}
}

void ballsCollision(){
	while(appIsRunning){
		ballsSizeMtx.lock();
		for(int i=0; i<balls.size(); i++){
			if(int(balls.at(i)->getX()) == int(grayArea->getX())){
				int height = grayArea->getHeight();
				int y = grayArea->getY();
				if(y - height > balls.at(i)->getY() or balls.at(i)->getY() > y + height){
					if(balls.at(i)->isFrozen()) frozenBallsNumber--;
					balls.at(i)->unfreez();
				}else{
					if(!balls.at(i)->isFrozen())frozenBallsNumber++;
					balls.at(i)->freez();
				}
			}
		}
		ballsSizeMtx.unlock();
    		
    		this_thread::sleep_for(chrono::milliseconds(ballsCollisionSpeed));
    	}
}
 

void update(int _) {
	
    	glutPostRedisplay();	//wywołanie display
    	glutTimerFunc(refreshingScreenSpeed, update, 0);
}

void display() {
    	glClear(GL_COLOR_BUFFER_BIT);

    	// Rysujemy okrąg o promieniu 200, z 50 segmentami
    	glPushMatrix();
    	
    	grayArea->draw();
    	
    	ballsSizeMtx.lock();
    	for(int i = 0; i<balls.size(); i++){
    		balls.at(i)->draw();
    	}
    	ballsSizeMtx.unlock();
    	
    //Rysowanie licznika kulek
    	
    	glColor3f(1, 1, 1); 
    	// Ustaw pozycję tekstu
    	glRasterPos2f(1100, 760);
    	string text = "Number of frozen balls: " + to_string(frozenBallsNumber);
    
    	// Narysuj każdy znak osobno
    	for (char c : text) {
        	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    	}
    	
    	
    	glPopMatrix();
    
    	glFlush();
}


void myInit() {
	ballsUpdatingThread = thread(ballUpdating);
	
	ballsCollisionThread = thread(ballsCollision);
	
    	glClearColor(0.0, 0.0, 0.0, 1.0);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluOrtho2D(0, 1400, 0, 800);
    	
    	srand(time(nullptr));
}



void close(){
	appIsRunning = false;
	ballsUpdatingThread.join();
	
	ballsCollisionThread.join();
	
	
	while(balls.size()>0){
		balls.front()->kill();
		balls.front()->unfreez();
		balls.erase(balls.begin());
		
	}
	
	for(int i = 0; i<ballThreads.size(); i++){
		ballThreads.at(i).join();
	}
	
	grayArea->kill();
	delete grayArea;
	grayAreaThread.join();
	
	
	exit(0);
}

void keyUp(unsigned char key, int x, int y){
	if (key == ' '){
		close();
	}
	if (key == 'a'){
		addBall();
	}
	if (key == 'r'){
		removeBall(0);
	}
	if (key == 'l'){
		if(!balls.at(0)->isFrozen()){
			balls.at(0)->freez();
		}
	}
	if (key == 'u'){
		if(balls.at(0)->isFrozen()){
			balls.at(0)->unfreez();
		}
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
