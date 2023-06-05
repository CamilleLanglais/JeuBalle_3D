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
#include "bonus.h"

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "IMAC Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

double newX = 0.;
double newY = 0.;
bool lbutton_down = false;
bool clickGauche = false;
bool perdUneVie = false;
bool debutBall = true;
bool prendSpecialBonus = false;
bool takeBonus = false;
double alpha = 60.0;

#define NBR_OBSTACLES 12
#define NBR_BONUS 5

GLuint textureID;
GLFWwindow* window;
int showMenu = 1; // Variable pour afficher ou masquer le menu
int perdu = 0; // Variable pour afficher ou masquer le menu pour le perdant
int gagne = 0; // Variable pour afficher ou masquer le menu pour le gagnant

typedef struct MenuList {
    GLuint textureID;
    float xPos;
    float yPos;
    float width;
    float height;
} MenuList;

Obstacles listeObs[NBR_OBSTACLES];
Bonus listeBonus[NBR_BONUS];
MenuList listeMenu[3];
Ball *ball;
Raquette *raquette;

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


void drawMenuList(MenuList* liste) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, liste->textureID);

    glPushMatrix();
		glTranslatef(1.5, 0., 0.);
		glScalef(0.,5.,5.);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, -1, -1);
			glTexCoord2f(1, 0);
			glVertex3f(0, 1, -1);
			glTexCoord2f(1, 1);
			glVertex3f(0, 1, 1);
			glTexCoord2f(0, 1);
			glVertex3f(0, -1, 1);
		glEnd();
	glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void loadTexture(MenuList* liste, const char* filename) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    glGenTextures(1, &(liste->textureID));
    glBindTexture(GL_TEXTURE_2D, liste->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_J :
				showMenu = 0;
				break;
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
	// newX = xpos;
	// newY = ypos; 
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

void mouse_button(GLFWwindow* window, int button, int action, int mods)
{
	if(!showMenu || !perdu || !gagne){
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
			if(perdUneVie == true || prendSpecialBonus == true || debutBall == true){
				ball->speedX = -0.5;
				ball->speedY = 0.;
				ball->speedZ = 0.;
				perdUneVie = false;
				prendSpecialBonus = false;
				debutBall = false;
			}
		}
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			clickGauche = true;
		}
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
			clickGauche = false;
		}
	}
    
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Rétablir la taille de la fenêtre à sa valeur initiale
    glfwSetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
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

	// Désactiver le redimensionnement de la fenêtre
    glfwSetWindowSizeLimits(window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetCursorPosCallback(window, mouse_mouv);
	glfwSetMouseButtonCallback(window, mouse_button);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	float profondeur=0.;
	float vitesse_corridor=0.2;
	float taille = 1000;
	ball = initBall(0, 0, 0, -0.5, 0., 0., 2);
	raquette = initRaquette(0,0);

	positionObstacles(listeObs, NBR_OBSTACLES);
	positionBonus(listeBonus, NBR_BONUS);
	srand(time(NULL));

	//Charger les textures
	loadTexture(&listeMenu[0], "img/Menu.png");
    loadTexture(&listeMenu[1], "img/MenuG.png");
    loadTexture(&listeMenu[2], "img/MenuP.png");
	
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
		
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */

		if (showMenu) {
            drawMenuList(&listeMenu[0]);
        }

		if (gagne) {
            drawMenuList(&listeMenu[1]);
        }

		if (perdu) {
            drawMenuList(&listeMenu[2]);
        }

		if(debutBall==true){
			colleRaquette(ball, newX, newY);
		}

		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
					
		}
		if(clickGauche==true){
			profondeur +=  vitesse_corridor;
		}

		if(perdUneVie==true){
			colleRaquette(ball, newX, newY);
			raquette->nbrVie -= 1;
		}

		if(raquette->nbrVie==0){
			perdu = 1;
		}

		// if(takeBonus==true){
		// 	prendSpecialBonus = collisionBonus(bonus, ball, raquette, newX, newY);
		// 	supprimerBonusCollision(listeBonus, NBR_BONUS, INDEXAMETTRE);
		// }

		drawCorridor(profondeur, taille);
		//mouvRaquette(*raquette, aspectRatio, newX, newY, WINDOW_WIDTH, WINDOW_HEIGHT, 16., -9.);
		drawRaquette(*raquette, newX, newY);
		drawball(ball);
		//printf("X : %f, Y : %f, Z : %f\n", ball->posY, ball->posZ, ball->posX); 
		//collisions murs
		if(ball->posY - ball->radius < -0.5 * 20 || ball->posY + ball->radius > 0.5 * 20){
            
        	ball->speedY*= -1;
			
        }
        // collisions sol/plafond
        if(ball->posX - ball->radius < -0.5 * taille || ball->posX  + ball->radius> 0.5 * taille){
			if(ball->speedX > 0)
        	ball->speedX *= -1;
    	}
		for(int i=0; i<NBR_OBSTACLES;i++){
				drawObstacles(profondeur,40*(i+1), listeObs[i]);
				// float balle=ball->posX;
				// printf("%f\n",balle);
				// printf("posObstacle1 : %f\n",profondeur-(40*(0+1))+ ball->speedX);
				if(ball->posX - ball->radius <= profondeur-(40*(i+1)) && ball->posX + ball->radius >= profondeur-(40*(i+1)) + 1){
					//fprintf(stdout,"collision profondeur,(%d)\n");
					if(ball->posZ - ball->radius< listeObs[i].x2 && ball->posZ + ball->radius > listeObs[i].x1){
						//fprintf(stdout,"collision largeur,(%d)\n");
						if(ball->posY- ball->radius < listeObs[i].y1  && ball->posY + ball->radius > listeObs[i].y2){
							//fprintf(stdout,"collision hauteur,(%d)\n");
							if (ball->speedX <0) ball->speedX *= -1;
						}
					}
				}
				/*||  ball->posX <= profondeur-(40*(i+1)) -1*/
			// if(ball->posY  listeObs[i].y1 ){
			// 	ball->speedY *= -1;
			// }
			//x1 et y2 négatifs
		}

		//collisions balle/raquette
		
		if(ball->posX + ball->radius > 0){

			if(ball->posZ- ball->radius< newX && ball->posZ + ball->radius > newX ){
				if(ball->posY -ball->radius < newY+raquette->y+1  && ball->posY + ball->radius > newY-raquette->y-1 ){
					if(ball->posZ - ball->radius < raquette->x+1  && ball->posZ + ball->radius > raquette -> x+1 ){
						if(ball->posY - ball->radius < raquette->y+1 && ball->posY + ball->radius > raquette->y-1){
								if(ball->speedX > 0){
									ball->speedX *= -1;
								}
						}
					}
					
				}
			}
			else{

			}
		}
		bool test;
		
		for (int i=1; i<NBR_BONUS;i++){
			glPushMatrix();
				//glRotatef(2.*glfwGetTime(), 1.0, 0.0, 0.0);
				drawBonus(profondeur, 73*(i+1), listeBonus[i]);
			glPopMatrix();
		// collisions balle/bonus
			if(ball->posX - ball->radius <= profondeur-(73*(i+1)) && ball->posX + ball->radius >= profondeur-(73*(i+1)) + 1){
				if(ball->posZ - ball->radius< listeBonus[i].x1 && ball->posZ + ball->radius > listeBonus[i].x2){
						if(ball->posY + ball->radius  <= listeBonus[i].y2   && ball->posY - ball->radius +1 >= listeBonus[i].y1){
							test=true;
						}
					}
				}
		}

		/* Scene rendering */
		
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		
		

		/* Animate scenery */
	}

	glfwTerminate();
	return 0;
}
