/*
* Implementation of GameWorld.h file
* Jack Matters
* Version 01 - Started
* Date - 31/03/2017
*
* Version 02 - Small modifications
* Date - 01/04/2017
*/

#include "GameWorld.h"

// Default constructor
GameWorld::GameWorld()
{
	numNpcs = 0;
	screenWidth = 100;
	screenHeight = 100;
	gameDone = false;
	// Other initialisations
}

// Non-default constructor
//GameWorld::GameWorld(Camera* c)
//{
//	numNpcs = 0;
//	screenWidth = 100;
//	screenHeight = 100;
//	gameDone = false;
//	// Other initialisations
//}

// De-constructor
GameWorld::~GameWorld(){}

// Load the world
void GameWorld::LoadWorld(){};

// Unload world
void GameWorld::UnloadWorld(){};

// Count number of objects of type classID
int GameWorld::CountObjectTypes(const type_info &classID)
{
	return 1;
};

// Call protected Animate function
void GameWorld::Animate(float deltaTime)
{
	OnAnimate(deltaTime);
}

// Animate objects, check physics and collisions
void GameWorld::OnAnimate(float deltaTime){}

// Call protected Draw function
//void Draw(Camera *camera)
//{
//	OnDraw(camera);
//}

// Render the world
//void GameWorld::OnDraw(Camera *camera){}

// Call protected Prepare function
void GameWorld::Prepare()
{
	OnPrepare();
}

//
void GameWorld::OnPrepare(){}

// Fade the screen in/out
void GameWorld::FadeScreen(){}

// Set the screen size
void GameWorld::SetScreen(int width, int height)
{
	// Call graphics engine? as it uses OpenGL which is needed to create window
}

// Determine if game is done
bool GameWorld::IsGameDone()
{
	return gameDone;
}

// Called if game completed/player quits
void GameWorld::QuitGame()
{
	gameDone = true;
}

// Return number of NPCs
int GameWorld::GetNpcs()
{
	return numNpcs;
}