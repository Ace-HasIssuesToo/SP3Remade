#ifndef SENSOR
#define SENSOR
#include "Input_PI.h"
#include "Map_PI.h"
class Sensor
{
public:
	static Sensor* pointer(){ return m_pointer; };
	void Init();
	void Update(double dt);
	void Render();
	void Exit();
private:
	void Mesh_Update(Mesh* mesh,double dt);
	void Range_Cal(Vector3 Enemy_Pos);
	Sensor(){};
	~Sensor(){};
	Mesh* Save;
	Mesh* Danger;
	Mesh*dead;
	int Range;
	Vector3 Player_Pos;
	static Sensor* m_pointer;
};

#endif