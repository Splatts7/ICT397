/*
* Implementation of Input.cpp file
* Author - Jonathan Sands
*/

#include "Input.h"
#include "gl/glut.h"
#include <math.h>

// Default constructor
Input::Input(){};

// De-constructor
Input::~Input(){};

void Input::pressKeys(unsigned char key, int xx, int yy) { 	

        switch (key) {
			case 'w':
			case 'W':
				deltaMove = 0.5f;
				break;
			case 's':
			case 'S':
				deltaMove = -0.5f;
				break;
			case 'a':
			case 'A':
				
				break;
			case 'd':
			case 'D':
				
				break;
			case 'm':
			case 'M':
				if (displayManual) {
					
					displayManual = false;
				}
				else {
					
					displayManual = true;
				}
				break;
			case 'k':
			case 'K':
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
				if (displayExit) {
					
					displayExit = false;
				}
				else {
					
					displayExit = true;
				}
				break;
       }
}

void Input::releaseKeys(unsigned char key, int xx, int yy) { 	

        switch (key) {
			case 'w':
			case 'W':
			case 's':
			case 'S':
				deltaMove = 0;
				break;
        }
} 

void Input::moveMouse(int x, int y) { 	
	// Update deltaAngle
	deltaAngle = (x - xOrigin) * 0.010f;

	// Update camera's direction
	cameraLX = sin(cameraAngle + deltaAngle);
	cameraLZ = -cos(cameraAngle + deltaAngle);
}

void Input::pressMouseButton(int button, int state, int x, int y) {

	// If the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
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