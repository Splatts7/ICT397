/**
* @class Camera
* @brief Camera object inherited from GameObject class (concrete class)
* @author Jack Matters
* @version 01 - Started
* @date 18/04/2017
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera: public GameObject
{
	public:
		
		/**
		* @brief Default constructor
		*/
		Camera();

		/**
		* @brief Deconstructor
		*/
		~Camera();

		/**
		* @brief
		* @note Don't think we need this
		*/
		void Render();

		/**
		* @brief Returns camera Vec3 data
		* @param choice - Vec3 to return
		* @return Vec3 - Chosen vec3 data
		*/
		Vec3 Get(int choice);

		/**
		* @brief Sets camera Vec3 data
		* @param choice - Vec3 to set
		* @param vec - Vec3 data to be set
		*/
		void Set(int choice, Vec3 vec);

		/**
		* @brief Moves the camera
		* @note Jonathan, use this if you can?
		*/
		void Move();

		/// Camera look at position
		Vec3 lookAt;

		/// Camera up vector
		Vec3 upVec;


	private:

		

};

#endif