/**
* @class GameControl
* @brief GameControl engine that that is the Controller in the Model-View-Controller concept
* @author Jack Matters, Jonathan Sands
* @version 01 - Started
* @date 13/04/2017
*
* @version 02 - Added functions to set screen size, and return screen width and height from GameWorld Engine
* @date - 14/04/2017
*
* @version 03 - Added functions to return input read from keyboard and mouse from Input Engine
* @date - 14/04/2017
*
* @version 04 - Added functions for camera creation and returning of camera values
* @date - 18/04/2017
*/

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "GameWorld.h"
#include "Input.h"

class GameControl
{
	public:

		/**
		* @brief Default constructor
		*/
		GameControl();

		/**
		* @brief De-constructor
		*/
		~GameControl();

		/**
		* @brief Calls SetScreen function in GameWorld Engine
		*/
		void SetScreen();

		/**
		* @brief Calls GetScreenW function in GameWorld Engine
		* @return screenWidth from GameWorld Engine
		*/
		int GetScreenW();

		/**
		* @brief Calls GetScreenH function in GameWorld Engine
		* @return screenHeight from GameWorld Engine
		*/
		int GetScreenH();

		/**
		* @brief Calls Draw function in GameWorld Engine
		*/
		void Draw();

		/**
		* @brief Calls CreateCam function in GameWorld Engine
		*/
		void CreateCam();

		/**
		* @brief Calls CreateCam function in GameWorld Engine
		* @param choice - Which camera Vec3 to return
		*/
		Vec3 GetCam(int choice);

		/**
		* @brief Calls pressKeys function in Input Engine
		* @param key - Key pressed
		* @param xx - The mouse x-coordinate in window relative coordinates
		* @param yy - The mouse y-coordinate in window relative coordinates
		*/
		void KeyboardPress(unsigned char key, int xx, int yy);

		/**
		* @brief Calls releaseKeys function in Input Engine
		* @param key - Key released
		* @param xx - The mouse x-coordinate in window relative coordinates
		* @param yy - The mouse y-coordinate in window relative coordinates
		*/
		void KeyboardRelease(unsigned char key, int xx, int yy);

		/**
		* @brief Calls moveMouse function in Input Engine
		* @param x - The mouse x-coordinate in window relative coordinates
		* @param y - The mouse y-coordinate in window relative coordinates
		*/
		void MouseMovement(int x, int y);

		/**
		* @brief Calls pressMouseButton function in Input Engine
		* @param button - Mouse button pressed
		* @param state - State of mouse button (up or down)
		* @param x - The mouse x-coordinate in window relative coordinates
		* @param y - The mouse y-coordinate in window relative coordinates
		*/
		void MouseButton(int button, int state, int x, int y);

	private:

		/// GameWorld object
		GameWorld gameWorld;

		/// Input object
		Input input;

};

#endif