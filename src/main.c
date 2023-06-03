#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "3D_tools.h"
#include "draw_scene.h"
#include "corridor.h"
#include "ball.h"
#include "raquette.h"
#include "obstacles.h"




/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "Projet";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

double newX = 0.;
double newY = 0.;
bool lbutton_down = false;
double alpha = 60.0;

#define NBR_OBSTACLES 8

Obstacles listeObs[NBR_OBSTACLES];

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(alpha,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_R :
				flag_animate_rot_arm = 1-flag_animate_rot_arm;
				break;
			case GLFW_KEY_T :
				flag_animate_rot_scale = 1-flag_animate_rot_scale;
				break;
			case GLFW_KEY_KP_9 :
				if(dist_zoom<100.0f) dist_zoom*=1.1;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_KP_3 :
				if(dist_zoom>1.0f) dist_zoom*=0.9;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_UP :
				if (phy>2) phy -= 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_DOWN :
				if (phy<=88.) phy += 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_LEFT :
				theta -= 5;
				break;
			case GLFW_KEY_RIGHT :
				theta += 5;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
		}
	}
	
}

void mouse_mouv(GLFWwindow* window, double xpos, double ypos){
	glfwGetCursorPos(window, &xpos, &ypos);
	double h = (tan(alpha/2))*2;
	if(xpos<WINDOW_WIDTH-120 && xpos>120){
		if(xpos >= 120  && xpos <= WINDOW_WIDTH-120){
		newX = -((xpos-(WINDOW_WIDTH/2.0))*(h/WINDOW_WIDTH));
	}
	if(ypos<WINDOW_HEIGHT-120 && ypos>120){
		}
	if (ypos >=120 && ypos <= WINDOW_HEIGHT -120){
		newY = ((ypos-(WINDOW_HEIGHT/2.0))*(h/WINDOW_HEIGHT));
		}
	}

}


int main(int argc, char** argv)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_mouv);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	float profondeur=0.;
	float vitesse_corridor=0.2;
	float taille = 1000;
	Ball *ball = initBall(0, 0, 0, -0.2, 0.5, 0., 2);

	positionObstacles(listeObs, NBR_OBSTACLES);


	
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		// int profondeur= + vitesse_corridor*elapsedTime;
		// drawCorridor(profondeur);
		
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		



		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
					
		}
		profondeur +=  vitesse_corridor;
		

		drawCorridor(profondeur, taille);
		drawRaquette(newX, newY);
		drawball(ball);
		// collisions sol/plafond
		if(ball->posY< -0.5 * 20 || ball->posY > 0.5 * 20){
            ball->speedY *= -1;
        }
        //colissions murs
        if(ball->posX < -0.5 * taille|| ball->posX > 0.5 * taille){
        ball->speedX *= -1;
    }
		for(int i=0; i<NBR_OBSTACLES;i++){
				drawObstacles(profondeur,40*(i+1), listeObs[i]);
			}
		
	
		

		/* Scene rendering */
		
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		// double elapsedTime = glfwGetTime() - startTime;
		// /* If to few time is spend vs our wanted FPS, we wait */
		// // profondeur +=  vitesse_corridor*elapsedTime;
		
		
		// if(elapsedTime < FRAMERATE_IN_SECONDS)
		// {
		// 	glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		// }
		
		
		

		/* Animate scenery */
	}

	glfwTerminate();
	return 0;
}
