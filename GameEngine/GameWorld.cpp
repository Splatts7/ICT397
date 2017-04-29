/*
* Implementation of GameWorld.h file
* Author - Jack Matters
*/

#include "GameWorld.h"
#include "Camera.h"
#include "Input.h"
//#include <iostream>

// Default constructor
GameWorld::GameWorld()
{
	numNpcs = 0;
	screenWidth = 100;
	screenHeight = 100;
	gameDone = false;
	// Other initialisations

	// Initialize camera variables
	cam = new Camera();
	pos = Vec3();
	look = Vec3();
	up = Vec3();

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
void GameWorld::LoadWorld()
{

};

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

// Load the GUI
void GameWorld::DisplayGUI()
{
	extern Input input;
	GLuint texManual, texExit;
	texManual = guiObject.LoadTexture("Textures/Manual.raw", 600, 600);
	Vec3 temp = look;
	if (input.displayManual){
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texManual);
		glColor3f(1.0, 1.0, 1.0);
		glBegin (GL_QUADS);
			glTexCoord2d(0.0,1.0); glVertex3f(200.0,0.0,0.0);
			glTexCoord2d(1.0,1.0); glVertex3f(800.0,0.0,0.0);
			glTexCoord2d(1.0,0.0); glVertex3f(800.0,600.0,0.0);
			glTexCoord2d(0.0,0.0); glVertex3f(200.0,600.0,0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	texExit = guiObject.LoadTexture("Textures/Exit.raw", 600, 600);
	if (input.displayExit){
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texExit);
		glColor3f(1.0, 1.0, 1.0);
		glBegin (GL_QUADS);
			glTexCoord2d(0.0,1.0); glVertex3f(200.0,0.0,0.0);
			glTexCoord2d(1.0,1.0); glVertex3f(800.0,0.0,0.0);
			glTexCoord2d(1.0,0.0); glVertex3f(800.0,600.0,0.0);
			glTexCoord2d(0.0,0.0); glVertex3f(200.0,600.0,0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
};

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

	extern Input input;
	input.MoveCamera();

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

	DisplayGUI();

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
	if (luaL_dofile(L, "Scripts/GameWindow.lua"))
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

// Creates the game camera object
// Note - Not sure if able to have one instance of lua state for each script, or if each script requires its own state
//		  Therefore, commented code may still be required here. Also not too sure how to go about error checking as
//		  adding in #include <iostream> causes errors
void GameWorld::CreateCam()
{
	// Make camera object
	cam = GAF.Create("CAMERA");
	Vec3 temp;

	// Read in starting camera values from script
	if (luaL_dofile(L, "Scripts/Camera.lua"))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L,"camx");
	lua_getglobal(L,"camy");
	lua_getglobal(L,"camz");
	lua_getglobal(L,"lookx");
	lua_getglobal(L,"looky");
	lua_getglobal(L,"lookz");
	lua_getglobal(L,"upx");
	lua_getglobal(L,"upy");
	lua_getglobal(L,"upz");

	// Set cam position
	temp.x = lua_tonumber(L,1);
	temp.y = lua_tonumber(L,2);
	temp.z = lua_tonumber(L,3);
	cam->Set(1, temp);

	// Set cam lookat
	temp.x = lua_tonumber(L,4);
	temp.y = lua_tonumber(L,5);
	temp.z = lua_tonumber(L,6);
	cam->Set(2, temp);

	// Set cam upvec
	temp.x = lua_tonumber(L,7);
	temp.y = lua_tonumber(L,8);
	temp.z = lua_tonumber(L,9);
	cam->Set(3, temp);

	// Close lua state? Or can it stay open until program ends/ all scripts read?
}

// Returns the Vec3 values for the camera object, depending on choice input
Vec3 GameWorld:: GetCam(int choice)
{
	if(choice == 1)
		return cam->Get(1);
	if(choice == 2)
		return cam->Get(2);
	if(choice == 3)
		return cam->Get(3);
}

// Sets the Vec3 values for the camera object, depending on choice input
void GameWorld::SetCam(int choice, Vec3 vec)
{
	if(choice == 1)
		cam->Set(choice, vec);
	if(choice == 2)
		cam->Set(choice, vec);
	if(choice == 3)
		cam->Set(choice, vec);
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