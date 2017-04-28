-- CollisionBodies.lua
-- Script for loading in data for collision bodies
-- Author - Jack Matters
-- Date - 27/04/2017
numsphere=4
numbox=3
numcone=1
numcylinder=1
numcapsule=0
numconvex=0
numheightfield=0
bodies=
{
  sphere=
  {
    position=
    {
      {x = 0.0, y = 50.0, z = 0.0, type = "dynamic", mass = 1.0},
      {x = 0.0, y = -50.0, z = 0.0, type = "dynamic", mass = 1.0},
      {x = -52.0, y = -10.0, z = 0.0, type = "dynamic", mass = 1.0},
      {x = -50.0, y = 10.0, z = 0.0, type = "dynamic", mass = 1.0},
    }
  },
  box=
  {
    position=
    {
      {x = 50.0, y = -200.0, z = 0.0, type = "static", mass = 1.0},
      {x = -50.0, y = -100.0, z = 0.0, type = "static", mass = 1.0},
      {x = 0.0, y = 0.0, z = 0.0, type = "static", mass = 1.0},
    }
  },
  cone=
  {
    position=
    {
      {x = 50.0, y = 30.0, z = 0.0, type = "dynamic", mass = 1.0},
    }
  },
  cylinder=
  {
    position=
    {
      {x = -50.0, y = 30.0, z = 0.0, type = "dynamic", mass = 1.0},
    }
  }
}
