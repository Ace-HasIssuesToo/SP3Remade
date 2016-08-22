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
	if (Application::IsKeyPressed(VK_UP))
	{
		IsBeingPressed[PokeThrowFront] = true;
	}
	else if (IsBeingPressed[PokeThrowFront] == true)
	{
		IsBeingPressed[PokeThrowFront] = false;
		HaveBeenPressed[PokeThrowFront] = true;
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		IsBeingPressed[PokeThrowBack] = true;
	}
	else if (IsBeingPressed[PokeThrowBack] == true)
	{
		IsBeingPressed[PokeThrowBack] = false;
		HaveBeenPressed[PokeThrowBack] = true;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		IsBeingPressed[PokeThrowLeft] = true;
	}
	else if (IsBeingPressed[PokeThrowLeft] == true)
	{
		IsBeingPressed[PokeThrowLeft] = false;
		HaveBeenPressed[PokeThrowLeft] = true;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		IsBeingPressed[PokeThrowRight] = true;
	}
	else if (IsBeingPressed[PokeThrowRight] == true)
	{
		IsBeingPressed[PokeThrowRight] = false;
		HaveBeenPressed[PokeThrowRight] = true;
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

	if (Application::IsKeyPressed(VK_SHIFT))
	{
		IsBeingPressed[Run] = true;
	}
	else
	{
		IsBeingPressed[Run] = false;
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
	if (Application::IsKeyPressed(VK_RETURN))
	{
		IsBeingPressed[NextStatement] = true;
	}
	else if (IsBeingPressed[NextStatement] == true)
	{
		IsBeingPressed[NextStatement] = false;
		HaveBeenPressed[NextStatement] = true;
	}
}


void Input_PI::Render()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	}
}

void Input_PI::Exit()
{
	delete m_pointer;
}
