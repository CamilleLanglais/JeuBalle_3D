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
#include <stdbool.h>
#include "ball.h"
#include "raquette.h"

typedef struct Bonus{
	float x1;
	float x2;
	float y1; 
	float y2;
    float xtransl;
    float ytransl;
	char typeBonus;
	bool visible;
} Bonus;


void drawBonus(float profondeur, float distance, Bonus bonus);

void positionBonus(Bonus *liste, int nbrBonus);

bool collisionBonus(Bonus *bonus, Ball *ball, Raquette *raquette, float newX, float newY);