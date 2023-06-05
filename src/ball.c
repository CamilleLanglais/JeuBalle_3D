#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>
#include "ball.h"

Ball* initBall(float posX,float posY, float posZ, float speedX, float speedY, float speedZ, float radius){
    Ball* ball = (Ball*)malloc(sizeof(Ball));
    ball->posX = posX; 
    ball->posY = posY;  
    ball->posZ = posZ; 
    ball->speedX = speedX; 
    ball->speedY = speedY; 
    ball->speedZ = speedZ;  
    ball->radius = radius; 
    return ball;
};

void colleRaquette(Ball *ball, float newX, float newY){
    ball->posY = newX;
    ball->posZ = newY+1.5;
    ball->posX = -2.;
    ball->speedX = 0;
    ball->speedY = 0;
    ball->speedZ = 0;
}

