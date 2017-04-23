/**
* @class NPC
* @brief NPC object inherited from GameObject class (concrete class)
* @author Jack Matters
* @version 01 - Started
* @date 18/04/2017
*/

#ifndef NPC_H
#define NPC_H

#include "GameObject.h"

class NPC: public GameObject
{
	public:

		/**
		* @brief Default constructor
		*/
		NPC();

		/**
		* @brief Deconstructor
		*/
		~NPC();

		/**
		* @brief Render an NPC
		*/
		void Render();

		/**
		* @brief Returns NPC Vec3 data
		* @param choice - Vec3 to return
		* @return Vec3 - Chosen vec3 data
		*/
		Vec3 Get(int choice);

		/**
		* @brief Sets NPC Vec3 data
		* @param choice - Vec3 to set
		* @param vec - Vec3 data to be set
		*/
		void Set(int choice, Vec3 vec);

		/**
		* @brief Moves the NPC
		* @note Jonathan, use this if you can?
		*/
		void Move();

	private:

};

#endif