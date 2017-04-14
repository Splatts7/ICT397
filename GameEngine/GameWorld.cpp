/*
* Implementation of GameWorld.h file
* Author - Jack Matters
*/

#include "GameWorld.h"
//#include <iostream>

// Default constructor
GameWorld::GameWorld()
{
	numNpcs = 0;
	screenWidth = 100;
	screenHeight = 100;
	gameDone = false;
	// Other initialisations

	// Lua initializations (might need to put this in every function that reads a script instead of having only one state?)
	L = lua_open();
	luaL_openlibs(L);
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

// Return screen width
int GameWorld::GetScreenW()
{
	return screenWidth;
}

// Return screen height
int GameWorld::GetScreenH()
{
	return screenHeight;
}

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
// Note - currently used for testing purposes
void GameWorld::OnPrepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Front wall
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.0);   //dark green
    glVertex3f(10.0, 10.0, -100.0);   //TL
    glVertex3f(10.0, -10.0, -100.0);   //BL
    glVertex3f(-10.0, -10.0, -100.0);   //BR
    glVertex3f(-10.0, 10.0, -100.0);   //TR
    glEnd();

    ////Back wall
    //glBegin(GL_POLYGON);
    //glColor3f(1.0, 0.0, 0.0);   //red
    //glVertex3f(-20.0, 30.0, -30.0);    //TL
    //glVertex3f(20.0, 30.0, -30.0);   //TR
    //glVertex3f(20.0, 0.0, -30.0);    //BR
    //glVertex3f(-20.0, 0.0, -30.0);     //BL
    //glEnd();

    ////left wall
    //glBegin(GL_POLYGON);
    //glColor3f(0.0, 0.0, 1.0);   //blue
    //glVertex3f(-20.0, 0.0, 0.0);        //BR
    //glVertex3f(-20.0, 30.0, 0.0);       //TR
    //glVertex3f(-20.0, 30.0, -30.0);    //TL
    //glVertex3f(-20.0, 0.0, -30.0);     //BL
    //glEnd();

    ////right wall
    //glBegin(GL_POLYGON);
    //glColor3f(0.0, 1.0, 1.0);   //cyan
    //glVertex3f(20.0, 30.0, 0.0);      //TL
    //glVertex3f(20.0, 0.0, 0.0);       //BL
    //glVertex3f(20.0, 0.0, -30.0);    //BR
    //glVertex3f(20.0, 30.0, -30.0);   //TR
    //glEnd();

	glutSwapBuffers();
    glFlush();
}

// Fade the screen in/out
void GameWorld::FadeScreen(){}

// Set the screen size
// Note - Not sure if able to have one instance of lua state for each script, or if each script requires its own state
//		  Therefore, commented code may still be required here. Also not too sure how to go about error checking as
//		  adding in #include <iostream> causes errors
void GameWorld::SetScreen()
{
	// Load script
	//lua_State* L = lua_open();
	/*if (L == NULL)
	{
		std::cout << "Error Initializing lua.." << std::endl;
		return -1;
	}*/

	// Load standard lua library functions
	//luaL_openlibs(L);
	// Load and run script
	if (luaL_dofile(L, "../Scripts/GameWindow.lua"))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L,"width");
	lua_getglobal(L,"height");
	lua_getglobal(L,"xposition");
	lua_getglobal(L,"yposition");

	// Set positions
	screenWidth = lua_tonumber(L,1);
	screenHeight = lua_tonumber(L,2);
	
	// Close lua state? Or can it stay open until program ends/ all scripts read?
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