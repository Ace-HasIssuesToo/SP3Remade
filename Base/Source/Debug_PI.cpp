#include "Debug_PI.h"
#include "Texture_PI.h"

Debug_PI* Debug_PI::c_pointer = new Debug_PI();

Debug_PI::Debug_PI()
{

}

Debug_PI::~Debug_PI()
{

}

void Debug_PI::Init()
{
	Camera_PI camera;
	camera.Init(Vector3(10, 0, 0), Vector3(), Vector3(0, 1, 0), 0, 0);
	Render_PI::pointer()->Camera_Set(camera);
	if (!Floor1.Init("Data\\Map\\Floor1.csv"))
	{
		cout << "File Error" << endl;
	}
}

void Debug_PI::Update(double dt)
{
}

void Debug_PI::Render()
{
	Floor1.Render(Vector3());
}

void Debug_PI::Exit()
{

}
