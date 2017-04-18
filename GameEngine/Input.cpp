/*
* Implementation of Input.cpp file
* Author - Jonathan Sands
*/

#include "Input.h"

// Default constructor
Input::Input(){};

// De-constructor
Input::~Input(){};
/*
void computePos(float deltaMove)
{
	cameraX += deltaMove * cameraLX * 0.1f;
	cameraZ += deltaMove * cameraLZ * 0.1f;
}
*/
// Responds to keyboard key input
void Input::pressKeys(unsigned char key, int xx, int yy)
{ 	
        switch (key) {
			case 'w':
			case 'W':
				// Move forward
				deltaMove = 0.5f;
				break;
			case 's':
			case 'S':
				// Move backward
				deltaMove = -0.5f;
				break;
			case 'a':
			case 'A':
				// Strafe to the left
				
				break;
			case 'd':
			case 'D':
				// Strafe to the right
				
				break;
			case 'm':
			case 'M':
				// Show manual if not already displayed, otherwise hide it
				if (displayManual) {
					
					displayManual = false;
				}
				else {
					
					displayManual = true;
				}
				break;
			case 'k':
			case 'K':
				// Switch between wireframe and full rendering
				if (displayWireframe) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					displayWireframe = false;
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					displayWireframe = true;
				}
				break;
			case 'x':
			case 'X':
				// Show exit splash screen if not already displayed, otherwise hide it
				if (displayExit) {
					
					displayExit = false;
				}
				else {
					
					displayExit = true;
				}
				break;
       }
}

// Responds to keyboard key being released
void Input::releaseKeys(unsigned char key, int xx, int yy)
{ 	
        switch (key) {
			case 'w':
			case 'W':
			case 's':
			case 'S':
				// Halt forward or backward movement
				deltaMove = 0;
				break;
        }
} 

// Responds to mouse movement input
void Input::moveMouse(int x, int y)
{ 	
	// Update deltaAngle
	deltaAngle = (x - xOrigin) * 0.010f;

	// Update camera's direction
	cameraLX = sin(cameraAngle + deltaAngle);
	cameraLZ = -cos(cameraAngle + deltaAngle);
}

// Responds to mouse button input
void Input::pressMouseButton(int button, int state, int x, int y)
{
	// If the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// Close the program if exit splash screen is showing
		if (displayExit) {
			exit(0);
		}
		// when the button is released
		if (state == GLUT_UP) {

		}
		else {// state = GLUT_DOWN
			
		}
	}
}