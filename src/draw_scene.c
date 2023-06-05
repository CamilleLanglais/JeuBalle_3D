#include "draw_scene.h"
#include "3D_tools.h"
#include "ball.h"

void drawball(Ball *ball){
    ball->posX += ball->speedX;
    ball->posY += ball->speedY;
    ball->posZ += ball->speedZ;
    glPushMatrix();
        glColor3f(183/255.,1.,216/255.); 
        glTranslatef(ball->posX,ball->posY,ball->posZ);      
        drawSphere();
    glPopMatrix();

}


