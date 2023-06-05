#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>


void drawCorridor(float profondeur, float taille){
    //sol
    glPushMatrix();
		glTranslatef(profondeur,0.,-5.);
		glScalef(taille, 40., 1.);
		glColor3f(196/225.,245/255.0,252/255.);
		drawSquareXY();
	glPopMatrix();

    // Mur gauche
	glPushMatrix();
		glTranslatef(profondeur, -10., 0.);
		glScalef(taille, 0.5, 30.);
		glColor3f(1.0,193/255.0,207/255.);
		drawSquareXZ();
    glPopMatrix();

	// mur droit
	glPushMatrix();
		glTranslatef(profondeur, 10., 0.);
		glScalef(taille, 0.5, 30.);
		glColor3f(1.0,193/255.0,207/255.);
		drawSquareXZ();
    glPopMatrix();


    //plafond
    glPushMatrix();
		glTranslatef(profondeur,0.,5.);
		glScalef(taille, 40., 1.);
		glColor3f(196/225.,245/255.0,252/255.);
		drawSquareXY();
	glPopMatrix();
}