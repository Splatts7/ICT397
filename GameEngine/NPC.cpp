/*
* Implementation of NPC.h file
* Author - Jack Matters
*/

#include "NPC.h"

// Default constructor
NPC::NPC()
{
	position = Vec3(0, 0, 0);
}

// Non-default constructor
NPC::~NPC(){}

// Render an NPC
void NPC::Render(){}

// Move the NPC based on AI?
void NPC::Move(){}

// Return the chosen NPC Vec3 data
Vec3 NPC::Get(int choice)
{
	if(choice == 1)
		return position;
}

// Set the passed in Vec3 to chosen NPC Vec3
void NPC::Set(int choice, Vec3 vec)
{
	if(choice == 1)
		position = vec;
}