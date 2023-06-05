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

typedef struct Raquette{
    float x;
    float y;
    int nbrVie;
    int width;
    int height;
} Raquette;

Raquette* initRaquette(float x, float y);

void drawRaquette(Raquette * raquette, float x, float y);

void mouvRaquette(Raquette raquette, float aspectRatio, float xpos, float ypos, float windowWidth, float windowHeight, float corridorWidth, float corridorHeight);