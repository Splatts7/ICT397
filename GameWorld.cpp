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
	
	extern Input input;
	input.MoveCamera();
	glEnable(GL_DEPTH_TEST);
	testmodel.Draw(_shader);
	testmodel2.Draw(_shader);

    //Front wall
    glBegin(GL_POLYGON);
    //glColor3f(0.0, 0.5, 0.0);   //dark green
    glVertex3f(10.0, 10.0, -100.0);   //TL
    glVertex3f(10.0, -10.0, -100.0);   //BL
    glVertex3f(-10.0, -10.0, -100.0);   //BR
    glVertex3f(-10.0, 10.0, -100.0);   //TR
    glEnd();

	//_shader.Use();
	/*glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
	glm::vec3 _pos, _front, _up;
	_pos.x = cam->Get(1).x;_pos.y = cam->Get(1).y;_pos.z = cam->Get(1).z;
	_front.x = cam->Get(2).x;_front.y = cam->Get(2).y;_front.z = cam->Get(2).z;
	_up.x = cam->Get(3).x;_up.y = cam->Get(3).y;_up.z = cam->Get(3).z;
	glm::mat4 view = glm::lookAt(_pos, _front, _up);

    glUniformMatrix4fv(glGetUniformLocation(_shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(_shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));*/
	
	//_shader.Disable();

    
	glutSwapBuffers();
}

void GameWorld::SetUpModels()
{
	_shader = Shader("Shaders/shader.vs", "Shaders/shader.frag");
	testmodel = Model("models/buildings/house65.obj");
	testmodel2 = Model("models/NPCs/MONK.obj");
	testmodel2.SetPos(20.3f,5.2f,20.0f);
	testmodel2.SetScale(3.0f,3.0f,3.0f);
}

/*Model GameWorld::LoadModel(const char* filename)
{
	
	glm::vec3 pos,scale, rotation;

	if (luaL_dofile(L, filename))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	lua_settop(L,0);

	lua_getglobal(L,"modelName");
	lua_getglobal(L,"xpos");
	lua_getglobal(L,"ypos");
	lua_getglobal(L,"zpos");
	lua_getglobal(L,"xscale");
	lua_getglobal(L,"yscale");
	lua_getglobal(L,"zscale");
	string fn = lua_tostring(L,0);
	//char* file = fn.c_str;
	char* file = new char[fn.length()+1];
	memcpy(file,fn.c_str, fn.length()+1);
	Model temp = Model(file);
	float xpos= lua_tonumber(L,1);
	float ypos= lua_tonumber(L,2);
	float zpos= lua_tonumber(L,3);
	temp.SetPos(xpos,ypos,zpos);
	float xscale= lua_tonumber(L,4);
	float yscale= lua_tonumber(L,5);
	float zscale= lua_tonumber(L,6);
	temp.SetScale(xscale,yscale,zscale);
	return temp;
}

void GameWorld::SetUpModels()
{
	if (luaL_dofile(L, "Scripts/Model_init.lua"))
	{
		//std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	//get the vertex and fragment shaders
	lua_settop(L,0);	
	//get all the models scripts , model scripts will hold position data
	lua_getglobal(L,"numModels");
	int numbModels = lua_tonumber(L,0);
	for(int i = 1; i <= numbModels;i++)
	{
		lua_getglobal(L,"modelName"+i);
		string fn = lua_tostring(L,0);
		char* file = fn.c_str;
		modelsVec.push_back(LoadModel(file));
	}
}*/

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