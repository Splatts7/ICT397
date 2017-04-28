/*
* Implementation of GameControl.h file
* Author - Jack Matters, Jonathan Sands
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
void GameControl::Draw()
{
	gameWorld.Draw();
}

// Call CreateCam function in GameWorld Engine
void GameControl::CreateCam()
{
	gameWorld.CreateCam();
}

// Call GetCam function in GameWorld Engine
Vec3 GameControl::GetCam(int choice)
{
	return gameWorld.GetCam(choice);
}

// Call SetCam function in GameWorld Engine
void GameControl::SetCam(int choice, Vec3 vec)
{
	gameWorld.SetCam(choice, vec);
}

// Initialize all data before running game
void GameControl::Prepare()
{
	gameWorld.Prepare();
}