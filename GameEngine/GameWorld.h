/**
* @class GameWorld
* @brief Game World Engine
* @author Jack Matters
* @version 01 - Started, layout taken from lecture slides
* @date 31/03/2017
*
* @version 02 - Small modifications
* @date 01/04/2017 
* @note Most of these functions will call functions from other classes/engines (unless I am mistaken),
*		so I have left the initializations in the .cpp file blank but ready to be used
*
* @version 03 - Added functions to return screen height and width
* @date 14/04/2017
*
* @version 04 - Added functions to create camera object, reading data from script
* @date 18/04/2017
*/

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "AudioEngine.h"
//#include "Animation.h"
#include "GraphicsEngine.h"
//#include "AI.h"
//#include "Input.h"
//#include "Physics.h"
#include "Camera.h"
#include "GameAssetFactory.h"
#include "Texture.h"
#include "lua.hpp"

class GameWorld
{
	private:
		/// Number of NPCs
		int numNpcs;

		/// Width of the screen
		int screenWidth;
		
		/// Height of the screen
		int screenHeight;

		/// Variable for determining if game is done (true) or not (false)
		bool gameDone;

		/// GraphicsEngine object
		GraphicsEngine graphicsEngine;

		/// GameAssetFactory object
		GameAssetFactory GAF;

		/// Camera object
		GameObject* cam;

		/// Camera position
		Vec3 pos;

		/// Camera lookat
		Vec3 look;

		/// Camera up vec
		Vec3 up;

		/// Lua state
		lua_State* L;

		/// Texture object for GUI elements
		Texture guiObject;

	protected:

		/**
		* @brief Called by public Animate function, does physics calculations
		* @param deltaTime - Time passed since last call
		*/
		void OnAnimate(float deltaTime);

		/**
		* @brief Called by public Draw function, renders the world
		* @param camera - The camera object
		*/
		//void OnDraw(Camera *camera);

		/**
		* @brief 
		*/
		void OnPrepare();

	public:
		
		/**
		* @brief Default constructor
		*/
		GameWorld();

		/**
		* @brief Non-default constructor
		* @param c - Camera object
		*/
		//GameWorld(Camera *camera);

		/**
		* @brief De-constructor
		*/
		~GameWorld();

		/**
		* @brief Returns the screen width
		* @return screenWidth
		*/
		int GetScreenW();

		/**
		* @brief Returns the screen height
		* @return screenHeight
		*/
		int GetScreenH();

		/**
		* @brief Initialize terrain, load all objects, and put in container
		*/
		void LoadWorld();

		/**
		* @brief Unload all objects, terrain, and remove container
		*/
		void UnloadWorld();

		/**
		* @brief Countnumber of objects of type 'classID' in world
		* @parm classID - Counts number of objects in game world
		* @return int - Number of objects
		*/
		int CountObjectTypes(const type_info &classID);

		/**
		* @brief Public Animate function that calls protected one
		* @param deltaTime - The amount of time passed since last call
		*/
		void Animate(float deltaTime);

		/**
		* @brief Public Draw function that calls protected one
		* @param camera - Camera object
		*/
		//void Draw(Camera *camera);

		/**
		* @brief Initialize GUI, load all splash screens
		*/
		void DisplayGUI();

		/**
		* @brief Public Prepare function that calls protected one
		*/
		void Prepare();

		/**
		* @brief Fades the screen in/out
		*/
		void FadeScreen();

		/**
		* @brief Sets the screen size, reading data from script
		*/
		void SetScreen();

		/**
		* @brief Creates the camera object, reading data from script
		*/
		void CreateCam();

		/**
		* @brief Returns Vec3 values of the camera, depending on choice input
		* @param choice - Vec3 to return
		* @return Vec3 - Chosen camera Vec3 data
		*/
		Vec3 GetCam(int choice);

		/**
		* @brief Sets Vec3 values of the camera, depending on choice input
		* @param choice - Vec3 to return
		* @param vec - Vec3 data to copy from
		*/
		void SetCam(int choice, Vec3 vec);

		/**
		* @brief Determine if game is done/quit by player
		* @return bool - True if gameDone, false otherwise
		*/
		bool IsGameDone();

		/**
		* @brief Sets gameDone to true
		*/
		void QuitGame();

		/**
		* @brief Getter function that returns number of NPCs
		* @return int - Number of NPCs
		*/
		int GetNpcs();

		/// Terrain object
		//Terrain *terrain;

		/// Player object (don't think we need, player will be camera)
		//Player *player;

		/// Audio system object
		//AudioSystem *audioSystem;

		/// World ambient sound object
		//Audio *worldSound;

		/// GUI object
		//GUI *gui;

		/// Levels object
		//Levels *levels;

		/// Enemy object (don't think we need)
		//Enemy *NPC;

		/// The time the game started
		float timeStart;

		/// The time passed since game started
		float timeElapsed;
};

#endif