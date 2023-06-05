#include "raquette.h"
#include "3D_tools.h"
#include <math.h>

Raquette* initRaquette(float x, float y){
	Raquette* raquette = (Raquette*)malloc(sizeof(Raquette));
	raquette->x = x;
	raquette->y = y;
	raquette->nbrVie = 5;
	return raquette;
}

void drawRaquette(Raquette raquette, float x, float y){
	raquette.x = x;
	raquette.y = y;
    glBegin(GL_LINES);
        glColor3f(226/255.0,160/255.0,1.0);
		glVertex3f(0.0,x+1.0,y-1.0);
		glVertex3f(0.0,x-1.0,y-1.0);
		glVertex3f(0.0,x+1.0,y-1.0);
		glVertex3f(0.0,x+1.0,y+1.0);
		glVertex3f(0.0,x+1.0,y+1.0);
		glVertex3f(0.0,x-1.0,y+1.0);
		glVertex3f(0.0,x-1.0,y+1.0);
		glVertex3f(0.0,x-1.0,y-1.0);
    glEnd();
}

void setVieRaquette(Raquette raquette){
	raquette.nbrVie -= 1;
}