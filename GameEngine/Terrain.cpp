/*
* Implementation of Terrain.h file
* Author - Jack Matters
*/

#include "Terrain.h"

// Default constructor
Terrain::Terrain()
{
	position = Vec3(0, 0, 0);
}

// Non-default constructor
Terrain::~Terrain(){}

// Render a terrain field
void Terrain::Render(){}

// Move terrain? Needed as it is a virtual function
void Terrain::Move(){}

// Return the chosen Terrain Vec3 data
Vec3 Terrain::Get(int choice)
{
	if(choice == 1)
		return position;
}

// Set the passed in Vec3 to chosen Terrain Vec3
void Terrain::Set(int choice, Vec3 vec){}