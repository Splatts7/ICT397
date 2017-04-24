/*
* Implementation of GUI.cpp file
* Author - Jonathan Sands
*/

#include "GUI.h"

// Default constructor
GUI::GUI()
{

}

// Deconstructor
GUI::~GUI()
{
	
}

// Load in a texture into memory
GLuint GUI::LoadTexture(const char * filename, int width, int height)
{
    // Read in a .raw file
    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

	// Generate the texture with the loaded data
    glGenTextures(1, &texture);
	// Bind the texture to its array
    glBindTexture(GL_TEXTURE_2D, texture);
	 // Set texture environment parameters
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //here we are setting what textures to use and when. The MIN filter is which quality to show
    //when the texture is near the view, and the MAG filter is which quality to show when the texture
    //is far from the view.

    //The qualities are (in order from worst to best)
    //GL_NEAREST
    //GL_LINEAR
    //GL_LINEAR_MIPMAP_NEAREST
    //GL_LINEAR_MIPMAP_LINEAR

    //And if you go and use extensions, you can use Anisotropic filtering textures which are of an
    //even better quality, but this will do for now.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the parameter to repeat the texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// Free the texture
    free(data);
	// Return whether it was successful
    return texture;
}

// Unload a texture from memory
void GUI::FreeTexture(GLuint texture)
{
  glDeleteTextures(1, &texture); 
}