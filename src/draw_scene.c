#include "draw_scene.h"
#include "3D_tools.h"

void drawBase() {
    glPushMatrix();
	glColor3f(235.0/255.0 , 207.0/255.0 , 52.0/255.0);
    glScalef(3.0,3.0,0.0);
	drawCircle();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0,2.0,10.0);
    drawCone();
    glPopMatrix();
}

void drawArm() {
    
    glPushMatrix();
        glColor3f(245.0/255.0 , 164.0 / 255.0 , 66.0/255.0);
        glTranslatef(0.,0.,10.); 
        glScalef(3.2/2.,3.2/2.,3.2/2.);
        drawSphere();
    glPopMatrix();

    glPushMatrix();

        glTranslatef(0.0,0.0,10.0);
        glRotatef(90.,0.,1.,0.);
        glScalef(1.0,1.0,10.0);
        drawCone();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.,0.,10.);
        glRotatef(-90.,0.,1.,0.);
        glScalef(1.0,1.0,10.0);
        drawCone();
    glPopMatrix();
}

void drawPan() {
    glPushMatrix();
        glColor3f(1.0/255., 0., 0.);
        glTranslatef(-10., 0., 5.);
        glScalef(3.,3.,3.);
        drawCircle();
    glPopMatrix();

    glPushMatrix();
        
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



