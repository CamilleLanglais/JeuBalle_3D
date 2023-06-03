#pragma once

#include <GLFW/glfw3.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Ball{
    float posX;
    float posY;
    float posZ;
    float speedX;
    float speedY;
    float speedZ;  
    float radius;
}Ball;

Ball* initBall(float posX,float posY, float posZ, float speedX, float speedY, float speedZ, float radius);
