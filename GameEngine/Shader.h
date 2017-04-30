/**
*@class Shader
*
*@brief The Shader class holds an instance of a vertex and fragment shader it also compiles and binds them for use
*
* @version 01 - Alex 
*
* @date 21/04/2017
*/
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#define GLEW_STATIC
#include "gl\glew.h"
#include "gl\glut.h"
#include "glm\glm.hpp"

class Shader
{
public:
	Shader();
    GLuint Program;
    /// Constructor generates the shader on the fly
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    /// Uses the current shader
    void Use();
	void Disable();
};

#endif