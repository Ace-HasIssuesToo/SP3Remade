#ifndef ROOM_SCENE
#define ROOM_SCENE
#include "Game_Core.h"
#include "Vector3.h"

class Room_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void Render_Scene(Vector3 Pos);
	void Recursive_Maze_Generator(Vector3 Top, Vector3 Bottom, int Min_Height);
	void Room_Render(int X, int Z);
	static bool Collision_Check(Vector3 pos);
private:

};

#endif