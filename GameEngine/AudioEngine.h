/**
* @class AudioEngine
* @brief Audio engine to handle all game sounds
* @author Jack Matters
* @version 01 - Started
* @date 18/04/2017
* @note Reference - http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
* @note Sound files - http://www.wavsource.com/sfx/sfx.htm
*					- https://www.freesound.org/browse/
*/

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "lua.hpp"

class AudioEngine
{
	public:

		/**
		* @brief Defualt constructor
		*/
		AudioEngine();

		/**
		* @brief Deconstructor
		*/
		~AudioEngine();

		/**
		* @brief Load music
		* @return success - True if loaded, false otherwise
		*/
		bool LoadMedia();

		/**
		* @brief Unload all audio
		*/
		void UnloadMedia();

		/**
		* @brief Plays audio
		*/
		void PlaySound();


	private:

		/// Determine if loading worked or failed
		bool success;

		//The music that will be played
		Mix_Music *gMusic;

		//The sound effects that will be used
		Mix_Chunk *gScratch;
		Mix_Chunk *gHigh;
		Mix_Chunk *gMedium;
		Mix_Chunk *gLow;

		/// Lua state for reading in sound files
		lua_State* L;

};

#endif