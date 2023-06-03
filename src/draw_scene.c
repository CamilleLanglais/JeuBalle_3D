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

void drawFrame(){
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(20.0,0.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,20.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,20.0);
    glEnd();
}



