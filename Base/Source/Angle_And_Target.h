#ifndef ANGLE_AND_TARGET
#define ANGEL_AND_TARGET
#include "Camera_PI.h"

class A_A_T
{
public:
	static float Angle(float Input_PI);

	static float Angle_Cal(Vector3 Origin, Vector3 Target);

	static Vector3 Target_Cal(Vector3 Origin, float Angle_, float Range);

	static Vector3 target_calculator(Vector3 origin, float Range, float XZ_Angle, float Y_Angle);
};

#endif