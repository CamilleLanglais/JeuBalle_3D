#include "bonus.h"
#include "3D_tools.h"
#include <math.h>
#include "time.h"

void drawBonus(float profondeur, float distance, Bonus bonus){
	glPushMatrix();
		glTranslatef(profondeur-distance, 0., 0.);
		glScalef(1., 1., 1.);
        if(bonus.typeBonus=='t'){
            glColor3f(226/255.0,160/255.0, 1.0);
            glPushMatrix();
                glTranslatef(0., bonus.xtransl, bonus.ytransl);
                drawCone();
            glPopMatrix();
            /*glBegin(GL_TRIANGLE_FAN);
			    glVertex3f(0.0,bonus.x1,bonus.y2);
			    glVertex3f(0.0,bonus.x2,bonus.y2);
			    glVertex3f(0.0,bonus.x2,bonus.y1);
			    glVertex3f(0.0,bonus.x1,bonus.y1);
		    glEnd();*/
        } else{
            glColor3f(1.0,1.0, 1.0);
            glPushMatrix();
                glTranslatef(0., bonus.xtransl, bonus.ytransl);
                drawSphere();
            glPopMatrix();
            /*glBegin(GL_TRIANGLE_FAN);
			    glVertex3f(0.0,bonus.x1,bonus.y2);
			    glVertex3f(0.0,bonus.x2,bonus.y2);
			    glVertex3f(0.0,bonus.x2,bonus.y1);
			    glVertex3f(0.0,bonus.x1,bonus.y1);
		    glEnd();*/
        }
    glPopMatrix();	
}

void positionBonus(Bonus *liste, int nbrBonus){
    for(int i = 0; i<nbrBonus;i++){
        int rdTypeBonus = rand()%2;
        switch(rdTypeBonus){
            case 0:
                liste[i].typeBonus = 'c';
                break;
            case 1:
                liste[i].typeBonus = 't';
                break;
        }
        //Définir la graine
        srand(time(NULL));

        //Initialiser le générateur de nombre aléatoire avec la graine
        int rdPos = rand() % 100 + 0;
        printf("%d\n", rdPos);
        switch(rdPos){
            case 0 :
                //Bonus à gauche, milieu
                liste[i].x1 = -5;
                liste[i].x2 = -3;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                if(liste[i].typeBonus=='c'){
                    liste[i].xtransl = -4;
                    liste[i].ytransl = 1.5;
                } else{
                    liste[i].xtransl = -4;
                    liste[i].ytransl = 0;
                }
                break;
            case 1 :
                //Bonus à droit, milieu
                liste[i].x1 = 3;
                liste[i].x2 = 5;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                if(liste[i].typeBonus=='c'){
                    liste[i].xtransl = 3.5;
                    liste[i].ytransl = 1.5;
                } else{
                    liste[i].xtransl = 4;
                    liste[i].ytransl = -0.5;
                }
                break;
            case 2 :
                //Bonus en haut, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = 4;
                liste[i].y2 = 2;
                if(liste[i].typeBonus=='c'){
                    liste[i].xtransl = 0;
                    liste[i].ytransl = 4.5;
                } else{
                    liste[i].xtransl = 0;
                    liste[i].ytransl = 2.5;
                }
                break;
            case 3 :
                //Bonus en bas, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = -2;
                liste[i].y2 = -4;
                if(liste[i].typeBonus=='c'){
                    liste[i].xtransl = 0;
                    liste[i].ytransl = -4;
                } else{
                    liste[i].xtransl = 0;
                    liste[i].ytransl = -3;
                }
                break;
        }
    }
}

/*void destroyBonus(Bonus bonus){
    
}*/