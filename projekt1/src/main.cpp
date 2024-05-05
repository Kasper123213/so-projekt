#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "ball.h"

using namespace std;

int width = 1370;
int height = 768;

float maxSpeed = 1;
int maxBallsNumber = 3;

std::vector<Ball*> balls;
std::vector<thread> ballThreads;
float fps = 50; //ms
float newBallProbability = .000001; //%


void removeBall(int index){
	balls.at(index)->kill();
	
	ballThreads[index].join();
	cout<<index<<" joined"<<endl;
	
	auto threadsIt = ballThreads.begin() + index;
	ballThreads.erase(threadsIt);
	
	auto ballsIt = balls.begin() + index;
	delete balls.at(index);
	balls.erase(ballsIt);
}


void addBall(){
	if(balls.size()>=maxBallsNumber) return;

	vector<float> color;
	
	for(int i =0; i<3;i++){
		color.push_back(float(random()) /RAND_MAX);
	}
	
	
	float speedX = float(random()) /RAND_MAX * maxSpeed;
	float speedY = float(random()) /RAND_MAX * maxSpeed*2;	//zmienic
	
	float posX = float(random()) /RAND_MAX * width;
	float posY = float(random()) /RAND_MAX * height;
	
	Ball* ball = new Ball(width, height, posX, posY, speedX, speedY, color, balls.size());
	cout<<"rozmiar \t"<<balls.size()<<endl;
	balls.push_back(ball);
	
	ballThreads.push_back(balls[balls.size() - 1]->movingThread());
	
    	
    	//cout<<float(random()) /RAND_MAX<<endl;
	
}


void update(int value) {
	if (rand()%100 <= newBallProbability) addBall();
	
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
		//cout<<"closing " <<balls.front().alive<<endl;
		balls.erase(balls.begin());
		
	}
	cout<<"all done  "<<endl;
	
	for(int i = 0; i<ballThreads.size(); i++){
		ballThreads[i].join();
		cout<<i<<" joined"<<endl;
	}
	exit(0);
}

void keyUp(unsigned char key, int x, int y){
	if (key == ' '){
		close();
	}
	if (key == 'i'){
		cout<<"Size of balls: "<<balls.size()<<endl;
		cout<<"Size of threads: "<<ballThreads.size()<<endl;
		for(int i = 0; i<ballThreads.size(); i++){
			cout<<i<<" "<<balls[i]->getX()<<" "<< balls[i]->getY()<<" "<<balls[i]->isAlive()<<" "<<ballThreads[i].joinable()<<endl;
		}
		cout<<endl<<endl;
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
