/**
*@class Model
*
*@brief The Model class is responsible for loading all the vertices and textures into a Mesh object
*
* @version 01 - Alex 
*
* @date 21/04/2017
*/
#ifndef MODEL_H
#define MODEL_H

#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#define GLEW_STATIC

#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
	///empty constructor only used to hold the models until it gets initalized properly with other constructor
	Model();
	///constructor used to initalize the model with the absolute path to the model
	Model(GLchar* path);
	///prcondition compiled and activated shader, projection, view,scale and tanslate(read position) have been set
	void Draw(Shader shader);

	void SetPos(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	Vec3 GetPos();
	Vec3 GetRotation();
	Vec3 GetScale();
private:
	glm::vec3 position,scale;
	glm::vec4 rotation;
	vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint TextureFromFile(const char* path, string directory);
};

#endif