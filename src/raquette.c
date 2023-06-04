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

void mouvRaquette(Raquette raquette, float aspectRatio, float xpos, float ypos, float windowWidth, float windowHeight, float corridorWidth, float corridorHeight) {
	
	// float halfRectWidth = 1;
    // float halfRectHeight = 1;

    // if (aspectRatio > 1) {
    //     float normalizedX = (xpos - windowWidth / 2) / (windowWidth / 2) * aspectRatio;
    //     raquette.x = normalizedX > 1.0 ? (corridorWidth / 2 - halfRectWidth) : (normalizedX < -1.0 ? -(corridorWidth / 2 - halfRectWidth) : normalizedX * (corridorWidth / 2 - halfRectWidth));
    //     raquette.y = -((ypos - windowHeight / 2) / (windowHeight / 2)) * (corridorHeight / 2 - halfRectHeight);
    // }
    // else {
    //     float normalizedX = (xpos - windowWidth / 2) / (windowWidth / 2);
    //     raquette.x = normalizedX > 1.0 ? (corridorWidth / 2 - halfRectWidth) : (normalizedX < -1.0 ? -(corridorWidth / 2 - halfRectWidth) : normalizedX * (corridorWidth / 2 - halfRectWidth));
    //     raquette.y = -((ypos - windowHeight / 2) / (windowHeight / 2) / aspectRatio) * (corridorHeight / 2 - halfRectHeight);
    // }

	float halfRectWidth = 1;
    float halfRectHeight = 1;

    float normalizedX = (xpos - windowWidth / 2) / (windowWidth / 2);
    float normalizedY = (ypos - windowHeight / 2) / (windowHeight / 2);

    float maxX, maxY, minX, minY;

    if (aspectRatio > 1) {
        maxX = corridorWidth / 2 - halfRectWidth;
        maxY = corridorHeight / 2 - halfRectHeight;
        minX = -maxX;
        minY = -maxY;
    } else {
        maxX = corridorWidth / 2 - halfRectWidth;
        maxY = (corridorHeight / 2 - halfRectHeight) / aspectRatio;
        minX = -maxX;
        minY = -maxY;
    }

    if (normalizedX > 1.0) {
        raquette.x = maxX;
    } else if (normalizedX < -1.0) {
        raquette.x = minX;
    } else {
        raquette.x = normalizedX * maxX;
    }

    if (normalizedY > 1.0) {
        raquette.y = -maxY;
    } else if (normalizedY < -1.0) {
        raquette.y = -minY;
    } else {
        raquette.y = -normalizedY * maxY;
    }

}