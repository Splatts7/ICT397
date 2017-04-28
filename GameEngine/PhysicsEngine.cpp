/*
* Implementation of PhysicsEngine.h file
* Author - Jack Matters
* Note - ReactPhys3D documentation http://www.reactphysics3d.com/usermanual.html#x1-90005
*/

#include "PhysicsEngine.h"
#include <iostream>

// Default constructor
PhysicsEngine::PhysicsEngine()
{
	// Dynamic world initialization
	gravity = Vector3(0.0, -9.81, 0.0);
	dynamicWorld = new DynamicsWorld(gravity);
	orientation = Quaternion::identity();

	// Frame time initialization
	accumulator = 0.0;
	timeStep = 1.0 / 60.0;
	currentFrame = std::chrono::system_clock::now();
	prevFrame = std::chrono::system_clock::now();
};

// De-constructor
PhysicsEngine::~PhysicsEngine(){};

// Performs physics calculations and updates all collision body locations
Vec3 PhysicsEngine::Update(std::vector<Vector3> &colBodies, Vec3 cam)
{
	// Get difference between frames
	currentFrame = std::chrono::system_clock::now();
	elapsed_seconds = currentFrame-prevFrame;
	prevFrame = currentFrame;

	// Add difference to accumulator
	accumulator += elapsed_seconds.count();

	// Update camera collision box
	position = Vector3(cam.x, cam.y, cam.z);
	orientation = Quaternion::identity();
	transform = Transform(position, orientation);
	rigidBodies[rigidBodies.size()-1]->setTransform(transform);

	// Update physics world
	while (accumulator >= timeStep) 
	{ 
		dynamicWorld->update(timeStep);
		accumulator-= timeStep;
	}

	// Set new collision body locations
	for(int i = 0; i < rigidBodies.size()-1; i++)
	{
		transform = rigidBodies[i]->getTransform();
		position = transform.getPosition();
		colBodies[i] = position;
	}
	
	// Reset forces on camera, and set new camera position
	transform = rigidBodies[rigidBodies.size()-1]->getTransform();
	position = transform.getPosition();
	rigidBodies[rigidBodies.size()-1]->setAngularVelocity(Vector3(0,0,0));
	rigidBodies[rigidBodies.size()-1]->setLinearVelocity(Vector3(0,0,0));
	return Vec3(position.x, position.y, position.z);
}

// Add camera collision object
void PhysicsEngine::AddCam(Vec3 &pos)
{
	// Cam collision body
	position = Vector3(pos.x, pos.y, pos.z);
	transform = Transform(position, orientation);
	body = dynamicWorld->createRigidBody(transform);
	body->setType(DYNAMIC);
	body->enableGravity(false);

	// Create cam collision box
	transform = Transform::identity();
	camBox = new BoxShape(Vector3(20,20,20));
	proxy = body->addCollisionShape(camBox, transform, 1.0);
	rigidBodies.push_back(body);
	proxyShapes.push_back(proxy);
}

// Call private function to make collision shapes
void PhysicsEngine::MakeCollisionShapes()
{
	OnMakeCollisionShapes();
}

