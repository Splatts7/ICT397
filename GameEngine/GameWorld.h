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
*/

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

//#include "Audio.h"
//#include "Animation.h"
#include "GraphicsEngine.h"
//#include "AI.h"
#include "Input.h"
//#include "Physics.h"
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

		/// Lua state
		lua_State* L;

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
		//GameWorld(Camera *c);

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
		* @brief Public Prepare function that calls protected one
		*/
		void Prepare();

		/**
		* @brief Fades the screen in/out
		*/
		void FadeScreen();

		/**
		* @brief Sets the screen size
		* @param width - Width of screen
		* @param height - Height of screen
		*/
		void SetScreen();

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

		/// Camera object
		//Camera *camera;

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