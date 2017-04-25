/**
*@class Mesh
*
*@brief 
*
* @version 01 - Alex 
*
* @date 22/04/2017
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
        /*  Mesh Data  */
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Texture> textures;
        /*  Functions  */
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  Render data  */
        GLuint VAO, VBO, EBO;
        /*  Functions    */
        void setupMesh();
};  