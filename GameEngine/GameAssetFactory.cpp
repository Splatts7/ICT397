/*
* Implementation of GameAssetFactory.h file
* Author - Jack Matters
*/

#include "GameAssetFactory.h"
#include "Camera.h"

// Create an abstract pointer to the created GameObject
GameObject* GameAssetFactory::Create(std::string type)
{
	if(type=="CAMERA")
		return new Camera();
	/*else if(type=="MESH")
		return new Mesh;
	else if(type=="ITEM")
		return new Item;
	else if(type == "TEXTURE")
		return new Texture;
	else if(type == "TERRAIN")
		return new Terrain;*/
}