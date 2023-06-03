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
} Ball;
