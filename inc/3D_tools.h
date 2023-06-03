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

#define NB_SEG_CIRCLE 64

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;      // Angle between x axis and viewpoint
extern float phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom ; // Distance between origin and viewpoint

void setCamera();

/* Draw cannonic objet functions */
void drawSquareXY();
void drawSquareXZ();
void drawSquareYZ();

void drawCircle();

void drawCube();

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);
