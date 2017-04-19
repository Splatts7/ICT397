/**
* @class GameObject
* @brief Base class used for game object creation
* @author Jack Matters
* @version 01 - Started, implemented from lecture notes
* @date 18/04/2017
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Structs.h"

class GameObject
{
	public:
		
		/**
		* @brief Default constructor
		*/
		GameObject();

		/**
		* @brief Deconstructor
		*/
		~GameObject();

		/**
		* @brief Virtual render function
		*/
		virtual void Render();

		/**
		* @brief Virtual render function
		*/
		virtual void Move() = 0;

		/**
		* @brief Virtual gets function
		*/
		virtual Vec3 Get(int choice) = 0;

		/**
		* @brief Virtual sets function
		*/
		virtual void Set(int choice, Vec3 vec) = 0;


	private:



	protected:

		/// Position of the object
		Vec3 position;

};

#endif