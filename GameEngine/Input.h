/**
* @class Input
* @brief Input class that handles user input
* @author Jonathan Sands
* @version 01 Started
* @date 14/04/2017
*
*/

#ifndef INPUT_H
#define INPUT_H

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
		*/
		void Input::pressKeys(unsigned char key, int xx, int yy);

		/**
		* @brief Responds to keyboard key being released
		*/
		void Input::releaseKeys(unsigned char key, int xx, int yy);

		/**
		* @brief Responds to mouse movement input
		*/
		void Input::moveMouse(int x, int y);

		/**
		* @brief Responds to mouse button input
		*/
		void Input::pressMouseButton(int button, int state, int x, int y);

	private:
		// Angle of rotation for the camera direction
		float cameraAngle;

		// Actual vector representing the camera's direction
		float cameraLX, cameraLZ;

		// XZ position of the camera
		float cameraX, cameraZ;

		// The key states. These variables will be zero
		// when no key is being presses
		float deltaAngle;
		float deltaMove;
		int xOrigin;

		// Boolean values to check for different modes
		bool displayManual;
		bool displayWireframe;
		bool displayExit;
};

#endif