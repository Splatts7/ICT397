/*
* Implementation of GameControl.h file
* Author - Jack Matters
*/

#include "GameControl.h"

// Default constructor
GameControl::GameControl(){};

// De-constructor
GameControl::~GameControl(){};

// Calls GameWorld Engine SetScreen function
void GameControl::SetScreen()
{
	gameWorld.SetScreen();
}

// Returns screen width stored in GameWorld Engine
int GameControl::GetScreenW()
{
	return gameWorld.GetScreenW();
}

// Returns screen height stored in GameWorld Engine
int GameControl::GetScreenH()
{
	return gameWorld.GetScreenH();
}

// Call the Draw function in the GameWorld Engine
// Note - Will call Draw function once we get that far, Prepare function used for testing
void GameControl::Draw()
{
	//gameWorld.Draw();
	gameWorld.Prepare();
}