// Read collision shape data from script and initialize shapes
void PhysicsEngine::OnMakeCollisionShapes()
{
	// Make lua state and open libs
	lua_State* L = lua_open();
	luaL_openlibs(L);

	if (luaL_dofile(L, "Scripts/CollisionShapes.lua"))
	{
		std::cout << "Error opening file.." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L, "shapes");

	// Array of strings for different shape types
	std::string shapes[7];
	shapes[0] = "sphere";
	shapes[1] = "box";
	shapes[2] = "cone";
	shapes[3] = "cylinder";
	shapes[4] = "capsule";
	shapes[5] = "convex";
	shapes[6] = "heightField";

	// Array of strings for different shape data types
	std::string vars[5];
	vars[0] = "radius";
	vars[1] = "height";
	vars[2] = "x";
	vars[3] = "y";
	vars[4] = "z";

	// Shapes data values to be read in
	decimal radius;
	decimal height;
	Vector3 boxSize;

	// Used for finding which data is currently being read
	std::string temp;

	// Read table of shapes from script
	lua_pushnil(L);
    while (lua_next(L, -2) != 0) 
	{
		// Reset all data variables so they don't carry over to next shape
		radius = decimal(5.0);
		height = decimal(5.0);
		boxSize = Vector3(2.5, 2.5, 2.5);

		// Get current shape being read
		temp = lua_tostring(L,-2);

		// Sphere shape
        if(temp.compare(shapes[0]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				radius = lua_tonumber(L,-1);
				lua_pop(L,1);
			}
			sphere = new SphereShape(radius);
		}
		// Box shape
		if(temp.compare(shapes[1]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				temp = lua_tostring(L,-2);
				if(temp.compare(vars[2]) == 0)
					boxSize.x = lua_tonumber(L,-1);
				if(temp.compare(vars[3]) == 0)
					boxSize.y = lua_tonumber(L,-1);
				if(temp.compare(vars[4]) == 0)
					boxSize.z = lua_tonumber(L,-1);
				lua_pop(L,1);
			}
			box = new BoxShape(boxSize);
		}
		// Cone shape
		if(temp.compare(shapes[2]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				temp = lua_tostring(L,-2);
				if(temp.compare(vars[0]) == 0)
					radius = lua_tonumber(L,-1);
				if(temp.compare(vars[1]) == 0)
					height = lua_tonumber(L,-1);
				lua_pop(L,1);
			}
			cone = new ConeShape(radius, height);
		}

		// Cylinder shape
		if(temp.compare(shapes[3]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				temp = lua_tostring(L,-2);
				if(temp.compare(vars[0]) == 0)
					radius = lua_tonumber(L,-1);
				if(temp.compare(vars[1]) == 0)
					height = lua_tonumber(L,-1);
				lua_pop(L,1);
			}
			cylinder = new CylinderShape(radius, height);
		}

		// Capsule shape
		if(temp.compare(shapes[4]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				temp = lua_tostring(L,-2);
				if(temp.compare(vars[0]) == 0)
					radius = lua_tonumber(L,-1);
				if(temp.compare(vars[1]) == 0)
					height = lua_tonumber(L,-1);
				lua_pop(L,1);
			}
			capsule = new CapsuleShape(radius, height);
		}

		//// Convex shape
		//if(temp.compare(shapes[5]) == 0)
		//{
		//	lua_pushnil(L);
		//	while (lua_next(L, -2) != 0) 
		//	{
		//		dec = lua_tonumber(L,-1);
		//		std::cout<<dec<<std::endl;
		//		lua_pop(L,1);
		//	}
		//}

		//// Heightfield shape
		//if(temp.compare(shapes[6]) == 0)
		//{
		//	lua_pushnil(L);
		//	while (lua_next(L, -2) != 0) 
		//	{
		//		dec = lua_tonumber(L,-1);
		//		std::cout<<dec<<std::endl;
		//		lua_pop(L,1);
		//	}
		//}
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

	lua_close(L);
}

// Call private function to make collision bodies
void PhysicsEngine::MakeCollisionBodies(std::vector<Vector3> &bodyPos, std::vector<int> &numBody, std::vector<std::string> &shapeT)
{
	OnMakeCollisionBodies(bodyPos, numBody, shapeT);
}

// Read collision body data from script and create them
void PhysicsEngine::OnMakeCollisionBodies(std::vector<Vector3> &bodyPos, std::vector<int> &numBody, std::vector<std::string> &shapeT)
{
	// Make lua state and open libs
	lua_State* L = lua_open();
	luaL_openlibs(L);

	// Load and run script
	if (luaL_dofile(L, "Scripts/CollisionBodies.lua"))
	{
		std::cout << "Error opening file......." << std::endl;
		getchar();
		//return 1;
	}

	// Read from script
	lua_settop(L,0);
	lua_getglobal(L, "numsphere");
	lua_getglobal(L, "numbox");
	lua_getglobal(L, "numcone");
	lua_getglobal(L, "numcylinder");
	lua_getglobal(L, "numcapsule");
	lua_getglobal(L, "numconvex");
	lua_getglobal(L, "numheightfield");
	lua_getglobal(L, "bodies");

	// Get number of collision bodies to make from script
	int num = lua_tonumber(L,1);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,2);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,3);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,4);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,5);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,6);
	shapeNumbers.push_back(num);
	num = lua_tonumber(L,7);
	shapeNumbers.push_back(num);
	Vector3 pos;

	// Array of strings for collision body data type
	std::string data[9];
	data[0] = "position";
	data[1] = "type";
	data[2] = "sphere";
	data[3] = "box";
	data[4] = "cone";
	data[5] = "cylinder";
	data[6] = "capsule";
	data[7] = "convex";
	data[8] = "heightfield";

	// Array of strings for collision body data
	std::string vars[5];
	vars[0] = "x";
	vars[1] = "y";
	vars[2] = "z";
	vars[3] = "type";
	vars[4] = "mass";

	// Used for finding which data is currently being read
	std::string temp;
	decimal m;

	// Read table of bodies and their positions from script
	lua_pushnil(L);
    while (lua_next(L, -2) != 0) 
	{
		// Get current shape being read
		temp = lua_tostring(L,-2);

		// Sphere shape
        if(temp.compare(data[2]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) 
				{
					// Reset position to center so previous data doesn't carry over
					pos = Vector3();
					lua_pushnil(L);
					while (lua_next(L, -2) != 0) 
					{
						// Read xyz position
						temp = lua_tostring(L,-2);
						if(temp.compare(vars[0]) == 0)
							pos.x = lua_tonumber(L,-1);
						if(temp.compare(vars[1]) == 0)
							pos.y = lua_tonumber(L,-1);
						if(temp.compare(vars[2]) == 0)
							pos.z = lua_tonumber(L,-1);
						if(temp.compare(vars[3]) == 0)
						{
							temp = lua_tostring(L,-1);
							types.push_back(temp);
						}
						if(temp.compare(vars[4]) == 0)
						{
							m = lua_tonumber(L,-1);
							masses.push_back(m);
						}
						lua_pop(L,1);
					}
					// Increment position count and push position to back of vector
					rbPositions.push_back(pos);
					shapeType.push_back("sphere");
					lua_pop(L,1);
				}
				lua_pop(L,1);
			}
		}
		// Box shape
		if(temp.compare(data[3]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) 
				{
					// Reset position to center so previous data doesn't carry over
					pos = Vector3();
					lua_pushnil(L);
					while (lua_next(L, -2) != 0) 
					{
						// Read xyz position
						temp = lua_tostring(L,-2);
						if(temp.compare(vars[0]) == 0)
							pos.x = lua_tonumber(L,-1);
						if(temp.compare(vars[1]) == 0)
							pos.y = lua_tonumber(L,-1);
						if(temp.compare(vars[2]) == 0)
							pos.z = lua_tonumber(L,-1);
						if(temp.compare(vars[3]) == 0)
						{
							temp = lua_tostring(L,-1);
							types.push_back(temp);
						}
						if(temp.compare(vars[4]) == 0)
						{
							m = lua_tonumber(L,-1);
							masses.push_back(m);
						}
						lua_pop(L,1);
					}
					// Increment position count and push position to back of vector
					rbPositions.push_back(pos);
					shapeType.push_back("box");
					lua_pop(L,1);
				}
				lua_pop(L,1);
			}
		}
		// Cone shape
		if(temp.compare(data[4]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) 
				{
					// Reset position to center so previous data doesn't carry over
					pos = Vector3();
					lua_pushnil(L);
					while (lua_next(L, -2) != 0) 
					{
						// Read xyz position
						temp = lua_tostring(L,-2);
						if(temp.compare(vars[0]) == 0)
							pos.x = lua_tonumber(L,-1);
						if(temp.compare(vars[1]) == 0)
							pos.y = lua_tonumber(L,-1);
						if(temp.compare(vars[2]) == 0)
							pos.z = lua_tonumber(L,-1);
						if(temp.compare(vars[3]) == 0)
						{
							temp = lua_tostring(L,-1);
							types.push_back(temp);
						}
						if(temp.compare(vars[4]) == 0)
						{
							m = lua_tonumber(L,-1);
							masses.push_back(m);
						}
						lua_pop(L,1);
					}
					// Increment position count and push position to back of vector
					rbPositions.push_back(pos);
					shapeType.push_back("cone");
					lua_pop(L,1);
				}
				lua_pop(L,1);
			}
		}
		// Cylinder shape
		if(temp.compare(data[5]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) 
				{
					// Reset position to center so previous data doesn't carry over
					pos = Vector3();
					lua_pushnil(L);
					while (lua_next(L, -2) != 0) 
					{
						// Read xyz position
						temp = lua_tostring(L,-2);
						if(temp.compare(vars[0]) == 0)
							pos.x = lua_tonumber(L,-1);
						if(temp.compare(vars[1]) == 0)
							pos.y = lua_tonumber(L,-1);
						if(temp.compare(vars[2]) == 0)
							pos.z = lua_tonumber(L,-1);
						if(temp.compare(vars[3]) == 0)
						{
							temp = lua_tostring(L,-1);
							types.push_back(temp);
						}
						if(temp.compare(vars[4]) == 0)
						{
							m = lua_tonumber(L,-1);
							masses.push_back(m);
						}
						lua_pop(L,1);
					}
					// Increment position count and push position to back of vector
					rbPositions.push_back(pos);
					shapeType.push_back("cylinder");
					lua_pop(L,1);
				}
				lua_pop(L,1);
			}
		}
		// Capsule shape
		if(temp.compare(data[6]) == 0)
		{
			lua_pushnil(L);
			while (lua_next(L, -2) != 0) 
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0) 
				{
					// Reset position to center so previous data doesn't carry over
					pos = Vector3();
					lua_pushnil(L);
					while (lua_next(L, -2) != 0) 
					{
						// Read xyz position
						temp = lua_tostring(L,-2);
						if(temp.compare(vars[0]) == 0)
							pos.x = lua_tonumber(L,-1);
						if(temp.compare(vars[1]) == 0)
							pos.y = lua_tonumber(L,-1);
						if(temp.compare(vars[2]) == 0)
							pos.z = lua_tonumber(L,-1);
						if(temp.compare(vars[3]) == 0)
						{
							temp = lua_tostring(L,-1);
							types.push_back(temp);
						}
						if(temp.compare(vars[4]) == 0)
						{
							m = lua_tonumber(L,-1);
							masses.push_back(m);
						}
						lua_pop(L,1);
					}
					// Increment position count and push position to back of vector
					rbPositions.push_back(pos);
					shapeType.push_back("capsule");
					lua_pop(L,1);
				}
				lua_pop(L,1);
			}
		}
		//// convex shape
		//if(temp.compare(data[7]) == 0)
		//{
		//	lua_pushnil(L);
		//	while (lua_next(L, -2) != 0) 
		//	{
		//		lua_pushnil(L);
		//		while (lua_next(L, -2) != 0) 
		//		{
		//			// Reset position to center so previous data doesn't carry over
		//			pos = Vector3();
		//			lua_pushnil(L);
		//			while (lua_next(L, -2) != 0) 
		//			{
		//				// Read xyz position
		//				temp = lua_tostring(L,-2);
		//				if(temp.compare(vars[0]) == 0)
		//					pos.x = lua_tonumber(L,-1);
		//				if(temp.compare(vars[1]) == 0)
		//					pos.y = lua_tonumber(L,-1);
		//				if(temp.compare(vars[2]) == 0)
		//					pos.z = lua_tonumber(L,-1);
		//				if(temp.compare(vars[3]) == 0)
		//				{
		//					temp = lua_tostring(L,-1);
		//					types.push_back(temp);
		//				}
		//				if(temp.compare(vars[4]) == 0)
		//				{
		//					m = lua_tonumber(L,-1);
		//					masses.push_back(m);
		//				}
		//				lua_pop(L,1);
		//			}
		//			// Increment position count and push position to back of vector
		//			rbPositions.push_back(pos);
		//			shapeType.push_back("convex");
		//			lua_pop(L,1);
		//		}
		//		lua_pop(L,1);
		//	}
		//	// heightfield shape
		//if(temp.compare(data[8]) == 0)
		//{
		//	lua_pushnil(L);
		//	while (lua_next(L, -2) != 0) 
		//	{
		//		lua_pushnil(L);
		//		while (lua_next(L, -2) != 0) 
		//		{
		//			// Reset position to center so previous data doesn't carry over
		//			pos = Vector3();
		//			lua_pushnil(L);
		//			while (lua_next(L, -2) != 0) 
		//			{
		//				// Read xyz position
		//				temp = lua_tostring(L,-2);
		//				if(temp.compare(vars[0]) == 0)
		//					pos.x = lua_tonumber(L,-1);
		//				if(temp.compare(vars[1]) == 0)
		//					pos.y = lua_tonumber(L,-1);
		//				if(temp.compare(vars[2]) == 0)
		//					pos.z = lua_tonumber(L,-1);
		//				if(temp.compare(vars[3]) == 0)
		//				{
		//					temp = lua_tostring(L,-1);
		//					types.push_back(temp);
		//				}
		//				if(temp.compare(vars[4]) == 0)
		//				{
		//					m = lua_tonumber(L,-1);
		//					masses.push_back(m);
		//				}
		//				lua_pop(L,1);
		//			}
		//			// Increment position count and push position to back of vector
		//			rbPositions.push_back(pos);
		//			shapeType.push_back("heightfield");
		//			lua_pop(L,1);
		//		}
		//		lua_pop(L,1);
		//	}
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

	// Close lua state
	lua_close(L);

	// Join collision shapes to collision bodies
	JoinShapesToBodies();

	// Set number of each shape and their positions and their shape type
	bodyPos = rbPositions;
	numBody = shapeNumbers;
	shapeT = shapeType;
}

