#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera_PI
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	float XZ_Angle;
	float Y_Angle;

	Camera_PI();
	~Camera_PI();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float& XZ_Angle, const float& Y_Angle);
};

#endif