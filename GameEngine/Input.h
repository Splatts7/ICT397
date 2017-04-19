/**
* @class Input
* @brief Input class that handles user input
* @author Jonathan Sands, Jack Matters
* @version 01 Started
* @date 14/04/2017
*
* @version 02 Added in code to allow current camera data to be read in, altered, and set to the new values (just example code, Jonathan will do the rest)
* @date 19/04/2017
*/

#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include "gl/glut.h"
#include <math.h>
#include "GameControl.h"

class Input
{
	public:

		/**
		* @brief Default constructor
		*/
		Input();

		/**
		* @brief De-constructor
		*/
		~Input();

		/**
		* @brief Responds to keyboard key input
		* @param key - Key pressed
		* @param xx - The mouse x-coordinate in window relative coordinates
		* @param yy - The mouse y-coordinate in window relative coordinates
		*/
		void pressKeys(unsigned char key, int xx, int yy);

		/**
		* @brief Responds to keyboard key being released
		* @param key - Key pressed
		* @param xx - The mouse x-coordinate in window relative coordinates
		* @param yy - The mouse y-coordinate in window relative coordinates
		*/
		void releaseKeys(unsigned char key, int xx, int yy);

		/**
		* @brief Responds to mouse movement input
		* @param x - The mouse x-coordinate in window relative coordinates
		* @param y - The mouse y-coordinate in window relative coordinates
		*/
		void moveMouse(int x, int y);

		/**
		* @brief Responds to mouse button input
		* @param button - Mouse button pressed
		* @param state - State of mouse button (up or down)
		* @param x - The mouse x-coordinate in window relative coordinates
		* @param y - The mouse y-coordinate in window relative coordinates
		*/
		void pressMouseButton(int button, int state, int x, int y);

	private:

		/// Angle of rotation for the camera direction
		float cameraAngle;

		/// Actual vector representing the camera's direction
		float cameraLX, cameraLZ;

		// XZ position of the camera
		float cameraX, cameraZ;

		/// The key states. These variables will be zero when no key is being presses
		float deltaAngle;
		float deltaMove;
		int xOrigin;

		/// Boolean values to check for different modes
		bool displayManual;
		bool displayWireframe;
		bool displayExit;

		/// Camera position and lookat
		Vec3 pos, look;
};

#endif