#include "obstacles.h"
#include "3D_tools.h"
#include <math.h>



void drawObstacles(float profondeur, float distance, Obstacles obstacle){
	glPushMatrix();
		glTranslatef(profondeur-distance, 0., 0.);
		glScalef(1., 16/9., 1.);
		glColor3f(232/255.0,1.0,183/255.0);
		glBegin(GL_QUADS);
			glVertex3f(0.0,obstacle.x1,obstacle.y2);  //bas gauche
			glVertex3f(0.0,obstacle.x2,obstacle.y2);  //bas droit
			glVertex3f(0.0,obstacle.x2,obstacle.y1);  // haut droit
			glVertex3f(0.0,obstacle.x1,obstacle.y1);  // haut gauche
		glEnd();
    glPopMatrix();
	
}

void positionObstacles(Obstacles *liste, int nbrObstacles){
	for(int i = 0; i<nbrObstacles;i++){
		int rdTaille = rand()%2;
		int taille;
		switch(rdTaille){
			case 0:
				taille = 1/3;
				break;
			case 1:
				taille =1/5;
				break;
		}
		int mur = rand() % 4;
		switch(mur){
			case 0 :
				// Mur de gauche
				liste[i].x1 = -5*16/9;
				liste[i].x2 = (5*16/9)*taille;
				liste[i].y1 = 5;
				liste[i].y2 = -5;
				break;
			case 1 :
				// Mur de droite
				liste[i].x1 = (-5*16/9)*taille;
				liste[i].x2 = 5*16/9;
				liste[i].y1 = 5;
				liste[i].y2 = -5;
				break;
			case 2 :
				// Mur du bas
				liste[i].x1 = -5*16/9;
				liste[i].x2 = 5*16/9;
				liste[i].y1 = 5*taille;
				liste[i].y2 = -5;
				break;
			case 3 :
				// Mur du haut
				liste[i].x1 = -5*16/9;
				liste[i].x2 = 5*16/9;
				liste[i].y1 = 5;
				liste[i].y2 = -5*taille;
				break;
		}
	}
}