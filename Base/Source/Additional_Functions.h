#ifndef ADDITIONALFUNCTIONS
#define ADDITIONALFUNCTIONS

#include "Support_Codes.h"
#include "Map_PI.h"

class Functions
{
public:
	static Vector3 PathFinding(Vector3 Current_Pos, Vector3 Target_Pos,float Speed, Map* map);
	static Vector3 DisplaceWall(Vector3 movement, Vector3 Size);
};

#endif