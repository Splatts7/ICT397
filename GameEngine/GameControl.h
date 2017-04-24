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
		* @brief Calls GetCam function in GameWorld Engine
		* @param choice - Which camera Vec3 to return
		* @return Vec3 - Chosen camera Vec3 data
		*/
		Vec3 GetCam(int choice);

		/**
		* @brief Calls GetCam function in GameWorld Engine
		* @param choice - Which camera Vec3 to return
		* @param vec - Vec3 data to copy from
		*/
		void SetCam(int choice, Vec3 vec);

	private:
		/// GameWorld object
		GameWorld gameWorld;

};

#endif