#include "3D_tools.h"
#include <math.h>

//#define NBR_OBSTACLES 5

typedef struct Obstacles{
	float x1;
	float x2;
	float y1; 
	float y2;
	char typeMur;
	float typeTaille; 
} Obstacles;

void drawObstacles(float profondeur, float distance, Obstacles obstacle);

void positionObstacles(Obstacles *liste, int nbrObstacles);