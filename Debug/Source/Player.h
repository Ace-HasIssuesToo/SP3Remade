#ifndef PLAYER
#define PLAYER

#include "camera.h"

class Player
{
public:
	enum Direction_Type
	{
		forward,
		backward,
		left,
		right,
	};
	Camera Get_camera(){ return camera; };
	void Set_camera(Camera Input){ camera = Input; };
	float Get_AngleXZ(){ return Angle_XZ; };
	void Set_AngleXZ(float Input){ Angle_XZ = Input; };
	float Get_AngleY(){ return Angle_Y; };
	void Set_AngleY(float Input){ Angle_Y = Input; };
	void Update(float dt);
	void Jump(float dt);
	void View(float dt);
	void Move(float speed, int Direction, bool Run);
	void Still();
private:
	Camera camera;
	float Angle_XZ;
	float Angle_Y;
	Vector3 Move_Vel;
	float Jump_Vel;
	float dt_check;
};

#endif