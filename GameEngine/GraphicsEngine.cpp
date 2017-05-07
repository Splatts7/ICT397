/*
* Implementation of GraphicsEngine.h file
* Author - Jack Matters
*/

#include "GraphicsEngine.h"
#include <iostream>

// Default constructor
GraphicsEngine::GraphicsEngine()
{
	quad = gluNewQuadric();
	totalNumCol = 0;
};

// De-constructor
GraphicsEngine::~GraphicsEngine(){};

// Calls private OnDraw function
Vec3 GraphicsEngine::Draw(Vec3 cam)
{
	return OnDraw(cam);
}

// Draw all shapes and objects
Vec3 GraphicsEngine::OnDraw(Vec3 cam)
{
	// Update physics each frame
	cam = physics.Update(collisionBodyPos, cam);

	// Draw shapes
	for(int i = 0; i < totalNumCol; i++)
	{
		if(shapeTypes[i].compare("sphere") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			gluSphere(quad, 3, 100, 100);
			glPopMatrix();
		}
		if(shapeTypes[i].compare("box") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.5, 0.0); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			glutSolidCube(50);
			glPopMatrix();
		}
		if(shapeTypes[i].compare("cone") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.5, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			glutSolidCone(3, 5, 100, 100);
			glPopMatrix();
		}
		if(shapeTypes[i].compare("cylinder") == 0)
		{
			glPushMatrix();
			glColor3f(0.5, 0.5, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			gluCylinder(quad, 3, 3, 5, 100, 100);
			glPopMatrix();
		}
		/*if(shapeTypes[i].compare("capsule") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.5, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			glutSolidCone(3, 5, 100, 100);
			glPopMatrix();
		}*/
		/*if(shapeTypes[i].compare("convex") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.5, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			glutSolidCone(3, 5, 100, 100);
			glPopMatrix();
		}
		if(shapeTypes[i].compare("heightfield") == 0)
		{
			glPushMatrix();
			glColor3f(0.0, 0.5, 0.5); 
			glTranslatef(collisionBodyPos[i].x, collisionBodyPos[i].y, collisionBodyPos[i].z);
			glutSolidCone(3, 5, 100, 100);
			glPopMatrix();
		}*/
	}

	//glutSwapBuffers();
	//glFlush();

	return cam;
}

// Initialize all collision bodies and shapes
void GraphicsEngine::Prepare(Vec3 cam)
{
	physics.MakeCollisionShapes();
	physics.MakeCollisionBodies(collisionBodyPos, numberCollisionShapes, shapeTypes);
	physics.AddCam(cam);

	for(int i = 0; i < numberCollisionShapes.size(); i++)
		totalNumCol += numberCollisionShapes[i];
}