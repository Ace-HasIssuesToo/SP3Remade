#include "Camera_PI.h"
#include "Application.h"
#include "Mtx44.h"

Camera_PI::Camera_PI()
{
}

Camera_PI::~Camera_PI()
{
}

void Camera_PI::Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float& XZ_Angle, const float& Y_Angle)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->XZ_Angle = XZ_Angle;
	this->Y_Angle = Y_Angle;
}