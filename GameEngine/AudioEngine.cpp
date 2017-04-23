/*
* Implementation of Camera.h file
* Author - Jack Matters
*/

#include "AudioEngine.h"

#define FREQUENCY 44100
#define CHANNELS 2		/* 1 for mono, 2 for stereo */
#define SAMPLESIZE 4096

// Default constructor
AudioEngine::AudioEngine()
{
	success = true;
	gMusic = NULL;
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;
	
	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, SAMPLESIZE ) < 0 )
    {
	    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
}

// Deconstructor
AudioEngine::~AudioEngine()
{
	UnloadMedia();
}

// Load media
bool AudioEngine::LoadMedia()
{
	L = lua_open();
	luaL_openlibs(L);

	if (luaL_dofile(L, "Scripts/GameSounds.lua"))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L,"numSounds");

	int numSounds = lua_tonumber(L,1);
	std::string one;
	std::list<std::string> songList;

	for(int i = 0; i < numSounds; i++)
	{
		lua_getglobal(L,"fileName");
		one = lua_tostring(L,2+i);
		songList.push_back(one);
	}
	/*lua_getglobal(L,"height");
	lua_getglobal(L,"xposition");
	lua_getglobal(L,"yposition");*/

	// Set positions
	//screenWidth = lua_tonumber(L,1);
	//screenHeight = lua_tonumber(L,2);

	lua_close(L);



	//Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS( "Sounds/Alice.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gScratch = Mix_LoadWAV( songList.front().c_str() );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gHigh = Mix_LoadWAV( songList.back().c_str() );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( "Sounds/medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gLow = Mix_LoadWAV( "Sounds/low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

// Unload all media
void AudioEngine::UnloadMedia()
{
    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    SDL_Quit();
}

// Play a sound
void AudioEngine::PlaySound()
{
	
	Mix_Volume(-1, 20);
	//Mix_PlayChannel( -1, gHigh, -1 );
	//Mix_PlayChannel( -1, gMedium, -1 );
	//Mix_PlayChannel( -1, gLow, -1 );
	Mix_PlayChannel( -1, gScratch, -1 );

	Mix_VolumeMusic(20);
	//Mix_PlayMusic( gMusic, -1 );
}