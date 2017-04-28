/**
* @class PhysicsEngine
* @brief Physics engine that handles object collisions and physics based movement
* @author Jack Matters
* @version 01 Started
* @date 23/04/2017
*
* @version 02 Tried to change to Bullet physics as was having a hard time with ReactPhysics3D, but Bullet was
*			  even more confusing. Went back to ReactPhysics3D and made some progress.
* @date 25/04/2017
*
* @version 03 Made big progress. Got physics working with sphere shapes colliding with each other.
* @date 26/04/2017
*
* @version 04 Moved all collision body and shape initializations to scripts. To add a new shape to game, all
*			  user has to do is edit the scripts. All shapes collide with each other as they should.
* @note Currently, only one size for each collision shape is able to be initialized. Will change this in next
*		assignment.
* @date 27/04/2017
*/

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "ReactPhys3D/reactphysics3d.h"
#include "Structs.h"
#include "lua.hpp"
#include <Windows.h>
#include <chrono>
#include <vector>

using namespace reactphysics3d;

class PhysicsEngine 
{
	public:

		/**
		* @brief Default constructor
		*/
		PhysicsEngine();

		/**
		* @brief De-constructor
		*/
		~PhysicsEngine();

		/**
		* @brief Calls private function to make collision shapes
		*/
		void MakeCollisionShapes();

		/**
		* @brief Calls private function to create rigid bodies
		* @param bodyPos - Position of each collision body
		* @param numBody - Number of each shape type
		* @param shapeT - Type of each shape
		*/
		void MakeCollisionBodies(std::vector<Vector3> &bodyPos, std::vector<int> &numBody, std::vector<std::string> &shapeT);

		/**
		* @brief destroys all created objects upon end of program
		*/
		void DestroyAll();
		
		/**
		* @brief Update all bodies, applying physics forces
		* @param colBodies - Vector of all collision body positions (updated in this function)
		* @param cam - Camera position
		* @return Vec3 - New camera position after doing physics calculations
		*/
		Vec3 Update(std::vector<Vector3> &colBodies, Vec3 cam);

		/**
		* @brief Adds camera collision shape
		* @param pos - Camera position
		*/
		void AddCam(Vec3 &pos);

	private:

		/**
		* @brief Makes all collision shapes, as read in from script
		*/
		void OnMakeCollisionShapes();

		/**
		* @brief Makes all collision bodies, as read in from script
		* @param bodyPos - Position of each collision body
		* @param numBody - Number of each shape type
		* @param shapeT - Type of each shape
		*/
		void OnMakeCollisionBodies(std::vector<Vector3> &bodyPos, std::vector<int> &numBody, std::vector<std::string> &shapeT);

		/**
		* @brief Joins collision bodies with shapes
		*/
		void JoinShapesToBodies();

		/// Dynamic collision world
		DynamicsWorld* dynamicWorld;

		/// Collision world
		CollisionWorld collisionWorld;

		/// Gravity vector
		Vector3 gravity;

		/// Camera collision shape
		BoxShape* camBox;

		/// Sphere collision shape
		SphereShape* sphere;

		/// Box collision shape
		BoxShape* box;

		/// Cone collision shape
		ConeShape* cone;

		/// Cylinder collision shape
		CylinderShape* cylinder;

		/// Capsule collision shape
		CapsuleShape* capsule;

		/// Convex collision shape
		ConvexMeshShape* convex;

		/// Heightfield collision shape
		HeightFieldShape* heightField;
		
		/// Vector of rigid body positions
		std::vector<Vector3> rbPositions;

		/// Single rigid body position (added to vector after data read in)
		Vector3 position;

		/// Vector of strings for rigid body types
		std::vector<std::string> types;

		/// Vector of decimals for rigid body masses
		std::vector<decimal> masses;

		/// Rigid body orientation
		Quaternion orientation;

		/// Rigid body transformation
		Transform transform;

		/// Vector of rigid bodies
		std::vector<RigidBody*> rigidBodies;

		/// Vector of proxy shapes
		std::vector<ProxyShape*> proxyShapes;

		/// Single rigid body for creation (added to vector after creation)
		RigidBody* body;

		/// Single proxy shape for creation (added to vector after creation)
		ProxyShape* proxy;

		/// Vector of number of each collision shape
		std::vector<int> shapeNumbers;

		/// Vector of shape types in order they are read from script
		std::vector<std::string> shapeType;

		/// Time step used for updating of physics
		float timeStep;

		/// Holds time difference between frames
		long double accumulator;

		/// Current frame time
		std::chrono::time_point<std::chrono::system_clock> currentFrame;

		/// Previous frame time
		std::chrono::time_point<std::chrono::system_clock> prevFrame;

		/// Time difference between frames
		std::chrono::duration<double> elapsed_seconds;
};


#endif