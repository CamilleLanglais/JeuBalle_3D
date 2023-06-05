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

typedef struct Obstacles{
	float x1;
	float x2;
	float y1; 
	float y2;
	float positionProf;
	char typeMur;
	float typeTaille;
} Obstacles;

void drawObstacles(float profondeur, float distance, Obstacles obstacle);

void positionObstacles(Obstacles *liste, int nbrObstacles);

void setPositionObstacles(float profondeur, float distance, Obstacles *obstacle);