/**
* @class GUI
* @brief GUI engine to handle GUI elements
* @author Jonathan Sands
* @version 01 - Started
* @date 23/04/2017
*/

#include <stdlib.h>
#include "gl/glut.h"
#include <fstream>

#ifndef GUI_H
#define GUI_H

class GUI
{
	public:

		/**
		* @brief Defualt constructor
		*/
		GUI();

		/**
		* @brief Deconstructor
		*/
		~GUI();

		/**
		* @brief Loads a texture into memory
		* @param filename - File name of texture to load
		* @param width - Width of texture
		* @param height - Height of texture
		*/
		GLuint LoadTexture(const char * filename, int width, int height);

		/**
		* @brief Unloads a texture from memory
		* @param texture - Texture object
		*/
		void FreeTexture(GLuint texture);

	private:

		/// Texture object
		GLuint texture;

		/// Texture data
		unsigned char * data;

		/// File name for texture
		FILE * file;
};

#endif