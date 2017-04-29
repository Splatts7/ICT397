/**
*@class Mesh
*
*@brief The Mesh class holds all the buffer objects with vertex and texture information
* for a part of a Model. 1 Model can hold many Meshes
*
*@note Only to be called in the Model class shouldn't be called anywhere else
*
* @version 01 - Alex 
*
* @date 21/04/2017
*/
#include <vector>

#define GLEW_STATIC
#include "gl\glew.h"
#include "gl\glut.h"
#include "gl\GL.h"

#include "Shader.h"
#include "Structs.h"
using namespace std;

class Mesh {
    public:
        ///vertex mesh data
        vector<Vertex> vertices;
		///indices mesh data
        vector<GLuint> indices;
		///texture mesh data
        vector<Texture> textures;
        ///general use constructor for the Mesh class
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /// Buffer objects
        GLuint VAO, VBO, EBO;
        /// Setup function
        void setupMesh();
};  