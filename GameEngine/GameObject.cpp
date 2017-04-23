/*
* Implementation of GameObject.h file
* Author - Jack Matters
*/

#include "GameObject.h"

// Default constructor
GameObject::GameObject()
{
	position = Vec3(0, 0, 0);
}

// Non-default constructor
GameObject::~GameObject(){}

// Render function for GameObject
void GameObject::Render()
{
	// Call Image and Model Database to get GameObject data (passed in through script)
}