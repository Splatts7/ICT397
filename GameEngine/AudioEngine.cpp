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
	// Open lua state
	L = lua_open();
	luaL_openlibs(L);

	// Open script
	if (luaL_dofile(L, "Scripts/GameSounds.lua"))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L,"numSounds");
	lua_getglobal(L, "sounds");

	int numSounds = lua_tonumber(L,1);
	std::string one;
	std::string sound;
	std::vector<std::string> songList;

	// Read all sounds from list in script and put into a vector
	lua_pushnil(L);
    while (lua_next(L, -2) != 0) 
	{
        sound = lua_tostring(L, -1);
		songList.push_back(sound);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

	// Close the lua state
	lua_close(L);



	//Loading success flag
    bool success = true;

    //Load music
    /*gMusic = Mix_LoadMUS( "Sounds/Alice.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }*/
    
    //Load sound effects
    gScratch = Mix_LoadWAV( songList[0].c_str() );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gHigh = Mix_LoadWAV( songList[1].c_str() );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( songList[2].c_str() );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gLow = Mix_LoadWAV( songList[3].c_str() );
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
void AudioEngine::PlaySounds()
{
	
	Mix_Volume(-1, 20);
	//Mix_PlayChannel( -1, gScratch, -1 );
	Mix_PlayChannel( -1, gHigh, -1 );
	//Mix_PlayChannel( -1, gMedium, -1 );
	//Mix_PlayChannel( -1, gLow, -1 );

	Mix_VolumeMusic(20);
	//Mix_PlayMusic( gMusic, -1 );
}