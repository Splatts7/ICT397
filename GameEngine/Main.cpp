/*
* Team Quest's Game Engine
*
* Implementation of Main function
* Jack Matters
* Version 01 - Started, set up window creation and main loop
* Date - 13/04/2017
*
* Version 02 - Moved window creation to main, and added Draw, Init, and Reshape functions
* Date - 14/04/2017
*/

#include <stdio.h>
#include <iostream>
#include "GameControl.h"
#include "gl\glut.h"

// GameControl object (Controller for MVC model)
GameControl gameControl;

// Variables to hold screen width and height
int screenW, screenH;
float ratio;

// Function used for calling Draw function from GameWorld Engine
void Display();

// Initialize game window and variables/ objects/ everything else
void Initialize();

// Reshape function for when screen size is altered
void Reshape(int w, int h);


using namespace std;

int main(int argc, char** argv)
{
	// Set screen size from script, and return screen width and height
	gameControl.SetScreen();
	screenW = gameControl.GetScreenW();
	screenH = gameControl.GetScreenH();

	// Create game window, initialize all objects/variables, and enter main game loop
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(screenW,screenH);
	glutCreateWindow("Graphics Engine");
	glutReshapeFunc(Reshape);
	Initialize();
	glutDisplayFunc(Display); 
	glutIdleFunc(Display);	

	//glutKeyboardFunc(keyboardInput);        /* key pressed */
	//glutKeyboardUpFunc(keyboardRelease);    /* key released */
	//glutPassiveMotionFunc(mouseMovement);   /* camera look at position */

	glutMainLoop();

	return 0;
}

// Display the game by calling the Draw function in the GameControl Engine
// Note - Had to do it this way, as glutDisplayFunc() could not take in a function from another
//		  class that isn't static
void Display()
{
	gameControl.Draw();
}

// Initialize game
void Initialize()
{
	// White background
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// set perpsective
	gluLookAt(0.0, 1.75, 0.0,
		0.0, 1.75, -1,
		0.0f,1.0f,0.0f);

	// Other initializations
}

// Reshape screen size when window size is altered
void Reshape(int w, int h)
{
	// Reset screen ratio
	if (h == 0) 
		h = 1;
	screenW = w;
	screenH = h;
	ratio = 1.0f * w / h;

	// Reset view matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,250000);
	glMatrixMode(GL_MODELVIEW);
}
