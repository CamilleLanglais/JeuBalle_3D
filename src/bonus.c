#include "bonus.h"
#include "3D_tools.h"
#include <math.h>
#include <string.h>
#include "time.h"

void drawBonus(float profondeur, float distance, Bonus bonus){
    if(bonus.visible){
        glPushMatrix();
		glTranslatef(profondeur-distance, 0., 0.);
		glScalef(1., 1., 1.);
        // Si le typeBonus est égale à 't' on défini une couleur particulière
        if(bonus.typeBonus=='t'){
            glColor3f(226/255.0,160/255.0, 1.0);
            glPushMatrix();
                glTranslatef(0., bonus.xtransl, bonus.ytransl);
                drawCone();
            glPopMatrix();
        } else{
            // On définit une seconde couleur pour le deuxième bonus
            glColor3f(1.0,1.0, 1.0);
            glPushMatrix();
                glTranslatef(0., bonus.xtransl, bonus.ytransl);
                drawCone();
            glPopMatrix();
        }
        glPopMatrix();	
    }
}

void positionBonus(Bonus *liste, int nbrBonus){
    for(int i = 0; i<nbrBonus;i++){
        liste[i].visible = true;
        // On donne aléatoirement le type de bonus
        int rdTypeBonus = rand()%2;
        switch(rdTypeBonus){
            case 0:
                liste[i].typeBonus = 'c';
                break;
            case 1:
                liste[i].typeBonus = 't';
                break;
        }
        //On donne aléatoirement la position du bonus
        int rdPos = rand() % 4;
        switch(rdPos){
            case 0 :
                //Bonus à gauche, milieu
                liste[i].x1 = -5;
                liste[i].x2 = -3;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                liste[i].xtransl = -4;
                liste[i].ytransl = 0;
                break;
            case 1 :
                //Bonus à droit, milieu
                liste[i].x1 = 3;
                liste[i].x2 = 5;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                liste[i].xtransl = 4;
                liste[i].ytransl = -0.5;
                break;
            case 2 :
                //Bonus en haut, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = 4;
                liste[i].y2 = 2;
                liste[i].xtransl = 0;
                liste[i].ytransl = 2.5;
                break;
            case 3 :
                //Bonus en bas, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = -2;
                liste[i].y2 = -4;
                liste[i].xtransl = 0;
                liste[i].ytransl = -3;
                break;
        }
    }
}

bool collisionBonus(Bonus *bonus, Ball *ball, Raquette *raquette, float newX, float newY){
    bool valeurBonus = false;
    if (bonus->typeBonus == 'c'){
        colleRaquette(ball, newX, newY);
        valeurBonus = true;
    } else{
        if(raquette->nbrVie<5){
            raquette->nbrVie +=1;
        }
    }
    bonus->visible = false;
    return valeurBonus;
}