/**
* @class GraphicsEngine
* @brief Graphics engine that handles creation of all game objects
* @author Jack Matters
* @version 01 Started
* @date 13/04/2017
*
* @version 02 Added vector objects to hold object positions and numbers of each object type. Added functions for drawing.
* @date 27/04/2017
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>
#include "PhysicsEngine.h"
#include "gl/glut.h"

class GraphicsEngine
{
	public:

		/**
		* @brief Default constructor
		*/
		GraphicsEngine();

		/**
		* @brief De-constructor
		*/
		~GraphicsEngine();

		/**
		* @brief Calls private OnDraw function
		* @param cam - Camera position
		* @return Vec3 - New camera position
		*/
		Vec3 Draw(Vec3 cam);

		/**
		* @brief Initializes all data before starting game
		* @param cam - Camera position
		*/
		void Prepare(Vec3 cam);

	private:

		/**
		* @brief Draws all objects/shapes
		* @param cam - Camera position
		* @return Vec3 - New camera position
		*/
		Vec3 OnDraw(Vec3 cam);

		/// Physics Engine object
		PhysicsEngine physics;

		/// For shapes
		GLUquadricObj* quad;

		/// Vector for number of each collision shape (used for drawing)
		std::vector<int> numberCollisionShapes;

		/// Total number of collisions
		int totalNumCol;

		/// Position of collision bodies
		std::vector<Vector3> collisionBodyPos;

		/// Vector of shape types in order they are read from script
		std::vector<std::string> shapeTypes;
};

#endif