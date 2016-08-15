#include "Angle_And_Target.h"

bool Zero_Check(float input, float check)
{
	return ((input<(check - Math::EPSILON)) || (input>(check + Math::EPSILON)));
}

float A_A_T::Angle(float Input_Controller)
{
	if (Input_Controller > 360)
	{
		Input_Controller -= 360;
	}
	else if (Input_Controller < 0)
	{
		Input_Controller += 360;
	}
	return Input_Controller;
}

float A_A_T::Angle_Cal(Vector3 Origin, Vector3 Target)
{
	float Angle_ = 0;
	if (Target.x > Origin.x)
	{
		float X = Target.x - Origin.x;
		float Y = 0;
		if (Target.y > Origin.y)
		{
			Y = Target.y - Origin.y;
			Angle_ = 270 + Math::RadianToDegree(atan(Y / X));
		}
		else if (Target.y < Origin.y)
		{
			Y = Origin.y - Target.y;
			Angle_ = 180 + Math::RadianToDegree(atan(X / Y));
		}
		else if (Target.y == Origin.y)
		{
			Angle_ = 270;
		}
	}
	else if (Target.x < Origin.x)
	{
		float X = Origin.x - Target.x;
		float Y = 0;
		if (Target.y > Origin.y)
		{
			Y = Target.y - Origin.y;
			Angle_ = Math::RadianToDegree(atan(X / Y));
		}
		else if (Target.y < Origin.y)
		{
			Y = Origin.y - Target.y;
			Angle_ = 90 + Math::RadianToDegree(atan(Y / X));
		}
		else if (Target.y == Origin.y)
		{
			Angle_ = 90;
		}
	}
	else if (Target.x == Origin.x)
	{
		if (Target.y > Origin.y)
		{
			Angle_ = 0;
		}
		else if (Target.y < Origin.y)
		{
			Angle_ = 180;
		}
	}
	return Angle(Angle_);
}

Vector3 A_A_T::Target_Cal(Vector3 Origin, float Angle_, float Range)
{
	float Ang = Angle(Angle_);
	float X = 0;
	float Z = 0;
	if (Zero_Check(Ang, 0) && Zero_Check(Ang, 180))
	{
		Z = Origin.z + Range * Math::RadianToDegree(sin(Math::DegreeToRadian(Ang)));
	}
	if (Zero_Check(Ang, 90) && Zero_Check(Ang, 270))
	{
		X = Origin.x + Range * Math::RadianToDegree(cos(Math::DegreeToRadian(Ang)));
	}
	return Vector3(X, Origin.y, Z);
}

Vector3 A_A_T::target_calculator(Vector3 origin, float Range, float XZ_Angle, float Y_Angle)
{
	float CosY = 0;
	float SinY = 0;
	float CosXZ = 0;
	float SinXZ = 0;
	if (Y_Angle != 90 && Y_Angle != 270)
	{
		CosY = cos(Math::DegreeToRadian(Y_Angle));
	}
	if (Y_Angle != 0 && Y_Angle != 180)
	{
		SinY = sin(Math::DegreeToRadian(Y_Angle));
	}
	if (XZ_Angle != 90 && XZ_Angle != 270)
	{
		CosXZ = cos(Math::DegreeToRadian(XZ_Angle));
	}
	if (XZ_Angle != 0 && XZ_Angle != 180)
	{
		SinXZ = sin(Math::DegreeToRadian(XZ_Angle));
	}

	Vector3 Return_Vec;
	Return_Vec.x = origin.x + Range*CosY * CosXZ;
	Return_Vec.y = origin.y + Range*SinY;
	Return_Vec.z = origin.z + Range*CosY * SinXZ;
	return Return_Vec;
}