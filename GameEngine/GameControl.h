/**
* @class GameControl
* @brief GameControl engine that that is the Controller in the Model-View-Controller concept
* @author Jack Matters
* @version 01 - Started
* @date 13/04/2017
*
* @version 02 - Added functions to set screen size, and return screen width and height from GameWorld Engine
* @date - 14/04/2017
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

	private:

		/// GameWorld object
		GameWorld gameWorld;

};

#endif