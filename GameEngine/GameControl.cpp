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
// Note - Will call Draw function once we get that far, Prepare function used for testing
void GameControl::Draw()
{
	//gameWorld.Draw();
	gameWorld.Prepare();
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

// Call the pressKeys function in the Input Engine
void GameControl::KeyboardPress(unsigned char key, int xx, int yy)
{
	input.pressKeys(key, xx, yy);
}

// Call the releaseKeys function in the Input Engine
void GameControl::KeyboardRelease(unsigned char key, int xx, int yy)
{
	input.releaseKeys(key, xx, yy);
}

// Call the moveMouse function in the Input Engine
void GameControl::MouseMovement(int x, int y)
{
	input.moveMouse(x, y);
}

// Call the pressMouseButton function in the Input Engine
void GameControl::MouseButton(int button, int state, int x, int y)
{
	input.pressMouseButton(button, state, x, y);
}