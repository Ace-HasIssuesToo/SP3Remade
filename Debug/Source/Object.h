#ifndef OBJECT
#define OBJECT

#include "Vector3.h"
#include "Mesh.h"

class Object
{
private:
	Vector3 position;
	Vector3 direction;
	Vector3 target;
	Vector3 rotation;
	Mesh* mesh;
	int state;
	int power;
public:
	Object(){};
	Object(const Object &copy)
	{
		position = copy.position;
		direction = copy.direction;
		target = copy.target;
		rotation = copy.rotation;
		mesh = copy.mesh;
		state = copy.state;
		power = copy.power;
	};
	~Object(){};
	Vector3 Get_position(){ return position; };
	Vector3 Get_direction(){ return direction; };
	Vector3 Get_target(){ return target; };
	Vector3 Get_rotation(){ return rotation; };
	Mesh* Get_mesh(){ return mesh; };
	int Get_state(){ return state; };
	int Get_power(){ return power; };
	void Set_position(Vector3 Input){ position = Input; };
	void Set_direction(Vector3 Input){ direction = Input; };
	void Set_target(Vector3 Input){ target = Input; };
	void Set_rotation(Vector3 Input){ rotation = Input; };
	void Set_mesh(Mesh* Input){ mesh = new Mesh(*Input); };
	void Set_state(int Input){ state = Input; };
	void Set_power(int Input){ power = Input; };
};

#endif