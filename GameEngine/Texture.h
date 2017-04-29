/**
* @class Texture
* @brief Texture engine for loading textures
* @author Jonathan Sands
* @version 01 - Started
* @date 23/04/2017
*/

#include <stdlib.h>
#include "gl/glut.h"
#include <fstream>

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	public:

		/**
		* @brief Defualt constructor
		*/
		Texture::Texture();

		/**
		* @brief Deconstructor
		*/
		Texture::~Texture();

		/**
		* @brief Loads a texture into memory
		* @param filename - File name of texture to load
		* @param width - Width of texture
		* @param height - Height of texture
		*/
		GLuint Texture::LoadTexture(const char * filename, int width, int height);

		/**
		* @brief Unloads a texture from memory
		* @param texture - Texture object
		*/
		void Texture::FreeTexture(GLuint texture);

	private:

		/// Texture object
		GLuint texture;

		/// Texture data
		unsigned char * data;

		/// File name for texture
		FILE * file;
};

#endif