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
}

void Debug_PI::Update(double dt)
{
}

void Debug_PI::Render()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BackGround"), false, (Render_PI::Window_Scale()*0.5) + Vector3(0, 0, -1), Render_PI::Window_Scale() + Vector3(0, 0, 1));
	Render_PI::pointer()->modelStack_Set(false);

}

void Debug_PI::Exit()
{

}
