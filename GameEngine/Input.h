/**
* @class Input
* @brief Input class that handles user input
* @author Jonathan Sands, Jack Matters
* @version 01 Started
* @date 14/04/2017
*
* @version 02 Added in code to allow current camera data to be read in, altered, and set to the new values (just example code, Jonathan will do the rest)
* @date 19/04/2017
*
* @version 03 Jack took over while Jonathan works on other sections. Added and altered code from previous units to allow camera rotation via mouse and 
*			  movement via keyboard
* @date 22/04/2017
*/

#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "gl/glut.h"
#include "lua.hpp"
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
		* @brief Moves the camera according to user input via mouse
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

		/**
		* @brief Moves the camera according to user input via keyboard
		*/
		void MoveCamera();

		/// Flag to display game manual
		bool displayManual;

		/// Flag to display exit splash screen
		bool displayExit;

	private:


		/// Flag to display wire frames
		bool displayWireframe;

		/// Camera position
		Vec3 pos;

		/// Camera rotation
		Vec3 rotation;
		
		/// Camera angle
		Vec3 deltaAngle;

		/// Camera rotation speed
		float rotSpeed;

		/// Camera move speed
		float moveSpeed;

		/// Rotation around y-axis in radians
		float radRotY;

		/// Forward(1) and backward(2) movement
		int move;

		/// Left(1) and right(2) strafe
		int strafe;

		/**
		* @brief Translates the camera's position and rotation angle
		*/
		void TranslateCam();

		/**
		* @brief Moves camera forward and back
		* @param direction - 1 for forward, 2 for backward
		*/
		void ComputeCamFB(int direction);

		/**
		* @brief Strafes the camera left and right
		* @param direction - 1 for left, 2 for right
		*/
		void ComputeCamLR(int direction);
};

#endif