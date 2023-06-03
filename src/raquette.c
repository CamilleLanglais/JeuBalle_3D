#include "raquette.h"
#include "3D_tools.h"
#include <math.h>

void drawRaquette(float x, float y){
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

