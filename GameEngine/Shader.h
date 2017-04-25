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
    GLuint Program;
    // Constructor generates the shader on the fly
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Uses the current shader
    void Use();
};