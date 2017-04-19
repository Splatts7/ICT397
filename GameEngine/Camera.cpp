/*
* Implementation of Camera.h file
* Author - Jack Matters
*/

#include "Camera.h"

// Default constructor
Camera::Camera()
{
	position = Vec3(0.0, 1.75, 0.0);
	lookAt = Vec3(0.0, 1.75, -1.0);
	upVec = Vec3(0.0 ,1.0, 0.0);
}

// Deconstructor
Camera::~Camera(){};

// Render function
// Note: Don't think we need this
void Camera::Render()
{
	Camera cam = Camera();
}

// Don't need this (movement done through Input Engine
void Camera::Move(){}

// Return the chosen camera Vec3 data
Vec3 Camera::Get(int choice)
{
	if(choice == 1)
		return position;
	if(choice == 2)
		return lookAt;
	if(choice == 3)
		return upVec;
}

// Set the passed in Vec3 to chosen camera Vec3
void Camera::Set(int choice, Vec3 vec)
{
	if(choice == 1)
		position = vec;
	if(choice == 2)
		lookAt = vec;
	if(choice == 3)
		upVec = vec;
}