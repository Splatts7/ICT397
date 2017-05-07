/**
* @class Header file for structs
* @brief Contains all user created structures used in game engine
* @author Jack Matters
* @version 01
* @date 18/04/2017
*/

#ifndef STRUCT_H
#define STRUCT_H

//#include <math.h>
//#include <iostream>
#include <vector>

struct Vec3
{
	public:

		/// The x-axis value
		float x;

		/// The y-axis value
		float y;

		/// The z-axis value
		float z;

		/**
		* @brief Default constructor
		*/
		Vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		};

		/**
		* @brief Non-default constructor to set all 3 variables
		* @param x - The x-axis value
		* @param y - The y-axis value
		* @param z - The z-axis value
		*/
		Vec3(float x, float y, float z)
		{
			Vec3::x = x; 
			Vec3::y = y; 
			Vec3::z = z;
		};

		/**
		* @brief None-default constructor to set all variables to same value
		* @param num - The number to set
		*/
		Vec3(float num)
		{
			x = num;
			y = num;
			z = num;
		}
	
		/**
		* @brief Overloads the equality operator to copy Vec3s
		* @param original - Vec3 to be copied from
		* @return Vec3 - A new Vec3
		*/
		Vec3 operator = (const Vec3 original)
		{
			x = original.x;
			y = original.y;
			z = original.z;

			return Vec3(x,y,z);
		};
};

#endif