#include"Input_PI.h"


Input_PI* Input_PI::m_pointer = new Input_PI();

void Input_PI::Init()
{
	for (int i = Nothing + 1; i < All_Control; i++)
	{
		IsBeingPressed[i] = false;
		HaveBeenPressed[i] = false;
	}
}

void Input_PI::Clear()
{
	for (int i = Nothing + 1; i < All_Control; i++)
	{
		HaveBeenPressed[i] = false;
	}
}

void Input_PI::Update(double dt)
{
	Clear();
	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		IsBeingPressed[PokeThrow] = true;
	}
	else if (IsBeingPressed[PokeThrow] == true)
	{
		IsBeingPressed[PokeThrow] = false;
		HaveBeenPressed[PokeThrow] = true;
	}
	if (Application::IsKeyPressed(VK_RBUTTON))
	{
		IsBeingPressed[Light_Switch] = true;
	}
	else if (IsBeingPressed[Light_Switch] == true)
	{
		IsBeingPressed[Light_Switch] = false;
		HaveBeenPressed[Light_Switch] = true;
	}
	if (Application::IsKeyPressed('A'))
	{
		IsBeingPressed[Leftward] = true;
	}
	else
	{
		IsBeingPressed[Leftward] = false;
	}
	if (Application::IsKeyPressed('D'))
	{
		IsBeingPressed[Rightward] = true;
	}
	else
	{
		IsBeingPressed[Rightward] = false;
	}
	if (Application::IsKeyPressed('W'))
	{
		IsBeingPressed[Forward] = true;
	}
	else
	{
		IsBeingPressed[Forward] = false;
	}
	if (Application::IsKeyPressed('S'))
	{
		IsBeingPressed[Backward] = true;
	}
	else
	{
		IsBeingPressed[Backward] = false;
	}
	if (Application::IsKeyPressed(VK_SHIFT))
	{
		IsBeingPressed[Run] = true;
	}
	else if (IsBeingPressed[Run] == true)
	{
		IsBeingPressed[Run] = false;
		HaveBeenPressed[Run] = true;
	}
}


void Input_PI::Render()
{

}

void Input_PI::Exit()
{
	delete m_pointer;
}
