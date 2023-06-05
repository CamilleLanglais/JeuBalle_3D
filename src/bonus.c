#include "bonus.h"
#include "3D_tools.h"
#include <math.h>
#include <string.h>
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
                drawCone();
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
        //Initialiser le générateur de nombre aléatoire avec la graine
        int rdPos = 0;
        int rdAll = rand() % 100;
        
        if(rdAll <25){
            rdPos = 0;
        } else if(rdAll>=25 && rdAll<50){
            rdPos = 1;
        } else if(rdAll>=50 && rdAll<75){
            rdPos = 2;
        } else{
            rdPos = 3;
        }
        printf("%d\n", rdPos);
        switch(rdPos){
            case 0 :
                //Bonus à gauche, milieu
                liste[i].x1 = -5;
                liste[i].x2 = -3;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                liste[i].xtransl = -4;
                liste[i].ytransl = 0;
                // if(liste[i].typeBonus=='c'){
                //     liste[i].xtransl = -4;
                //     liste[i].ytransl = 1.5;
                // } else{
                    
                // }
                break;
            case 1 :
                //Bonus à droit, milieu
                liste[i].x1 = 3;
                liste[i].x2 = 5;
                liste[i].y1 = 1;
                liste[i].y2 = -1;
                liste[i].xtransl = 4;
                liste[i].ytransl = -0.5;
                // if(liste[i].typeBonus=='c'){
                //     liste[i].xtransl = 3.5;
                //     liste[i].ytransl = 1.5;
                // } else{
                
                // }
                break;
            case 2 :
                //Bonus en haut, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = 4;
                liste[i].y2 = 2;
                liste[i].xtransl = 0;
                liste[i].ytransl = 2.5;
                // if(liste[i].typeBonus=='c'){
                //     liste[i].xtransl = 0;
                //     liste[i].ytransl = 4.5;
                // } else{
                    
                // }
                break;
            case 3 :
                //Bonus en bas, milieu
                liste[i].x1 = -1;
                liste[i].x2 = 1;
                liste[i].y1 = -2;
                liste[i].y2 = -4;
                liste[i].xtransl = 0;
                liste[i].ytransl = -3;
                // if(liste[i].typeBonus=='c'){
                //     liste[i].xtransl = 0;
                //     liste[i].ytransl = -4;
                // } else{
                    
                // }
                break;
        }
    }
}

bool collisionBonus(Bonus bonus, Ball ball, Raquette raquette, float newX, float newY){
    bool typeBonus = false;
    if (bonus.typeBonus == 'c'){
        colleRaquette(&ball, newX, newY);
        typeBonus = true;
    } else{
        raquette.nbrVie +=1;
    }
    return typeBonus;
}

void supprimerBonusCollision(Bonus* liste, int tailleTableau, int indexBonus) {
    int indiceBonusASupprimer = -1;
    // Recherche de l'indice du bonus avec le type de collision spécifié
    for (int i = 0; i < tailleTableau; i++) {
        if (liste[i].typeBonus == indexBonus) {
            indiceBonusASupprimer = i;
            break;
        }
    }

    // Utilisation de memmove pour déplacer les éléments suivants
    memmove(&liste[indiceBonusASupprimer], &liste[indiceBonusASupprimer + 1], (tailleTableau - indiceBonusASupprimer - 1) * sizeof(Bonus));
}