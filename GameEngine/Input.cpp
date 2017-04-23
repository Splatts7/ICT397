/*
* Implementation of Input.cpp file
* Author - Jonathan Sands, Jack Matters
*/

#include "Input.h"

// Default constructor
Input::Input()
{
	// Create lua state
	lua_State* L = lua_open();
	if (L == NULL)
		std::cout << "Error Initializing lua.. " << lua_tostring(L, -1) << std::endl;

	// Load lua library functions
	luaL_openlibs(L);

	// Load and run script
	if (luaL_dofile(L, "Scripts/Camera.lua"))
		std::cout << "Error opening file.. " << lua_tostring(L, -1) << std::endl;

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L,"rotspeed");
	lua_getglobal(L,"movespeed");
	lua_getglobal(L,"camx");
	lua_getglobal(L,"camy");
	lua_getglobal(L,"camz");

	// Initialize camera move and rotation speed and position
	rotSpeed = lua_tonumber(L,1);
	moveSpeed = lua_tonumber(L,2);
	pos.x = lua_tonumber(L,3);
	pos.y = lua_tonumber(L,4);
	pos.z = lua_tonumber(L,5);

	// Close lua state
	lua_close(L);

	// Initialize other variables to 0
	rotation = Vec3();
	deltaAngle = Vec3();
	move = 0;
	strafe = 0;
	radRotY = 0.0;
};

// De-constructor
Input::~Input(){};

// Responds to keyboard key input
void Input::pressKeys(unsigned char key, int xx, int yy)
{ 	
	// Get a reference to the gameControl variable in the main.cpp file and get the current cam pos
	extern GameControl gameControl;
	pos = gameControl.GetCam(1);

	switch (key) 
	{
		// Move forward
		case 'w':
		case 'W':
			move = 2;
			break;
		// Move back
		case 's':
		case 'S':
			move = 1;
			break;
		// Strafe left
		case 'a':
		case 'A':
			strafe = 2;
			break;
		// Strafe right
		case 'd':
		case 'D':
			strafe = 1;
			break;
		// Display game manual
		case 'm':
		case 'M':
			if (displayManual) 
				displayManual = false;
			else 
				displayManual = true;
			break;
		// Switch between wireframe and full rendering
		case 'k':
		case 'K':
			if (!displayWireframe) 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				displayWireframe = true;
			}
			else 
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				displayWireframe = false;
			}
			break;
		// Show exit splash screen
		case 'x':
		case 'X':
			if (displayExit)
				displayExit = false;
			else
				displayExit = true;
			break;
       }
}

// Responds to keyboard key being released
void Input::releaseKeys(unsigned char key, int xx, int yy)
{ 	
   switch (key)
	{
		case 'A' :
		case 'a' :
		case 'D' :
		case 'd' :
			strafe = 0;
			break;

		case 'W' :
		case 'w' :
		case 'S' :
		case 's' :
			move = 0;	
			break;
	}
} 

// Responds to mouse movement input
void Input::moveMouse(int x, int y)
{ 	
	// Get a reference to the gameControl variable in the main.cpp file and get the current screen size
	extern GameControl gameControl;

	// I don't know why width == height, but it works, so yeah?
	float width = gameControl.GetScreenH();
	float height = gameControl.GetScreenW();
	
	// Warp mouse pointer to center of screen
	if (x != height/2 || y != width/2)
        glutWarpPointer(height/2, width/2);

	// Calculate mouse movement
    deltaAngle.x = (x - height/2);
    deltaAngle.y = (y - width/2);

	// Calculate rotation angles
	rotation.x += (deltaAngle.y * 180) / rotSpeed;
    rotation.y += (deltaAngle.x * 180) / rotSpeed;

	// Keep camera rotation to directly up/down and full 360 rotation
    if(rotation.x > 90)
        rotation.x = 90.0;
    if(rotation.x < -90)
        rotation.x = -90.0;
    if(rotation.y > 360)
        rotation.y = 0.0;
    if(rotation.y < -360)
        rotation.y = 0.0;

	// Rotate camera
	TranslateCam();
}

// Responds to mouse button input
void Input::pressMouseButton(int button, int state, int x, int y)
{
	// If the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// Close the program if exit splash screen is showing
		if (displayExit) {
			exit(0);
		}
		// when the button is released
		if (state == GLUT_UP) {

		}
		else {// state = GLUT_DOWN
			
		}
	}
}

// Move the camera forward and back
void Input::ComputeCamFB(int direction)
{
	// Calculate current camera rotation in radians
    radRotY = (rotation.y / 180 *  M_PI);

	// Forward movement
    if(direction == 1)
    {
        pos.x -= moveSpeed * (float)(sin(radRotY));
        pos.z += moveSpeed * (float)(cos(radRotY));
    }
	// Backwards movement
    if(direction == 2)
    {
        pos.x += moveSpeed * (float)(sin(radRotY));
        pos.z -= moveSpeed * (float)(cos(radRotY));
    }

	// Move camera
	TranslateCam();

	// Get a reference to the gameControl variable in the main.cpp file and set the new cam pos
	extern GameControl gameControl;
	gameControl.SetCam(1, pos);
}

// Strafe the camera left or right
void Input::ComputeCamLR(int direction)
{
	// Calculate current camera rotation in radians
    radRotY = (rotation.y / 180 * M_PI);

	// Strafe left
    if(direction == 1)
    {
        pos.x += moveSpeed * (float)(cos(radRotY));
        pos.z += moveSpeed * (float)(sin(radRotY));
    }
	// Strafe right
    if(direction == 2)
    {
        pos.x -= moveSpeed * (float)(cos(radRotY));
        pos.z -= moveSpeed * (float)(sin(radRotY));
	}

	// Move camera
	TranslateCam();

	// Get a reference to the gameControl variable in the main.cpp file and set the new cam pos
	extern GameControl gameControl;
	gameControl.SetCam(1, pos);
}

// Move the camera depending on key/s being pressed
void Input::MoveCamera()
{
	if(move)
		ComputeCamFB(move);
	if(strafe)
		ComputeCamLR(strafe);
}

// Moves the camera to the correct position, and rotates it to the correct angle
void Input::TranslateCam()
{
	glLoadIdentity();
	glRotatef(rotation.x, 1.0, 0.0, 0.0);
	glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glTranslatef(-pos.x, -pos.y, -pos.z);
}