// Join all shapes to bodies
void PhysicsEngine::JoinShapesToBodies()
{
	// Get total number of shapes
	int num = 0;
	for(int i = 0; i < shapeNumbers.size(); i++)
		num+= shapeNumbers[i];

	// Loop through all shapes, adding bodies
	for(int i = 0; i < num; i++)
	{
			// Make rigid body
			transform = Transform(rbPositions[i], orientation);
			body = dynamicWorld->createRigidBody(transform);
			if(types[i].compare("static") == 0)
				body->setType(STATIC);
			if(types[i].compare("kinematic") == 0)
				body->setType(KINEMATIC);

			// Sphere
			if(shapeType[i].compare("sphere") == 0)
			{
				// Make collision body
				transform = Transform::identity();
				proxy = body->addCollisionShape(sphere, transform, masses[i]);
				rigidBodies.push_back(body);
				proxyShapes.push_back(proxy);
			}
			// Box
			if(shapeType[i].compare("box") == 0)
			{
				// Make collision body
				transform = Transform::identity();
				proxy = body->addCollisionShape(box, transform, masses[i]);
				rigidBodies.push_back(body);
				proxyShapes.push_back(proxy);
			}
			// Cone
			if(shapeType[i].compare("cone") == 0)
			{
				// Make collision body
				transform = Transform::identity();
				proxy = body->addCollisionShape(cone, transform, masses[i]);
				rigidBodies.push_back(body);
				proxyShapes.push_back(proxy);
			}
			if(shapeType[i].compare("cylinder") == 0)
			{
				// Make collision body
				transform = Transform::identity();
				proxy = body->addCollisionShape(cylinder, transform, masses[i]);
				rigidBodies.push_back(body);
				proxyShapes.push_back(proxy);
			}
			if(shapeType[i].compare("capsule") == 0)
			{
				// Make collision body
				transform = Transform::identity();
				proxy = body->addCollisionShape(capsule, transform, masses[i]);
				rigidBodies.push_back(body);
				proxyShapes.push_back(proxy);
			}
			//if(shapeType[i].compare("convex") == 0)
			//{
			//	// Make collision body
			//	transform = Transform::identity();
			//	proxy = body->addCollisionShape(convex, transform, masses[i]);
			//	rigidBodies.push_back(body);
			//	proxyShapes.push_back(proxy);
			//}
			//if(shapeType[i].compare("heightfield") == 0)
			//{
			//	// Make collision body
			//	transform = Transform::identity();
			//	proxy = body->addCollisionShape(heightField, transform, masses[i]);
			//	rigidBodies.push_back(body);
			//	proxyShapes.push_back(proxy);
			//}
	}
	
}

// Destroy all created objects
void PhysicsEngine::DestroyAll()
{
	for(int i = 0; i < rigidBodies.size(); i++)
		dynamicWorld->destroyCollisionBody(rigidBodies[i]);
	dynamicWorld->destroyRigidBody(body);
	delete camBox;
	delete sphere;
	delete box;
	delete cone;
	delete cylinder;
	delete capsule;
	delete convex;
	delete heightField;
	delete dynamicWorld;
}