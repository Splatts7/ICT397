/**
* @class Terrain
* @brief Terrain object inherited from GameObject class (concrete class)
* @author Jack Matters
* @version 01 - Started
* @date 18/04/2017
*/

#ifndef TERRAIN_H
#define TERRAIN_H

#include "GameObject.h"

class Terrain: public GameObject
{
	public:

		/**
		* @brief Default constructor
		*/
		Terrain();

		/**
		* @brief Deconstructor
		*/
		~Terrain();

		/**
		* @brief Render the terrain field
		*/
		void Render();

		/**
		* @brief Returns terrain Vec3 data
		* @param choice - Vec3 to return
		* @return Vec3 - Chosen vec3 data
		*/
		Vec3 Get(int choice);

		/**
		* @brief Sets terrain Vec3 data
		* @param choice - Vec3 to set
		* @param vec - Vec3 data to be set
		*/
		void Set(int choice, Vec3 vec);

		/**
		* @brief Moves the Terrain
		* @note Need this because it is a virtual function
		*/
		void Move();

	private:


};

#endif