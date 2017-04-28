/*
* Team Quest's Game Engine
*
* Implementation of Main function
* Author - Jack Matters, Jonathan Sands
* Version 01 - Started, set up window creation and main loop
* Date - 13/04/2017
*
* Version 02 - Moved window creation to main, and added Draw, Init, and Reshape functions
* Date - 14/04/2017
*
* Version 03 - Added keyInput, keyRelease, mouseMove, and mouseButton functions
* Date - 14/04/2017
*
* Version 04 - Altered initialize function to set starting gluLookAt to data read from script
* Date - 18/04/2017
*
* Version 05 - Mouse cursor is now hidden while running
* Date - 23/04/2017
*/

#include <stdio.h>
#include <iostream>
#include "GameControl.h"
#include "Input.h"
#include "AudioEngine.h"
#include "gl/glut.h"

// GameControl object (Controller for MVC model)
GameControl gameControl;

// Input object
Input input;

// Variables to hold screen width and height
int screenW, screenH;
float ratioT;

// Function used for calling Draw function from GameWorld Engine
void Display();

// Initialize game window and variables/ objects/ everything else
void Initialize();

// Reshape function for when screen size is altered
void Reshape(int w, int h);

// Handle input via keyboard when button pressed
void keyInput(unsigned char key, int xx, int yy);

// Handle input via keyboard when button released
void keyRelease(unsigned char key, int xx, int yy);

// Handle input via mouse when moved
void mouseMove(int x, int y);

// Handle input via mouse when button pressed
void mouseButton(int button, int state, int x, int y);


using namespace std;


int main(int argc, char** argv)
{
	// Set screen size from script, and return screen width and height
	gameControl.SetScreen();
	screenW = gameControl.GetScreenW();
	screenH = gameControl.GetScreenH();

	// Audio engine testing (not added to Assignment 1, will add to Assignment 2)
	//AudioEngine audio;
	//audio.LoadMedia();
	//audio.PlaySound();

	// Create game window, initialize all objects/variables, and enter main game loop
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(screenW,screenH);
	glutCreateWindow("Graphics Engine");
	glutReshapeFunc(Reshape);
	Initialize();

	glutKeyboardUpFunc(keyRelease);  
	glutKeyboardFunc(keyInput);      	
	glutMouseFunc(mouseButton);		   
	glutPassiveMotionFunc(mouseMove); 

	glutDisplayFunc(Display); 
	glutIdleFunc(Display);	

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
	glClearColor(0.3, 0.0, 0.0, 1.0);

	// Create camera object
	gameControl.CreateCam();
	Vec3 pos = gameControl.GetCam(1);
	Vec3 look = gameControl.GetCam(2);
	Vec3 up = gameControl.GetCam(3);

	// Center and hide cursor
	glutWarpPointer(screenH/2, screenW/2);
	glutSetCursor(GLUT_CURSOR_NONE);

	// Set view perspective
	gluLookAt(pos.x, pos.y, pos.z,
		look.x, look.y, look.z,
		up.x, up.y, up.z);

	// Other initializations
	gameControl.Prepare();
}

// Reshape screen size when window size is altered
void Reshape(int w, int h)
{
	// Reset screen ratio
	if (h == 0) 
		h = 1;
	screenW = w;
	screenH = h;
	ratioT = 1.0f * w / h;

	// Reset view matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratioT,1,250000);
	glMatrixMode(GL_MODELVIEW);
}

// Handle input via keyboard when button pressed
void keyInput(unsigned char key, int xx, int yy)
{
	input.pressKeys(key, xx, yy);
}

// Handle input via keyboard when button released
void keyRelease(unsigned char key, int xx, int yy)
{
	input.releaseKeys(key, xx, yy);
}

// Handle input via mouse when moved
void mouseMove(int x, int y)
{
	input.moveMouse(x, y);
}

// Handle input via mouse when button pressed
void mouseButton(int button, int state, int x, int y)
{
	input.pressMouseButton(button, state, x, y);
}
