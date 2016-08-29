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
	if (Application::IsKeyPressed('F'))
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
	if (Application::IsKeyPressed(VK_RETURN))
	{
		IsBeingPressed[IntroSkip] = true;
	}
	else if (IsBeingPressed[IntroSkip] == true)
	{
		IsBeingPressed[IntroSkip] = false;
		HaveBeenPressed[IntroSkip] = true;
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
		IsBeingPressed[GameplayNext] = true;
	}
	else if (IsBeingPressed[GameplayNext] == true)
	{
		IsBeingPressed[GameplayNext] = false;
		HaveBeenPressed[GameplayNext] = true;
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
		IsBeingPressed[DuringGP] = true;
	}
	else if (IsBeingPressed[DuringGP] == true)
	{
		IsBeingPressed[DuringGP] = false;
		HaveBeenPressed[DuringGP] = true;
	}
	if (Application::IsKeyPressed('S'))
	{
		IsBeingPressed[Backward] = true;
	}
	else
	{
		IsBeingPressed[Backward] = false;
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
	if (Application::IsKeyPressed('F'))
	{
		IsBeingPressed[OnLight] = true;
	}
	else if (IsBeingPressed[OnLight] == true)
	{
		IsBeingPressed[OnLight] = false;
		HaveBeenPressed[OnLight] = true;
	}
	if (Application::IsKeyPressed('G'))
	{
		IsBeingPressed[OffLight] = true;
	}
	else if (IsBeingPressed[OffLight] == true)
	{
		IsBeingPressed[OffLight] = false;
		HaveBeenPressed[OffLight] = true;
	}
	if (Application::IsKeyPressed('1'))
	{
		IsBeingPressed[UseBattery] = true;
	}
	else if (IsBeingPressed[UseBattery] == true)
	{
		IsBeingPressed[UseBattery] = false;
		HaveBeenPressed[UseBattery] = true;
	}
	if (Application::IsKeyPressed('2'))
	{
		IsBeingPressed[UseDrink] = true;
	}
	else if (IsBeingPressed[UseDrink] == true)
	{
		IsBeingPressed[UseDrink] = false;
		HaveBeenPressed[UseDrink] = true;
	}
	if (Application::IsKeyPressed('N'))
	{
		IsBeingPressed[NextLevel] = true;
	}
	else if (IsBeingPressed[NextLevel] == true)
	{
		IsBeingPressed[NextLevel] = false;
		HaveBeenPressed[NextLevel] = true;
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
	if (m_pointer != nullptr)
	{
		delete m_pointer;
	}
}
